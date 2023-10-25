#include "Model.h"
#include "../Utility/MyUtility.h"
#include "../Base/DirectXCommon.h"
#include "ModelManager.h"
#include "../Resource/Texture/TextureManager.h"

#include <cassert>

using namespace Microsoft::WRL;

void Model::StaticInitialize()
{

}

void Model::PreDraw()
{
	ID3D12GraphicsCommandList* cmdList_ = DirectXCommon::GetInstance()->GetCommandList();

	// ビューポート設定
	cmdList_->RSSetViewports(1, DirectXCommon::GetInstance()->GetViewPort());
	// シザー矩形設定
	cmdList_->RSSetScissorRects(1, DirectXCommon::GetInstance()->GetScissorRect());

	ModelManager::GetInstance()->SetPSO();

	// パイプラインステートの設定
	//cmdList_->SetPipelineState(sPSO_->state_.Get());
	// ルートシグネチャの設定
	//cmdList_->SetGraphicsRootSignature(sPSO_->rootSignature_.Get());
	// プリミティブ形状の設定を行う
	cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::PostDraw()
{
}

Model* Model::Create(WorldTransform* worldTransform, const Vector4& color, const std::string& fileName, const std::string& directoryPath)
{
	// objのインスタンスを生成する
	Model* obj =
		new Model(worldTransform, color);
	// objの中身がnullならnullを返す
	if (obj == nullptr) {
		return nullptr;
	}
	obj->Initialize(directoryPath, fileName);

	// objを返す
	return obj;
}

Model* Model::Create(const Vector4& color, const std::string& fileName, const std::string& directoryPath)
{
	// objのインスタンスを生成する
	Model* obj =
		new Model(color);
	// objの中身がnullならnullを返す
	if (obj == nullptr) {
		return nullptr;
	}
	obj->Initialize(directoryPath, fileName);

	// objを返す
	return obj;
}

Model* Model::Create(const std::string& fileName, const std::string& directoryPath)
{
	// objのインスタンスを生成する
	Model* obj = new Model();
	// objの中身がnullならnullを返す
	if (obj == nullptr) {
		return nullptr;
	}
	obj->Initialize(directoryPath, fileName);

	// objを返す
	return obj;
}

Model::Model()
{

}

Model::Model(const Vector4& color)
{
	transform_->Initialize();
	color_ = color;
	uvTransform_.Initialize();
}

Model::Model(WorldTransform* transform, const Vector4& color)
{
	transform_ = transform;
	color_ = color;
	uvTransform_.Initialize();
}

void Model::Initialize(const std::string& directoryPath, const std::string& fileName)
{
	// 結果確認用
	HRESULT result = S_FALSE;

	// モデルデータ読み込み
	modelData_ = ModelManager::GetInstance()->LoadModel(directoryPath, fileName);

	textureHandle_ = TextureManager::Load(directoryPath, modelData_.material.textureFilePath);

	// テクスチャのリソース情報を取得
	resourceDesc_ = TextureManager::GetInstance()->GetResourceDesc(textureHandle_);

	// 頂点バッファリソース生成
	vertBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(VertexData) * modelData_.vertices.size());
	// 頂点バッファのマッピングを行う
	result = vertBuff_->Map(0, nullptr, reinterpret_cast<void**>(&vertMap_));
	// マッピング出来ているかを確認する
	assert(SUCCEEDED(result));

	// 頂点バッファへのデータ転送
	memcpy(vertMap_, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());

	// リソースの先頭のアドレスから使う
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	// 使用するリソースのサイズを設定する
	vbView_.SizeInBytes = sizeof(VertexData) * (UINT)modelData_.vertices.size();
	// 1頂点アドレスを設定する
	vbView_.StrideInBytes = sizeof(VertexData);

	// 定数バッファリソース作成
	constBuff_ = DirectXCommon::GetInstance()->CreateBufferResource(sizeof(ConstBufferData));
	// 定数バッファのマッピングを行う
	result = constBuff_->Map(0, nullptr, reinterpret_cast<void**>(&constMap_));
	// マッピングできているかを確認する
	assert(SUCCEEDED(result));

	// ライティングは初期設定で有効
	constMap_->enableLighting = true;
}

void Model::Draw()
{
	Matrix4x4 worldMat = transform_->GetMatrix();

	matWorld_ = worldMat;

	constMap_->color = color_;
	constMap_->mat = matWorld_;
	constMap_->world = worldMat;
	constMap_->uvTransform = uvTransform_.GetMatrix();

	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	// 頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView_);
	// 定数バッファの設定
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// シェーダリソースビューをセット
	TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(1, textureHandle_);

	// 描画コマンド
	cmdList->DrawInstanced((UINT)modelData_.vertices.size(), 1, 0, 0);
}

void Model::Draw(WorldTransform* transform)
{
	transform_ = transform;
	Draw();
}

void Model::TransferVertices()
{
	memcpy(vertMap_, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());
}
