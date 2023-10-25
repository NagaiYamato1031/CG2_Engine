#include "ModelManager.h"
#include "../Utility/MyUtility.h"
#include "../Resource/Texture/TextureManager.h"

#include <cassert>
#include <sstream>
#include <fstream>

using namespace Microsoft::WRL;

ModelManager* ModelManager::GetInstance()
{
	static ModelManager instance;
	return &instance;
}

void ModelManager::Initialize(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	dxCommon_ = dxCommon;
	modelDatas_.clear();
	CreatePSO();
}

Model::ModelData ModelManager::LoadModel(const std::string& directoryPath, const std::string& fileName)
{
	// モデルまでのフルパスを合成する
	std::string FullPath = directoryPath + "/" + fileName;

	// 同名のキーを見つけたらそれを返す
	if (modelDatas_.find(FullPath) != modelDatas_.end()) {
		// モデルの頂点データ等を渡す
		return modelDatas_[FullPath];
	}
	else {// 見つからなかった場合は読み込む

		Model::ModelData modelData_; // 構築するモデルデータ
		std::vector<Vector4> positions_; // 位置
		std::vector<Vector2> uv_; // UV座標系
		std::vector<Vector3> normal_; // 法線
		std::string line_; // ファイルから読んだ１行を格納するもの

		// ファイルを開く
		std::ifstream file(FullPath);
		// 開けなかった場合を止める
		assert(file.is_open());

		// ファイルの終端まで読む
		while (std::getline(file, line_)) {
			// 先端の識別子の値を格納する変数
			std::string identifier;
			// ファイルの１行を取得
			std::istringstream s(line_);
			// 先頭の識別子を読む
			s >> identifier;

			// 頂点だった場合
			if (identifier == "v") {
				// 位置座標用
				Vector4 position;
				// 空文字区切りで１つずつ値を読む
				s >> position.x >> position.y >> position.z;
				// wを設定
				position.w = 1.0f;
				position.x *= -1.0f;
				// 頂点の配列に追加する
				positions_.push_back(position);
			}
			// UVだった場合
			else if (identifier == "vt") {
				// UV座標用
				Vector2 uv;
				// 空文字区切りで1つずつ値を読む
				s >> uv.x >> uv.y;
				uv.y = 1.0f - uv.y;
				// UVの配列に追加する
				uv_.push_back(uv);
			}
			// 法線だった場合
			else if (identifier == "vn") {
				// 法線用
				Vector3 normal;
				// 空文字区切りで１つずつ値を読む
				s >> normal.x >> normal.y >> normal.z;
				normal.x *= -1.0f;
				// 法線の配列に追加する
				normal_.push_back(normal);
			}
			// 終了なら
			else if (identifier == "f") {
				Model::VertexData triangle[3];
				// 面は三角形のみ、　そのほかは対応していない
				for (int32_t faceVertex = 0; faceVertex < 3; faceVertex++) {
					// 頂点情報
					std::string vertexDefinition;
					// 識別子を取得
					s >> vertexDefinition;

					// 頂点の要素へのIndexは 位置 / UV / 法線で格納されているため、分解してIndexを取得
					std::stringstream v(vertexDefinition);
					uint32_t elementIndices[3];
					for (int32_t element = 0; element < 3; element++) {
						std::string index;
						// 区切りのインデックスを読む
						std::getline(v, index, '/');
						elementIndices[element] = std::stoi(index);
					}
					// 要素へのIndexから実際の要素の値を取得して、頂点を構築する
					Vector4 position = positions_[elementIndices[0] - 1];
					Vector2 uv = uv_[elementIndices[1] - 1];
					Vector3 normal = normal_[elementIndices[2] - 1];
					triangle[faceVertex] = { position, uv, normal };
				}
				modelData_.vertices.push_back(triangle[2]);
				modelData_.vertices.push_back(triangle[1]);
				modelData_.vertices.push_back(triangle[0]);
			}
			else if (identifier == "mtllib") {
				std::string materialFileName;
				s >> materialFileName;
				modelData_.material = LoadMaterial(directoryPath, materialFileName);
			}
		}

		// 読み込んだモデルデータをコンテナに格納する
		modelDatas_[FullPath] = modelData_;

		// 値を返す
		return modelData_;

	}
}

Model::MaterialData ModelManager::LoadMaterial(const std::string& directoryPath, const std::string& fileName)
{
	Model::MaterialData materialData; // 構築するマテリアルデータ
	std::string line; // ファイルから読んだ１行を格納するモノ

	// ファイルを開く
	std::ifstream file(directoryPath + "/" + fileName);
	// 開けなかった場合を止める
	assert(file.is_open());

	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		// identifier に応じた処理
		if (identifier == "map_Kd") {
			std::string textureFileName;
			s >> textureFileName;
			// 連結してファイルパスに
			materialData.textureFilePath = textureFileName;
		}
	}

	// マテリアルデータを返す
	return materialData;
}

void ModelManager::SetPSO()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon_->GetCommandList();
	cmdList->SetPipelineState(pso_->state_.Get());
	cmdList->SetComputeRootSignature(pso_->rootSignature_.Get());
}

void ModelManager::CreatePSO()
{

	pso_.reset(new PSO);

	HRESULT hr = S_FALSE;

	// PSOの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	// DescriptorRange
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0; // 0から始まる
	descriptorRange[0].NumDescriptors = 1; // 数は1つ
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算

	// ルートシグネチャを作成する
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	// ルートパラメータを設定する
	D3D12_ROOT_PARAMETER rootParameters[3] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[2].Descriptor.ShaderRegister = 1;
	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	// Sampler設定
	D3D12_STATIC_SAMPLER_DESC staticSamples[1] = {};
	staticSamples[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
	staticSamples[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 0~1の範囲外をリピート
	staticSamples[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamples[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamples[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
	staticSamples[0].MaxLOD = D3D12_FLOAT32_MAX; // ありったけのMipMapをつかう
	staticSamples[0].ShaderRegister = 0; // レジスタ番号0を使う
	staticSamples[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	descriptionRootSignature.pStaticSamplers = staticSamples;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamples);

	// シリアライズしてバイナリにする
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	// バイナリできているかを確認する
	if (FAILED(hr)) {
		// エラーが出た場合ログにそれを出力
		MyUtility::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		// 停止させる
		assert(false);
	}

	// バイナリを元に実際にルートシグネチャを生成
	hr = dxCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso_->rootSignature_));
	// 生成出来ているかを確認する
	assert(SUCCEEDED(hr));

	// インプットレイアウトの設定を行う
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;;
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
	graphicsPipelineStateDesc.InputLayout.pInputElementDescs = inputElementDescs;
	graphicsPipelineStateDesc.InputLayout.NumElements = _countof(inputElementDescs);

	// ブレンドステートの設定を行う
	D3D12_BLEND_DESC blendDesc{};
	// 全ての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;
	// ノーマルブレンドの設定
	blendDesc.RenderTarget[0].BlendEnable = true; // ブレンド有効
	blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;

	// ラスタライザステートの設定を行う
	D3D12_RASTERIZER_DESC rasterrizerDesc{};
	// 背面カリング
	rasterrizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterrizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	// デプスステンシルビューの設定を行う
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	// 深度の機能を有効
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はlessEqual 近ければ描画
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// 頂点シェーダ用のバイナリオブジェクト
	ComPtr<IDxcBlob> vertexBlob;
	// ピクセルシェーダ用のバイナリオブジェクト
	ComPtr<IDxcBlob> pixelBlob;

	// 頂点シェーダをコンパイルする
	vertexBlob = dxCommon_->GetDXC()->CompileShader(L"./resources/shaders/Object3d.VS.hlsl", L"vs_6_0");
	// コンパイル出来たか確認する
	assert(vertexBlob != nullptr);
	// ピクセルシェーダをコンパイルする
	pixelBlob = dxCommon_->GetDXC()->CompileShader(L"./Resources/shaders/Object3D.PS.hlsl", L"ps_6_0");
	// コンパイル出来たか確認する
	assert(pixelBlob != nullptr);

	// ルートシグネチャ
	graphicsPipelineStateDesc.pRootSignature = pso_->rootSignature_.Get();
	// 頂点シェーダ
	graphicsPipelineStateDesc.VS = { vertexBlob->GetBufferPointer(),
	vertexBlob->GetBufferSize() };
	// ピクセルシェーダ
	graphicsPipelineStateDesc.PS = { pixelBlob->GetBufferPointer(),
	pixelBlob->GetBufferSize() };
	// ブレンドステート
	graphicsPipelineStateDesc.BlendState = blendDesc;
	// ラスタライザステート
	graphicsPipelineStateDesc.RasterizerState = rasterrizerDesc;
	// デプスステンシルビュー
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	graphicsPipelineStateDesc.DepthStencilState = depthStencilDesc;

	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	// 利用するトポロジーのタイプ
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 3角形

	// どのように画面に色を打ち込むかの設定
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// 設定を元に実際に生成を行う
	hr = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&pso_->state_));
	// 生成出来ているかを確認する
	assert(SUCCEEDED(hr));
}