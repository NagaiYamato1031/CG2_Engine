#pragma once
#include <d3d12.h>
#include <wrl.h>

#include <string>

class PSO final
{
public: // メンバ変数

	// グラフィックパイプラインの状態
	Microsoft::WRL::ComPtr<ID3D12PipelineState> state_;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;

public: // メンバ関数

	void Initialize();
};

