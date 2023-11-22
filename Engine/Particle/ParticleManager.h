#pragma once

#include <array>
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include "Particle.h"

class ParticleManager final
{
public:

	static const size_t kDescriptorSize = 256;

public:

	static ParticleManager* GetInstance();

public:

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	void SetGraphicsDescriptorTable(uint32_t rootParameterIndex, uint32_t textureHandle);

public:

	void Initialize(DirectXCommon* dxCommon);

	void Reset();

private:


private:

	std::array<Particle*, kDescriptorSize> textures_;

	uint32_t cIncrementSize_ = 0u;

	uint32_t indexNextDescriptorHeap_ = 0u;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;

	DirectXCommon* dxCommon_ = nullptr;


};