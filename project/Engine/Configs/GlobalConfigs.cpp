#include "GlobalConfigs.h"

#include <Windows.h>
#include <fstream>
#ifdef _DEBUG

#include <imgui.h>

#endif

#include <json.hpp>

GlobalConfigs* GlobalConfigs::GetInstance() {
	static GlobalConfigs instance;
	return &instance;
}

void GlobalConfigs::Update() {
#ifdef _DEBUG


	if (!ImGui::Begin("Global Configs", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar()) {
		return;
	}

	// 各グループについて
	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end();
	     ++itGroup) {
		// グループ名を取得
		const std::string& groupName = itGroup->first;
		// グループの参照を取得
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str())) {
			continue;
		}

		// 各項目について
		for (std::map<std::string, Item>::iterator itItem = group.begin();
		     itItem != group.end(); ++itItem) {
			// 項目名を取得
			const std::string& itemName = itItem->first;
			// 項目の参照を取得
			Item& item = itItem->second;

			// int32_t 型の値を保持していれば
			if (std::holds_alternative<int32_t>(item)) {
				int32_t* ptr = std::get_if<int32_t>(&item);
				ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
			}
			// float 型の値を保持していれば
			if (std::holds_alternative<float>(item)) {
				float* ptr = std::get_if<float>(&item);
				ImGui::SliderFloat(itemName.c_str(), ptr, -10.0f, 10.0f);
			}
			// Vector3 型の値を保持していれば
			if (std::holds_alternative<Vector3>(item)) {
				Vector3* ptr = std::get_if<Vector3>(&item);
				ImGui::SliderFloat3(itemName.c_str(), &ptr->x, -10.0f, 10.0f);
			}
		}

		ImGui::Text("\n");

		if (ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = std::format("{}.json saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalConfigs", 0);
		}

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();
	ImGui::End();

#endif // _DEBUG
}

void GlobalConfigs::CreateGroup(const std::string& groupName) {
	// 指定のオブジェクトが無ければ追加する
	datas_[groupName];
}

void GlobalConfigs::SetValue(const std::string& groupName, const std::string& key, int32_t value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい高極のデータを設定
	Item newItem{};
	newItem = value;
	// 設定した項目を std::map に追加
	group[key] = newItem;
}
void GlobalConfigs::SetValue(const std::string& groupName, const std::string& key, float value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい高極のデータを設定
	Item newItem{};
	newItem = value;
	// 設定した項目を std::map に追加
	group[key] = newItem;
}
void GlobalConfigs::SetValue(const std::string& groupName, const std::string& key, Vector3 value) {
	// グループの参照を取得
	Group& group = datas_[groupName];
	// 新しい高極のデータを設定
	Item newItem{};
	newItem = value;
	// 設定した項目を std::map に追加
	group[key] = newItem;
}

void GlobalConfigs::AddItem(const std::string& groupName, const std::string& key, int32_t value) {
	// グループを検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());

	// 項目が未登録なら
	if (!datas_[groupName].contains(key)) {
		SetValue(groupName, key, value);
	}
}
void GlobalConfigs::AddItem(const std::string& groupName, const std::string& key, float value) {
	// グループを検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());

	// 項目が未登録なら
	if (!datas_[groupName].contains(key)) {
		SetValue(groupName, key, value);
	}
}
void GlobalConfigs::AddItem(const std::string& groupName, const std::string& key, Vector3 value) {
	// グループを検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());

	// 項目が未登録なら
	if (!datas_[groupName].contains(key)) {
		SetValue(groupName, key, value);
	}
}

int32_t GlobalConfigs::GetIntValue(const std::string& groupName, const std::string& key) const {
	// グループを検索
	std::map<std::string, Group>::const_iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());
	// グループの参照を取得
	const Group& group = itGroup->second;

	assert(group.contains(key));

	return std::get<int32_t>(group.find(key)->second);
}
float GlobalConfigs::GetFloatValue(const std::string& groupName, const std::string& key) const {
	// グループを検索
	std::map<std::string, Group>::const_iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());
	// グループの参照を取得
	const Group& group = itGroup->second;

	assert(group.contains(key));

	return std::get<float>(group.find(key)->second);
}
Vector3 GlobalConfigs::GetVector3Value(const std::string& groupName, const std::string& key) const {
	// グループを検索
	std::map<std::string, Group>::const_iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());
	// グループの参照を取得
	const Group& group = itGroup->second;

	assert(group.contains(key));

	return std::get<Vector3>(group.find(key)->second);
}

void GlobalConfigs::SaveFile(const std::string& groupName) {
	// グループを検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());

	nlohmann::json root;

	root = nlohmann::json::object();

	root[groupName] = nlohmann::json::object();

	for (std::map<std::string, Item>::iterator itItem = itGroup->second.begin();
	     itItem != itGroup->second.end(); ++itItem) {
		// 項目名を取得
		const std::string& itemName = itItem->first;
		// 項目の参照を取得
		Item& item = itItem->second;

		// int32_t 型の値を保持して居れば
		if (std::holds_alternative<int32_t>(item)) {
			// int32_t 型の値を登録
			root[groupName][itemName] = std::get<int32_t>(item);
		}

		// float 型の値を保持して居れば
		else if (std::holds_alternative<float>(item)) {
			// float 型の値を登録
			root[groupName][itemName] = std::get<float>(item);
		}

		// Vector3 型の値を保持して居れば
		else if (std::holds_alternative<Vector3>(item)) {
			// float 型の json 配列登録
			Vector3 value = std::get<Vector3>(item);
			root[groupName][itemName] = nlohmann::json::array({value.x, value.y, value.z});
		}
	}

	// ディレクトリが無ければ作成する
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		std::filesystem::create_directories(kDirectoryPath);
	}

	// 書き込む JSON ファイルのフルパスを合成する
	std::string filePath = kDirectoryPath + groupName + ".json";
	// 書き込み用ファイルストリーム
	std::ofstream ofs;
	// ファイルを書き込み用に開く
	ofs.open(filePath);

	// ファイルオープン失敗したか
	if (ofs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GlobalConfigs", 0);
		assert(0);
		return;
	}

	// ファイルに json 文字列を書き込む(インデント幅 4)
	ofs << std::setw(4) << root << std::endl;
	// ファイルを閉じる
	ofs.close();
}

void GlobalConfigs::LoadFiles() {
	// ディレクトリが無ければ終了する
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		return;
	}

	std::filesystem::directory_iterator dir_it(kDirectoryPath);
	for (const std::filesystem::directory_entry& entry : dir_it) {
		// ファイルパスを取得
		const std::filesystem::path& filePath = entry.path();

		// ファイル拡張子を取得
		std::string extension = filePath.extension().string();
		// .json ファイル以外はスキップ
		if (extension.compare(".json") != 0) {
			continue;
		}

		// ファイル読み込み
		LoadFile(filePath.stem().string());
	}
}

void GlobalConfigs::LoadFile(const std::string& groupName) {
	// ディレクトリが無ければ終了する
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		return;
	}

	// 読み込む JSON ファイルのフルパスを合成する
	std::string filePath = kDirectoryPath + groupName + ".json";
	// 読み込み用ファイルストリーム
	std::ifstream ifs;
	// ファイルを読み込み用に開く
	ifs.open(filePath);

	// ファイルオープンを失敗したか
	if (ifs.fail()) {
		std::string message = "Failed open data file for read.";
		MessageBoxA(nullptr, message.c_str(), "GlobalConfigs", 0);
		assert(0);
		return;
	}

	nlohmann::json root;

	// json 文字列から json のデータ構造に展開
	ifs >> root;
	// ファイルを閉じる
	ifs.close();

	// グループを検索
	nlohmann::json::iterator itGroup = root.find(groupName);

	// 未登録チェック
	assert(itGroup != root.end());

	// 各アイテムについて
	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {

		// アイテム名を取得
		const std::string& itemName = itItem.key();

		// int32_t 型の値を保持していれば
		if (itItem->is_number_integer()) {
			// int32_t 型の値を登録
			int32_t value = itItem->get<int32_t>();
			SetValue(groupName, itemName, value);
		}

		// float 型の値を保持していれば
		else if (itItem->is_number_float()) {
			// float 型の値を登録
			double value = itItem->get<double>();
			SetValue(groupName, itemName, static_cast<float>(value));
		}

		// 要素数 3 の配列であれば
		else if (itItem->is_array() && itItem->size() == 3) {
			// float 型の json 配列登録
			Vector3 value = {itItem->at(0), itItem->at(1), itItem->at(2)};
			SetValue(groupName, itemName, value);
		}
	}
}