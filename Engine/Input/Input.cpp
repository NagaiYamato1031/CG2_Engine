#include "Input.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}

void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT hr;
	// DirectInput のインスタンス作成
	//ComPtr<IDirectInput8> directInput = nullptr;
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(hr));
	// キーボードデバイス生成
	//ComPtr<IDirectInputDevice8> keyboard;
	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(hr));
	// 入力データ形式のセット
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(hr));
	// 排他制御レベルのセット
	hr = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(hr));
}

void Input::Update()
{
	// キーボード情報の取得開始
	keyboard->Acquire();
	// 全キーの入力情報を取得する
	BYTE key[256] = {};
	keyboard->GetDeviceState(sizeof(key), key);

}
