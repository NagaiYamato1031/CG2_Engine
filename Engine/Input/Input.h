#pragma once

#include <Windows.h>
#include <cassert>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>

class WinApp;

class Input final {
public: // メンバ関数

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Input* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winapp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

public: // キー入力取得

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>押した瞬間か</returns>
	bool TriggerKey(BYTE keyNumber);
	
	/// <summary>
	/// キーのリリースをチェック
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>離した瞬間か</returns>
	bool ReleaseKey(BYTE keyNumber);

private: // コピー禁止
	Input() = default;
	~Input() = default;
	Input(const Input& obj) = delete;
	const Input& operator=(const Input& obj) = delete;


private: // メンバ変数

	// namespace 省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	BYTE preKey[256] = {};

	WinApp* winApp_ = nullptr;
};