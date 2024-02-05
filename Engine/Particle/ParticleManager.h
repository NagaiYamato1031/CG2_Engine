#pragma once

#include <list>
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include "Particle.h"
#include "../Base/DirectXCommon.h"
#include "../Base/PSO/PSO.h"

#include "../Object/ViewProjection.h"

// パーティクルをどう扱うか考える
// ・設置するだけのものを一回作る
// ・
//

class ParticleManager final
{
public:

	// パーティクルのトランスフォーム最大数
	static const size_t kTransformMaxSize_ = 65535;

	static const size_t kParticleMaxSize = 128;

	const char* kTextureName_ = "Particle.png";

public:

	static ParticleManager* GetInstance();

public:

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

public:

	void Initialize(DirectXCommon* dxCommon);

	void Reset();

	void Update();

	void Draw(ViewProjection* viewProjection);

private:

	void CreatePSO();
	
	void CreateRootSignature();
	
	D3D12_GRAPHICS_PIPELINE_STATE_DESC CreatePipelineStateDesc();

	D3D12_BLEND_DESC CreateBlendDesc();

	D3D12_RASTERIZER_DESC CreateRasterizerDesc();

	D3D12_DEPTH_STENCIL_DESC CreateDepthStencilDesc();

private:

	// SRV 用の Heap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;

	DirectXCommon* dxCommon_ = nullptr;

	std::unique_ptr<PSO> pso_;

	std::list<std::unique_ptr<Particle>> particles_;

	uint32_t indexNextParticleCategory_ = 0u;

	uint32_t textureHandle_ = 0u;

};