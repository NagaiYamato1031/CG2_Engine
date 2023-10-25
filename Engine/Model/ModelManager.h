#pragma once
#include <string>
#include <map>
#include <wrl.h>

#include "../Base/DirectXCommon.h"
#include "Model.h"
#include "../PSO/PSO.h"

class ModelManager
{
public:

	static ModelManager* GetInstance();

	void Initialize(DirectXCommon* dxCommon);

	// モデルのロード
	Model::ModelData LoadModel(const std::string& directoryPath, const std::string& fileName);
	// .mtlファイルのロード
	Model::MaterialData LoadMaterial(const std::string& directoryPath, const std::string& fileName);

	void SetPSO();

private:

	void CreatePSO();

private:

	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;

private:

	// モデルデータ
	std::map<std::string, Model::ModelData> modelDatas_;

	// PSO
	std::unique_ptr<PSO> pso_;

	DirectXCommon* dxCommon_ = nullptr;

};