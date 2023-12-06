#pragma once

#include <array>
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include "Particle.h"
#include "../Base/PSO/PSO.h"

// パーティクルをどう扱うか考える
// ・設置するだけのものを一回作る
// ・
//

class ParticleManager final
{
public:

	static const size_t kParticleCategorySize = 16;

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

	void CreatePSO();
	
	void CreateRootSignature();
	
	D3D12_GRAPHICS_PIPELINE_STATE_DESC CreatePipelineStateDesc();

	D3D12_BLEND_DESC CreateBlendDesc();

	D3D12_RASTERIZER_DESC CreateRasterizerDesc();

	D3D12_DEPTH_STENCIL_DESC CreateDepthStencilDesc();

private:

	std::array<Particle*, kParticleCategorySize> textures_;

	uint32_t indexNextParticleCategory_ = 0u;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;

	DirectXCommon* dxCommon_ = nullptr;

	std::unique_ptr<PSO> pso_;

};