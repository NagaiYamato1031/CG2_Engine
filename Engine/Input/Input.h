#pragma once

#include <Windows.h>
#include <cassert>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>

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
	void Initialize(HINSTANCE hInstance, HWND hwnd);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

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

};