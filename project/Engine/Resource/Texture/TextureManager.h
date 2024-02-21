#pragma once

#include <array>
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include "../../../externals/DirectXTex/DirectXTex.h"

class DirectXCommon;

class TextureManager
{
public:

	static const size_t kDescriptorSize = 128;

	struct Texture {
		Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandleSRV_;
		D3D12_GPU_DESCRIPTOR_HANDLE gpuDescriptorHandleSRV_;
		std::string name;
	};

private:

	std::array<Texture, kDescriptorSize> textures_;

	// ヒープの一つの大きさ
	uint32_t cIncrementSize_ = 0u;

	// ImGui が 0 番目を使っているので 1 から
	uint32_t indexNextDescriptorHeap_ = 1u;

	//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;

	DirectXCommon* dxCommon_ = nullptr;

public:

	/// <summary>
	/// テクスチャを読み込む
	/// "Resources/" : "*.png"
	/// </summary>
	/// <param name="fileName">*.{png,jpg}</param>
	/// <returns></returns>
	static uint32_t Load(const std::string& fileName);
	/// <summary>
	/// テクスチャを読み込む
	/// "*/" : "*.png"
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="fileName"></param>
	/// <returns></returns>
	static uint32_t Load(const std::string& directoryPath, const std::string& fileName);

	static TextureManager* GetInstance();

public:

	// CPU 側のディスクリプタのハンドル
	// インクリメント用のサイズとインデックスが逆で入れてる可能性大
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	// GPU 側のディスクリプタのハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	const std::string& GetTextureName(uint32_t textureHandle);

	const D3D12_RESOURCE_DESC GetResourceDesc(uint32_t textureHandle);

	const D3D12_GPU_DESCRIPTOR_HANDLE GetTextureGPUHandle(uint32_t texturehandle);

	void SetGraphicsDescriptorTable(uint32_t rootParameterIndex, uint32_t textureHandle);

public:

	void Initialize(DirectXCommon* dxCommon);

	void Reset();

private:

	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata);

	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	ID3D12Resource* UploadTextureDataEx(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	uint32_t LoadInternal(const std::string& directoryPath, const std::string& fileName);

};