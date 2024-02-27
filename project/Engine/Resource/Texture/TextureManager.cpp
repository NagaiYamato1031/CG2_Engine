#include "TextureManager.h"
#include "../../Utility/MyUtility.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

#include "../../../externals/DirectXTex/d3dx12.h"
#include "../../Base/DirectXCommon.h"

using namespace Microsoft::WRL;


uint32_t TextureManager::Load(const std::string& fileName)
{
	return TextureManager::GetInstance()->LoadInternal("userResource", fileName);

}

uint32_t TextureManager::Load(const std::string& directoryPath, const std::string& fileName)
{
	return TextureManager::GetInstance()->LoadInternal("userResource/" + directoryPath, fileName);
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager textureManager;
	return &textureManager;
}

D3D12_CPU_DESCRIPTOR_HANDLE TextureManager::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += static_cast<UINT64>(descriptorSize) * static_cast<UINT64>(index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += static_cast<UINT64>(descriptorSize) * static_cast<UINT64>(index);
	return handleGPU;
}

const std::string& TextureManager::GetTextureName(uint32_t textureHandle)
{
	// 指定したテクスチャがテクスチャサイズを超過していないか確認する
	assert(textureHandle < textures_.size());

	// 指定したテクスチャの要素取得
	Texture& texture = textures_.at(textureHandle);
	// テクスチャ情報を返す
	return texture.name;
}

const D3D12_RESOURCE_DESC TextureManager::GetResourceDesc(uint32_t textureHandle)
{
	// 指定したテクスチャがテクスチャサイズを超過していないか確認する
	assert(textureHandle < textures_.size());

	// 指定したテクスチャの要素取得
	Texture& texture = textures_.at(textureHandle);
	// テクスチャ情報を返す
	return texture.resource_->GetDesc();
}

const D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetTextureGPUHandle(uint32_t textureHandle)
{
	assert(textureHandle < textures_.size());

	// 指定したテクスチャの要素取得
	Texture& texture = textures_.at(textureHandle);
	// テクスチャ情報を返す
	return texture.gpuDescriptorHandleSRV_;
}

void TextureManager::SetGraphicsDescriptorTable(uint32_t rootParameterIndex, uint32_t textureHandle)
{
	// テクスチャハンドルがテクスチャサイズを超過していないか確認する
	assert(textureHandle < textures_.size());

	// ディスクリプタヒープを取得
	ID3D12DescriptorHeap* ppHeaps[] = { dxCommon_->GetSRV()->GetHeap() };
	// 取得したディスクリプタヒープをコマンドリストにセット
	dxCommon_->GetCommandList()->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// ディスクリプタテーブルをコマンドリストにセット
	dxCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(
		rootParameterIndex, textures_[textureHandle].gpuDescriptorHandleSRV_
	);
}


void TextureManager::Initialize(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	dxCommon_ = dxCommon;
	cIncrementSize_ = dxCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	Reset();

	Load("../EngineResource", "white2x2.png");
	Load("../EngineResource", "uvChecker.png");
	Load("../EngineResource", "circle.png");
}

void TextureManager::Reset()
{
	//HRESULT hr = S_FALSE;

	//// ディスクリプタヒープの設定
	//D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	//descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; // タイプ設定
	//descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // フラッグ
	//descHeapDesc.NumDescriptors = kDescriptorSize;
	//// ディスクリプタヒープの生成
	//hr = dxCommon_->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descriptorHeap_));
	//// 生成出来ているか確認
	//assert(SUCCEEDED(hr));

	// 次のディスクリプタヒープの番号を指定
	indexNextDescriptorHeap_ = 1;

	// 全てのテクスチャをリセットする
	for (size_t i = 0; i < kDescriptorSize; i++)
	{
		textures_[i].resource_.Reset(); // リソース
		textures_[i].cpuDescriptorHandleSRV_.ptr = 0; // ディスクリプタハンドル（CPU）
		textures_[i].gpuDescriptorHandleSRV_.ptr = 0; // ディスクリプタハンドル（GPU）
		textures_[i].name.clear(); // ファイル名
	}
}

DirectX::ScratchImage TextureManager::LoadTexture(const std::string& filePath)
{
	// テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = MyUtility::ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	// ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	// ミップマップ付きのデータを返す
	return mipImages;
}

ID3D12Resource* TextureManager::CreateTextureResource(const DirectX::TexMetadata& metadata)
{
	ID3D12Device* device = DirectXCommon::GetInstance()->GetDevice();

#pragma region metadata を基に Resource の設定

	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);								// Texture の幅
	resourceDesc.Height = UINT(metadata.height);							// Texture の高さ
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);					// mipmap の数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);				// 奥行き or 配列 Texture の配列数
	resourceDesc.Format = metadata.format;									// Texture の Format
	resourceDesc.SampleDesc.Count = 1;										// サンプリングカウント。1 固定
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);	// Texture の次元数。普段は 2 次元

#pragma endregion

#pragma region 利用する Heap の設定

	D3D12_HEAP_PROPERTIES heapProperties{};
	//heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;							// 細かい設定を行う
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;	// WriteBack ポリシーで CPU アクセス可能
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;				// プロセッサの近くに配置


#pragma endregion

#pragma region Resource を生成する

	ID3D12Resource* resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties,					// Heap の設定
		D3D12_HEAP_FLAG_NONE,				// Heap の特殊な設定。特になし。
		&resourceDesc,						// Resource の設定
		D3D12_RESOURCE_STATE_GENERIC_READ,		// データ転送される設定
		//D3D12_RESOURCE_STATE_COPY_DEST,		// データ転送される設定
		nullptr,							// Clear 最適値。使わないので nullptr
		IID_PPV_ARGS(&resource)				// 作成する Resource ポインタへのポインタ
	);
	hr;
	assert(SUCCEEDED(hr));
	return resource;

#pragma endregion

}

void TextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	// Meta 情報を取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	// 全 MipMap について
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel)
	{
		// MipLevel を指定して各 Image を取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
		// Texture に転送
		HRESULT hr = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr,				// 全領域へコピー
			img->pixels,			// 元データアドレス
			UINT(img->rowPitch),	// 1 ラインサイズ
			UINT(img->slicePitch)	// 1 枚サイズ
		);
		hr;
		assert(SUCCEEDED(hr));
	}
}


[[nodiscard]]
ID3D12Resource* TextureManager::UploadTextureDataEx(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	DirectX::PrepareUpload(dxCommon->GetDevice(), mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermediateSize = GetRequiredIntermediateSize(texture, 0, UINT(subresources.size()));
	ID3D12Resource* intermediateResource = dxCommon->CreateBufferResource(intermediateSize);
	UpdateSubresources(dxCommon->GetCommandList(), texture, intermediateResource, 0, 0, UINT(subresources.size()), subresources.data());
	// Texture への転送後は利用できるよう、D3D12_RESOURCE_STATE_COPY_DEST から D3D12_RESOURCE_STATE_GENERIC_READ へ ResourceState を変更する
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	dxCommon->GetCommandList()->ResourceBarrier(1, &barrier);
	return intermediateResource;
}

uint32_t TextureManager::LoadInternal(const std::string& directoryPath, const std::string& fileName)
{
	// 次のディスクリプタヒープの番号が最大サイズを超過していないか確認
	assert(indexNextDescriptorHeap_ < kDescriptorSize);
	// ヒープを取得
	SRV* srvHeap = dxCommon_->GetSRV();
	// 次のディスクリプタヒープ番号の取得
	//uint32_t handle = indexNextDescriptorHeap_;
	uint32_t handle = srvHeap->GetCount();

	MyUtility::Log(std::format("[TextureManager] LoadTexture : file:\"{}\", path:\"{}\"\n", fileName, directoryPath + fileName));

	// テクスチャのコンテナ内に目的のテクスチャがあるかを確認する
	// コンテナ内の最初から最後までに引数のテクスチャがあるかを確認する
	auto it = std::find_if(textures_.begin(), textures_.end(), [&](const auto& texture) {
		// 発見できた場合ファイル名をそのまま返す
		return texture.name == fileName;
		});
	// コンテナ内にテクスチャが存在すればそのハンドルを返す
	if (it != textures_.end())
	{
		// テクスチャハンドルを返す
		handle = static_cast<uint32_t>(std::distance(textures_.begin(), it));
		MyUtility::Log(std::format("[TextureManager] Exist : file:\"{}\", handle: {}\n", fileName, handle));
		return handle;
	}

	// テクスチャをコンテナ内から取得
	Texture& texture = textures_.at(handle);
	texture.name = fileName;

	// 含まれていた場合は .　と / を含めたフルパスを入れる
	std::string fullPath = "resources/" + directoryPath + "/" + fileName;

	// ファイルパスをユニコード文字列に変換する
	wchar_t wfilePath[256];
	MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, wfilePath, _countof(wfilePath));

	// テクスチャ
	DirectX::ScratchImage scratchImg = LoadTexture(fullPath);;
	// メタデータ
	DirectX::TexMetadata metadata = scratchImg.GetMetadata();

	texture.resource_ = CreateTextureResource(metadata);
	UploadTextureData(texture.resource_.Get(), scratchImg);


	//// ミップマップ
	//DirectX::ScratchImage mipChain{};
	//// ミップマップ生成
	//result = GenerateMipMaps(
	//	scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
	//// ミップマップ生成に成功したら
	//if (SUCCEEDED(result)) {
	//	// 生成したミップマップの所有権をテクスチャにを渡す
	//	scratchImg = std::move(mipChain);
	//	// テクスチャのメタデータを取得する
	//	metadata = scratchImg.GetMetadata();
	//}
	//// メタデータのフォーマットをSRGBに変更する
	//metadata.format = MakeSRGB(metadata.format);
	//// メタデータを元にリソースの設定を行う
	//D3D12_RESOURCE_DESC textureResourceDesc{};
	//textureResourceDesc.Width = UINT(metadata.width); // テクスチャ幅
	//textureResourceDesc.Height = UINT(metadata.height); // テクスチャ高さ
	//textureResourceDesc.MipLevels = UINT16(metadata.mipLevels); // mipmapの数
	//textureResourceDesc.DepthOrArraySize = UINT16(metadata.arraySize); // 奥行き or 配列テクスチャの配列数
	//textureResourceDesc.Format = metadata.format; // テクスチャのフォーマット
	//textureResourceDesc.SampleDesc.Count = 1; // サンプリングカウント 1固定
	//textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension); // テクスチャの次元数　普段使っているのは二次元
	//// 利用するヒープの設定を行う
	//D3D12_HEAP_PROPERTIES heapProperties{};
	//heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM; // 細かい設定を行う
	//heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセスが可能
	//heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0; // プロセッサの近くに配置する
	//// テクスチャリソースを生成する
	//result = device_->CreateCommittedResource(
	//	&heapProperties,					// ヒープ設定
	//	D3D12_HEAP_FLAG_NONE,				// Heapの特殊な設定
	//	&textureResourceDesc,				// リソース設定
	//	D3D12_RESOURCE_STATE_GENERIC_READ,  // アップロードヒープに必要な開始状態
	//	nullptr,							// クリアの最適値、今回は使わないのでnullptr
	//	IID_PPV_ARGS(&texture.resource)		// 作成するリソースポインタでへのポインタ
	//);
	//// テクスチャリソースが生成出来たかどうか確認する
	//assert(SUCCEEDED(result));
	//// 全体のミップマップについて設定
	//for (size_t i = 0; i < metadata.mipLevels; i++) {
	//	// ミップマップレベルを設定し、各画像を取得する
	//	const Image* img = scratchImg.GetImage(i, 0, 0);
	//	// テクスチャの転送を行う
	//	result = texture.resource->WriteToSubresource(
	//		UINT(i),
	//		nullptr,			  // 全領域へコピーする
	//		img->pixels,		  // 元データアドレス
	//		(UINT)img->rowPitch,  // 1ラインアドレス
	//		(UINT)img->slicePitch // 1枚サイズ
	//	);
	//	// 転送出来たか確認する
	//	assert(SUCCEEDED(result));
	//}

	// SRVを作成するDescriptorHeapの場所を決める
	texture.cpuDescriptorHandleSRV_ = srvHeap->GetDescriptorHandleIncrementSize(handle);
	GetCPUDescriptorHandle(
		srvHeap->GetHeap(), handle, cIncrementSize_); // CPU
	texture.gpuDescriptorHandleSRV_ = srvHeap->GetGPUHandle();
	GetGPUDescriptorHandle(
		srvHeap->GetHeap(), handle, cIncrementSize_); // GPU

	// テクスチャのリソース設定を取得する
	D3D12_RESOURCE_DESC resourceDesc = texture.resource_->GetDesc();
	// SRVの設定を行う
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = resourceDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャの設定
	srvDesc.Texture2D.MipLevels = (UINT)metadata.mipLevels;

	// SRVの生成を行う
	dxCommon_->GetDevice()->CreateShaderResourceView(
		texture.resource_.Get(),
		&srvDesc,
		texture.cpuDescriptorHandleSRV_
	);

	// 次のディスクリプタヒープ番号を指定
	indexNextDescriptorHeap_++;
	MyUtility::Log(std::format("[TextureManager] Generate : file:\"{}\", handle: {}\n", fileName, handle));
	// カウントを進める
	MyUtility::Log(std::format("[TextureManager] SRV : Index: {}\n", srvHeap->GetCount()));
	srvHeap->Increment();

	// ハンドルを返す
	return handle;
}