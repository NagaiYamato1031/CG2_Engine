#pragma once
#include <map>
#include <string>
#include <variant>

#include "../Math/Math.h"

using Item = std::variant<int32_t,float,Vector3>;

using Group = std::map<std::string,Item>;

//// 項目
//struct Item {
//	// 項目の値
//	std::variant<int32_t, float, Vector3> value;
//};
//
//// グループ
//struct Group {
//	std::map<std::string, Item> items;
//};

class GlobalConfigs {
public:
	static GlobalConfigs* GetInstance();

	// 毎フレーム更新
	void Update();

	/// <summary>
	/// グループの作成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);

	// 値の追加
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	void SetValue(const std::string& groupName, const std::string& key, float value);
	void SetValue(const std::string& groupName, const std::string& key, Vector3 value);

	// 項目の追加
	void AddItem(const std::string& groupName, const std::string& key, int32_t value);
	void AddItem(const std::string& groupName, const std::string& key, float value);
	void AddItem(const std::string& groupName, const std::string& key, Vector3 value);

	// 値の取得
	int32_t GetIntValue(const std::string& groupName, const std::string& key) const;
	float GetFloatValue(const std::string& groupName, const std::string& key) const;
	Vector3 GetVector3Value(const std::string& groupName, const std::string& key) const;

	// グローバル変数の保存先ファイルパス
	const std::string kDirectoryPath = "Resources/GlobalConfigs/";

	/// <summary>
	/// ファイルに書き出し
	/// </summary>
	/// <param name="groupName"></param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// ディレクトリの全ファイル読み込み
	/// </summary>
	void LoadFiles();

	/// <summary>
	/// ファイルから読み込む
	/// </summary>
	/// <param name="groupName"></param>
	void LoadFile(const std::string& groupName);

private:
	GlobalConfigs() = default;
	~GlobalConfigs() = default;
	GlobalConfigs(const GlobalConfigs& obj) = delete;
	const GlobalConfigs& operator=(const GlobalConfigs& obj) = delete;

	// 全データ
	std::map<std::string, Group> datas_;
};
