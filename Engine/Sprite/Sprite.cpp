#include "Sprite.h"
#include "../Resource/Texture/TextureManager.h"
#include "../Utility/MyUtility.h"

#include <cassert>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dCompiler.lib")

using namespace Microsoft::WRL;

// 静的なメンバ変数の実体を宣言する

// コマンドリスト
DirectXCommon* Sprite::sDXCommon_ = nullptr;

std::unique_ptr<PSO> Sprite::sPSO_;

// 正射影行列
Matrix4x4 Sprite::sMatProjection_;

void Sprite::StaticInitialize(DirectXCommon* dxCommon, int windowWidth, int windowHeight)
{
	// 引数のNULLチェック
	assert(dxCommon);

	sDXCommon_ = dxCommon;

	CreatePSO();

	sMatProjection_ = Matrix4x4::MakeOrthographicMatrix(0.0f, 0.0f, (float)windowWidth, (float)windowHeight, 0.0f, 100.0f);

}

void Sprite::PreDraw()
{

	// PreDrawとPostDrawがペアで呼ばれていない場合はエラー
	//assert(Sprite::cmdList == nullptr);

	// コマンドリストをセットする
	ID3D12GraphicsCommandList* cmdList = sDXCommon_->GetCommandList();

	// ビューポート設定
	cmdList->RSSetViewports(1, DirectXCommon::GetInstance()->GetViewPort());
	// シザー矩形設定
	cmdList->RSSetScissorRects(1, DirectXCommon::GetInstance()->GetScissorRect());

	// パイプラインステートの設定
	cmdList->SetPipelineState(sPSO_->state_.Get());
	// ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(sPSO_->rootSignature_.Get());
	// プリミティブ形状の設定を行う
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

}

void Sprite::PostDraw()
{
}

Sprite* Sprite::Create(uint32_t textureHandle, Vector2* position, Vector2* size, Vector4* color, Vector2 anchorPoint)
{
	// スプライトのインスタンスを生成する
	Sprite* sprite =
		new Sprite(textureHandle, position, size, color, anchorPoint);
	// スプライトの中身がnullならnullを返す
	if (sprite == nullptr)
	{
		return nullptr;
	}

	// 初期化
	if (!sprite->Initialize())
	{
		// 作成したスプライトを削除する
		delete sprite;
		assert(0);
		// nullを返す
		return nullptr;
	}

	// スプライトを返す
	return sprite;
}

void Sprite::CreatePSO()
{
	sPSO_.reset(new PSO());


	// インプットレイアウトの設定を行う
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);


	// デプスステンシルビューの設定を行う
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	// 深度の機能を有効
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はlessEqual 近ければ描画
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;


	// 結果確認用
	HRESULT result = S_FALSE;

	// PSOの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = CreatePipelineStateDesc();

	psoDesc.InputLayout = inputLayoutDesc;
	psoDesc.DepthStencilState = depthStencilDesc;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	result = sDXCommon_->GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&sPSO_->state_));
	assert(SUCCEEDED(result));
}

D3D12_GRAPHICS_PIPELINE_STATE_DESC Sprite::CreatePipelineStateDesc()
{
	// PSOの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	CreateRootSignature();

	graphicsPipelineStateDesc.pRootSignature = sPSO_->rootSignature_.Get();


	// 頂点シェーダ用のバイナリオブジェクト
	ComPtr<IDxcBlob> vertexBlob;
	// ピクセルシェーダ用のバイナリオブジェクト
	ComPtr<IDxcBlob> pixelBlob;

	// 頂点シェーダをコンパイルする
	vertexBlob = sDXCommon_->GetDXC()->CompileShader(L"Sprite.VS.hlsl", L"vs_6_0");
	// コンパイル出来たか確認する
	assert(vertexBlob != nullptr);
	// ピクセルシェーダをコンパイルする
	pixelBlob = sDXCommon_->GetDXC()->CompileShader(L"Sprite.PS.hlsl", L"ps_6_0");
	// コンパイル出来たか確認する
	assert(pixelBlob != nullptr);

	// ルートシグネチャ
	graphicsPipelineStateDesc.pRootSignature = sPSO_->rootSignature_.Get();
	// 頂点シェーダ
	graphicsPipelineStateDesc.VS = { vertexBlob->GetBufferPointer(),	vertexBlob->GetBufferSize() };
	// ピクセルシェーダ
	graphicsPipelineStateDesc.PS = { pixelBlob->GetBufferPointer(),	pixelBlob->GetBufferSize() };
	// ブレンドステート
	graphicsPipelineStateDesc.BlendState = CreateBlendDesc();
	// ラスタライザステート
	graphicsPipelineStateDesc.RasterizerState = CreateRasterizerDesc();
	// デプスステンシルビュー
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	graphicsPipelineStateDesc.DepthStencilState = CreateDepthStencilDesc();

	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	// 利用するトポロジーのタイプ
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 3角形

	// どのように画面に色を打ち込むかの設定
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;



	return graphicsPipelineStateDesc;
}

void Sprite::CreateRootSignature()
{
	HRESULT result = S_FALSE;

	// ルートシグネチャを作成する
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	// DescriptorRange
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0; // 0から始まる
	descriptorRange[0].NumDescriptors = 1; // 数は1つ
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV; // SRVを使う
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // Offsetを自動計算

	// ルートパラメータを設定する
	D3D12_ROOT_PARAMETER rootParameters[2] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);
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
	result = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	// バイナリできているかを確認する
	if (FAILED(result))
	{
		// エラーが出た場合ログにそれを出力
		MyUtility::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		// 停止させる
		assert(false);
	}

	// バイナリを元に実際にルートシグネチャを生成
	result = sDXCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&sPSO_->rootSignature_));
	// 生成出来ているかを確認する
	assert(SUCCEEDED(result));

}

D3D12_BLEND_DESC Sprite::CreateBlendDesc()
{
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

	return blendDesc;
}

D3D12_RASTERIZER_DESC Sprite::CreateRasterizerDesc()
{
	// ラスタライザステートの設定を行う
	D3D12_RASTERIZER_DESC rasterrizerDesc{};
	// 背面カリング
	rasterrizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterrizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	return rasterrizerDesc;
}

D3D12_DEPTH_STENCIL_DESC Sprite::CreateDepthStencilDesc()
{
	return D3D12_DEPTH_STENCIL_DESC();
}

Sprite::Sprite() {}

Sprite::Sprite(uint32_t textureHandle, Vector2* position, Vector2* size, Vector4* color, Vector2 anchorPoint)
{
	// 引数の値をメンバ変数に代入する
	position_ = position;
	size_ = size;
	anchorPoint_ = anchorPoint;
	matWorld_ = Matrix4x4::MakeIdentity4x4();
	color_ = color;
	textureHandle_ = textureHandle;
	texBase_ = { 0.0f, 0.0f };
	// テクスチャの情報を取得
	const D3D12_RESOURCE_DESC& resDesc =
		TextureManager::GetInstance()->GetResourceDesc(textureHandle);
	// 三角形のサイズをテクスチャサイズに設定
	Vector2 texSize = { (float)resDesc.Width, (float)resDesc.Height };
	texSize_ = texSize;
}

bool Sprite::Initialize()
{
	// 結果確認用
	HRESULT result = S_FALSE;

	// テクスチャのリソース情報を取得
	resourceDesc_ = TextureManager::GetInstance()->GetResourceDesc(textureHandle_);

	// 頂点バッファリソース生成
	vertBuff_ = sDXCommon_->CreateBufferResource(sizeof(VertexData) * kVertexNum);
	// 頂点バッファのマッピングを行う
	result = vertBuff_->Map(0, nullptr, reinterpret_cast<void**>(&vertMap_));
	// マッピング出来ているかを確認する
	assert(SUCCEEDED(result));

	// 頂点バッファへのデータ転送
	TransferVertices();

	// リソースの先頭のアドレスから使う
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	// 使用するリソースのサイズを設定する
	vbView_.SizeInBytes = sizeof(VertexData) * kVertexNum;
	// 1頂点アドレスを設定する
	vbView_.StrideInBytes = sizeof(VertexData);

	// 定数バッファリソース作成
	constBuff_ = sDXCommon_->CreateBufferResource(sizeof(MaterialData));
	// 定数バッファのマッピングを行う
	result = constBuff_->Map(0, nullptr, reinterpret_cast<void**>(&constMap_));
	// マッピングできているかを確認する
	assert(SUCCEEDED(result));

	// 初期化が完了したらTrueを返す
	return true;
}

void Sprite::Draw()
{
	ID3D12GraphicsCommandList* cmdList = sDXCommon_->GetCommandList();

	// 頂点更新
	TransferVertices();

	matWorld_ = Matrix4x4::MakeIdentity4x4();
	matWorld_ = matWorld_ * Matrix4x4::MakeRotateZMatrix(rotation_);
	matWorld_ = matWorld_ * Matrix4x4::MakeTranslateMatrix({ position_->x, position_->y, 0.0f });

	// 色を設定
	constMap_->color = *color_;
	// 行列を設定
	constMap_->mat = matWorld_ * sMatProjection_;
	//constMap_->mat = matWorld_;

	// 頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView_);
	// 定数バッファの設定
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// シェーダリソースビューをセット
	TextureManager::GetInstance()->SetGraphicsDescriptorTable(1, textureHandle_);

	// 描画コマンド
	cmdList->DrawInstanced(kVertexNum, 1, 0, 0);
}

void Sprite::SetTextureHandle(uint32_t textureHandle)
{
	textureHandle_ = textureHandle;
	resourceDesc_ = TextureManager::GetInstance()->GetResourceDesc(textureHandle_);
}

void Sprite::TransferVertices()
{
	// 頂点
	enum
	{
		LB, // 左下
		LT, // 左上
		RB, // 右下
		RT	// 右上
	};

	// 4頂点の座標を設定
	float left = (0.0f - anchorPoint_.x) * size_->x;
	float right = (1.0f - anchorPoint_.x) * size_->x;
	float top = (0.0f - anchorPoint_.y) * size_->y;
	float bottom = (1.0f - anchorPoint_.y) * size_->y;

	// 頂点データ
	VertexData vertices[kVertexNum];

	vertices[LB].position = { left, bottom, 0.0f, 1.0f };  // 左下
	vertices[LT].position = { left, top, 0.0f, 1.0f };     // 左上
	vertices[RB].position = { right, bottom, 0.0f, 1.0f }; // 右下
	vertices[RT].position = { right, top, 0.0f, 1.0f };    // 右上

	float tex_left = texBase_.x / resourceDesc_.Width;
	float tex_right = (texBase_.x + texSize_.x) / resourceDesc_.Width;
	float tex_top = texBase_.y / resourceDesc_.Height;
	float tex_bottom = (texBase_.y + texSize_.y) / resourceDesc_.Height;

	vertices[LB].uv = { tex_left, tex_bottom };  // 左下
	vertices[LT].uv = { tex_left, tex_top };     // 左上
	vertices[RB].uv = { tex_right, tex_bottom }; // 右下
	vertices[RT].uv = { tex_right, tex_top };    // 右上

	// 頂点バッファへのデータ転送
	memcpy(vertMap_, vertices, sizeof(vertices));
}