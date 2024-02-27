#pragma once

#include <memory>
#include <wrl.h>
#include <d3d12.h>

#include "Math/Math.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Base/DirectXCommon.h"
#include "Base/PSO/PSO.h"

class Object3d
{
public:

	struct TransformaionMatrix
	{
		Matrix4x4 matWVP_;
		Matrix4x4 matWorld_;
	};

public:

	void Initialize();

private:

	void CreateResource();

private:

	static DirectXCommon* sDXCommon_;
	static std::unique_ptr<PSO> sPSO_;

private:


	Microsoft::WRL::ComPtr<ID3D12Resource> transformResource_;

	TransformaionMatrix* transformData_ = nullptr;


};

