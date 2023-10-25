#pragma once
#include <string>
#include <vector>
#include <wrl.h>

#include "../Math/Math.h"
#include "../Object/3D/WorldTransform.h"

class Model
{
public:
	struct VertexData
	{
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

	struct ConstBufferData {
		Vector4 color;
		Matrix4x4 mat;
		Matrix4x4 world;
		int32_t enableLighting;
		Matrix4x4 uvTransform;
	};

	struct MaterialData
	{
		std::string textureFilePath;
	};

	struct ModelData
	{
		std::vector<VertexData> vertices;
		MaterialData material;
	};

public:

	static void StaticInitialize();

	static void PreDraw();

	static void PostDraw();

	static Model* Create(WorldTransform* worldTransform, const Vector4& color, const std::string& fileName, const std::string& directoryPath = "./Resources");
	static Model* Create(const Vector4& color, const std::string& fileName, const std::string& directoryPath = "./Resources");
	static Model* Create(const std::string& fileName, const std::string& directoryPath = "./Resources");


public:

	Model();
	Model(const Vector4& color);
	Model(WorldTransform* transform, const Vector4& color = { 1.0f,1.0f,1.0f,1.0f });

	void Initialize(const std::string& directoryPath, const std::string& fileName);

	void Draw();
	void Draw(WorldTransform* transform);

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff_;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;

	VertexData* vertMap_ = nullptr;
	ConstBufferData* constMap_ = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vbView_{};

	ModelData modelData_;

	WorldTransform* transform_;
	WorldTransform uvTransform_;

	Matrix4x4 matWorld_{};
	uint32_t textureHandle_ = 0u;
	Vector2 texBase_ = { 0.0f, 0.0f };
	Vector2 texSize_ = { 100.0f, 100.0f };

	D3D12_RESOURCE_DESC resourceDesc_;

	Vector4 color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

private:

	void TransferVertices();

};