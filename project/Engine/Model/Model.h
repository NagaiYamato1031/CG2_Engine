#pragma once

#include <vector>
#include <string>
#include <memory>
#include <wrl.h>
#include <d3d12.h>

#include "../Math/Math.h"
#include "../Object/WorldTransform.h"
#include "../Object/ViewProjection.h"

class DirectXCommon;
class PSO;


class Model
{
public:

	struct VertexData
	{
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

	struct MaterialData
	{
		std::string textureFilePath;
		uint32_t textureHandle_;
	};

	struct ModelData
	{
		std::vector<VertexData> vertices;
		MaterialData material;
	};

	struct TransformaionMatrix
	{
		Matrix4x4 matWVP_;
		Matrix4x4 matWorld_;
	};

public:

	static void StaticInitialize(DirectXCommon* dxCommon);

	static Model* CreateOBJ(const std::string& directoryPath, const std::string& fileName);

	static void PreDraw();

	static void PostDraw();

private:

	static MaterialData LoadMaterialTemplateFile(const std::string& directotyPath, const std::string& filename);

	static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	static void CreatePSO();

	static D3D12_GRAPHICS_PIPELINE_STATE_DESC CreatePipelineStateDesc();

	static void CreateRootSignature();

	//static D3D12_INPUT_LAYOUT_DESC CreateInputLayoutDesc();

	static D3D12_BLEND_DESC CreateBlendDesc();

	static D3D12_RASTERIZER_DESC CreateRasterizerDesc();

	static D3D12_DEPTH_STENCIL_DESC CreateDepthStencilDesc();

public:

	void Initialize();

	void Draw(WorldTransform* worldTransform);
	void Draw(WorldTransform* worldTransform, ViewProjection* viewProjection);
	void Draw(uint32_t textureHandle);

	void SetTexture(uint32_t texture) { modelData_.material.textureHandle_ = texture; }

private:

	void CreateResource();

private:

	static DirectXCommon* sDXCommon_;
	static std::unique_ptr<PSO> sPSO_;

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;

	//Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_;

	Microsoft::WRL::ComPtr<ID3D12Resource> transformResource_;

	D3D12_VERTEX_BUFFER_VIEW vbView_;

	//D3D12_INDEX_BUFFER_VIEW ibView_;

	VertexData* vertexData_ = nullptr;

	TransformaionMatrix* transformData_ = nullptr;

	ModelData modelData_;

};

