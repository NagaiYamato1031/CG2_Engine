#include "Particle.h"
#include "../Utility/MyUtility.h"

#include <assert.h>
#include <fstream>
#include <sstream>

#include "../Base/DirectXCommon.h"
#include "../Base/PSO/PSO.h"
#include "../Resource/Texture/TextureManager.h"

using ModelData = Particle::ModelData;
using VertexData = Particle::VertexData;
using MaterialData = Particle::MaterialData;


DirectXCommon* Particle::sDXCommon_ = nullptr;
std::unique_ptr<PSO> Particle::sPSO_;

void Particle::StaticInitialize(DirectXCommon* dxCommon)
{
	assert(dxCommon);

	sDXCommon_ = dxCommon;

	CreatePSO();

}


ModelData Particle::LoadObjFile(const std::string& directoryPath, const std::string& filename) {
	// 使う変数の宣言
	ModelData modelData;
	std::vector<Vector4> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;
	std::string line;

	// ファイルを開く
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());

	// ファイルを読んで、ModelData を構築
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream	s(line);
		// 先頭の識別子を読む
		s >> identifier;

		// identifer に応じた処理
		// 頂点
		if (identifier == "v") {
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			position.w = 1.0f;
			position.x *= -1;
			positions.push_back(position);
		}
		// テクスチャ
		else if (identifier == "vt") {
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			texcoords.push_back(texcoord);
		}
		// 法線
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			normal.x *= -1;
			normals.push_back(normal);
		}
		// 面
		else if (identifier == "f") {
			VertexData triangle[3];
			// 面は三角形限定。その他は未対応
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				// 頂点の要素への Index は[位置/UV/法線]で格納されているので、分解して Index を取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					// '/' 区切りで Index を読んでいく
					std::getline(v, index, '/');
					elementIndices[element] = std::stoi(index);
				}
				// 要素への Index から、実際の要素の値を取得して、頂点を構成する
				// obj ファイルの Index は 1 から始まっているので -1 する
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				//VertexData vertex = { position,texcoord,normal };
				//modelData.vertices.push_back(vertex);
				triangle[faceVertex] = { position,texcoord,normal };
			}
			modelData.vertices.push_back(triangle[2]);
			modelData.vertices.push_back(triangle[1]);
			modelData.vertices.push_back(triangle[0]);
		}
		else if (identifier == "mtllib") {
			// MaterialTemplateLibraty ファイルの名前を取得する
			std::string materialFilename;
			s >> materialFilename;
			// 基本的に obj ファイルと同一階層に mtl は存在させるので、ディレクトリ名とファイル名を渡す
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
		}
	}
	return modelData;
}

void Particle::CreatePSO()
{
	sPSO_.reset(new PSO());


	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// DepthStencilState の設定
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	// Depth の機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込みする
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数は LessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = CreatePipelineStateDesc();

	// 生成時に存在させておく
	psoDesc.InputLayout = inputLayoutDesc;
	psoDesc.DepthStencilState = depthStencilDesc;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	HRESULT hr = S_FALSE;
	hr = sDXCommon_->GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&sPSO_->state_));
	assert(SUCCEEDED(hr));
}

D3D12_GRAPHICS_PIPELINE_STATE_DESC Particle::CreatePipelineStateDesc()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	CreateRootSignature();


	graphicsPipelineStateDesc.pRootSignature = sPSO_->rootSignature_.Get();

	// 生成時に実体がないとエラーが起きる
	//graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;


	IDxcBlob* vsBlob = sDXCommon_->GetDXC()->CompileShader(L"Particle.VS.hlsl", L"vs_6_0");
	IDxcBlob* psBlob = sDXCommon_->GetDXC()->CompileShader(L"Particle.PS.hlsl", L"ps_6_0");

	graphicsPipelineStateDesc.VS = { vsBlob->GetBufferPointer(),vsBlob->GetBufferSize() };
	graphicsPipelineStateDesc.PS = { psBlob->GetBufferPointer(),psBlob->GetBufferSize() };

	graphicsPipelineStateDesc.BlendState = CreateBlendDesc();
	graphicsPipelineStateDesc.RasterizerState = CreateRasterizerDesc();;
	// 書き込む RTV の情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	// 利用するトポロジ（形状）のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	// どのように画面に色を打ち込むかの設定（気にしなくていい）
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	// DepthStencil の設定
	graphicsPipelineStateDesc.DepthStencilState = CreateDepthStencilDesc();
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	return graphicsPipelineStateDesc;
}

void Particle::CreateRootSignature()
{
	HRESULT hr = S_FALSE;

	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	// デスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0;
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// ルートパラメータ
	D3D12_ROOT_PARAMETER rootParameters[2] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);

	// ここでインスタンシングの設定
	// デスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE SBdescriptorRange[1] = {};
	SBdescriptorRange[0].BaseShaderRegister = 0;
	SBdescriptorRange[0].NumDescriptors = 1;
	SBdescriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	SBdescriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].DescriptorTable.pDescriptorRanges = SBdescriptorRange;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(SBdescriptorRange);

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	// Sampler
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;			// バイリニアフィルタ
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;		// 0 ～ 1 の範囲外をリピート
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;		// 比較しない
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;						// ありったけの MitMap を使う
	staticSamplers[0].ShaderRegister = 0;								// レジスタ番号を使う
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;	// PixelShader で使う
	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	// シリアライズ
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr)) {
		MyUtility::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	// 生成
	hr = sDXCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&sPSO_->rootSignature_));
	assert(SUCCEEDED(hr));
}


D3D12_BLEND_DESC Particle::CreateBlendDesc()
{
	// BlendState の設定
	D3D12_BLEND_DESC blendDesc{};
	// すべての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;

	return blendDesc;
}

D3D12_RASTERIZER_DESC Particle::CreateRasterizerDesc()
{
	// Rasterizerstate の設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	// 裏面（時計回り）を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	return rasterizerDesc;
}

D3D12_DEPTH_STENCIL_DESC Particle::CreateDepthStencilDesc()
{
	// DepthStencilState の設定
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	// Depth の機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込みする
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数は LessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	return depthStencilDesc;
}

void Particle::Initialize()
{

}


MaterialData Particle::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename) {
	// 必要な変数
	MaterialData materialData;
	std::string line;
	// ファイルを開く
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());
	// ファイルを読んで、MaterialData を構築
	while (std::getline(file, line)) {
		std::string identifer;
		std::istringstream s(line);
		s >> identifer;

		// identifer に応じた処理
		if (identifer == "map_Kd") {
			std::string textureFilename;
			s >> textureFilename;
			// 連結してファイルパスにする
			materialData.textureFilePath = directoryPath + "/" + textureFilename;
			materialData.textureHandle_ = TextureManager::Load(directoryPath, textureFilename);
		}
	}

	return materialData;
}

Particle* Particle::CreateOBJ(const std::string& directoryPath, const std::string& fileName, uint32_t num)
{
	Particle* model = new Particle();

	model->modelData_.vertices.push_back({ .position = {1.0f,1.0f,0.0f,1.0f}, .texcoord = {0.0f,0.0f}, .normal = {0.0f,0.0f,1.0f} });
	model->modelData_.vertices.push_back({ .position = {-1.0f,1.0f,0.0f,1.0f}, .texcoord = {1.0f,0.0f}, .normal = {0.0f,0.0f,1.0f} });
	model->modelData_.vertices.push_back({ .position = {1.0f,-1.0f,0.0f,1.0f}, .texcoord = {0.0f,1.0f}, .normal = {0.0f,0.0f,1.0f} });
	model->modelData_.vertices.push_back({ .position = {1.0f,-1.0f,0.0f,1.0f}, .texcoord = {0.0f,1.0f}, .normal = {0.0f,0.0f,1.0f} });
	model->modelData_.vertices.push_back({ .position = {-1.0f,1.0f,0.0f,1.0f}, .texcoord = {1.0f,0.0f}, .normal = {0.0f,0.0f,1.0f} });
	model->modelData_.vertices.push_back({ .position = {-1.0f,-1.0f,0.0f,1.0f}, .texcoord = {1.0f,1.0f}, .normal = {0.0f,0.0f,1.0f} });

	model->modelData_.material.textureFilePath = directoryPath + "/" + fileName;
	model->modelData_.material.textureHandle_ = TextureManager::Load(directoryPath, fileName);
	//model->modelData_ = LoadObjFile(directoryPath, fileName);

	model->numInstancing_ = num;

	model->CreateResource();

	return model;
}

void Particle::PreDraw()
{
	ID3D12GraphicsCommandList* cmdList = sDXCommon_->GetCommandList();

	cmdList->RSSetViewports(1, sDXCommon_->GetViewPort());
	cmdList->RSSetScissorRects(1, sDXCommon_->GetScissorRect());

	cmdList->SetGraphicsRootSignature(sPSO_->rootSignature_.Get());
	cmdList->SetPipelineState(sPSO_->state_.Get());

	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Particle::PostDraw()
{
}

void Particle::Draw(WorldTransform* worldTransform)
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	TextureManager* textureManager = TextureManager::GetInstance();

	transformData_->matWorld_ = worldTransform->GetMatrix();

	cmdList->IASetVertexBuffers(0, 1, &vbView_);
	textureManager->SetGraphicsDescriptorTable(0, modelData_.material.textureHandle_);
	// ルートパラメータ二番目
	cmdList->SetGraphicsRootConstantBufferView(1, transformResource_->GetGPUVirtualAddress());


	cmdList->DrawInstanced(UINT(modelData_.vertices.size()), numInstancing_, 0, 0);

}

void Particle::Draw(WorldTransform* worldTransform, ViewProjection* viewProjection)
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	TextureManager* textureManager = TextureManager::GetInstance();

	
	transformData_->matWorld_ = worldTransform->GetMatrix();
	transformData_->matWVP_ = worldTransform->GetMatrix() * viewProjection->GetViewProjectionMatrix();

	cmdList->IASetVertexBuffers(0, 1, &vbView_);
	textureManager->SetGraphicsDescriptorTable(0, modelData_.material.textureHandle_);
	// ルートパラメータ二番目
	cmdList->SetGraphicsRootDescriptorTable(1, transformResource_->GetGPUVirtualAddress());

	cmdList->DrawInstanced(UINT(modelData_.vertices.size()), numInstancing_, 0, 0);
}

void Particle::Draw(uint32_t textureHandle)
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	TextureManager* textureManager = TextureManager::GetInstance();

	cmdList->IASetVertexBuffers(0, 1, &vbView_);
	textureManager->SetGraphicsDescriptorTable(0, textureHandle);
	// ルートパラメータ二番目
	cmdList->SetGraphicsRootConstantBufferView(1, transformResource_->GetGPUVirtualAddress());


	cmdList->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);

}


void Particle::CreateResource()
{
	vertexResource_ = sDXCommon_->CreateBufferResource(sizeof(VertexData) * modelData_.vertices.size());
	vbView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = UINT(sizeof(VertexData) * modelData_.vertices.size());
	vbView_.StrideInBytes = sizeof(VertexData);

	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
	// 頂点データをリソースにコピー
	std::memcpy(vertexData_, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());

	transformResource_ = sDXCommon_->CreateBufferResource(sizeof(TransformaionMatrix) * numInstancing_);
	transformData_ = nullptr;
	transformResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformData_));
	for (size_t i = 0; i < numInstancing_; i++)
	{
		transformData_[i].matWorld_ = Matrix4x4::MakeIdentity4x4();
		transformData_[i].matWVP_ = Matrix4x4::MakeIdentity4x4();
	}

	// SRV の Heap に StructuredBuffer を作らなければいけない
	// SRV の Heap をどこに持たせるか
	// マネージャーに持たせる
	// PSO や RootSigunature の設定も全部

}
