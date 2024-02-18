#pragma once

#include <wrl.h>
#include <d3d12.h>

class PSO final
{
public:

	PSO();
	~PSO();

	Microsoft::WRL::ComPtr<ID3D12PipelineState> state_;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;

};