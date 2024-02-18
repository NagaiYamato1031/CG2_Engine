#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <array>
#include <vector>

#include <Xinput.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>

class WinApp;

class Input final {
public:	// サブクラス

	enum class PadType {
		DirectInput,
		XInput,
	};

	// variantがC++17から
	union State {
		XINPUT_STATE xInput_;
		DIJOYSTATE2 directInput_;
	};

	struct Joystick
	{
		Microsoft::WRL::ComPtr<IDirectInputDevice8> device_;
		int32_t deadZoneL_;
		int32_t deadZoneR_;
		PadType type_;
		State state_;
		State statePre_;
	};


private: // メンバ変数

	// namespace 省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirectInput8> directInput_;
	ComPtr<IDirectInputDevice8> keyboard_;
	// ジョイスティック状態取得
	std::vector<Joystick> devJoysticks_;
	BYTE key_[256] = {};
	BYTE preKey_[256] = {};

	WinApp* winApp_ = nullptr;

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


	/// <summary>
	/// 現在のジョイスティック状態を取得する
	/// </summary>
	/// <param name="stickNo">ジョイスティック番号</param>
	/// <param name="out">現在のジョイスティック状態</param>
	/// <returns>正しく取得できたか</returns>
	bool GetJoystickState(int32_t stickNo, DIJOYSTATE2& out) const;


	/// <summary>
	/// 現在のジョイスティック状態を取得する
	/// </summary>
	/// <param name="stickNo">ジョイスティック番号</param>
	/// <param name="out">現在のジョイスティック状態</param>
	/// <returns>正しく取得できたか</returns>
	bool GetJoystickState(int32_t stickNo, XINPUT_STATE& out) const;


	/// <summary>
	/// デッドゾーンを設定する
	/// </summary>
	/// <param name="stickNo">ジョイスティック番号</param>
	/// <param name="deadZoneL">デッドゾーン左スティック 0~32768</param>
	/// <param name="deadZoneR">デッドゾーン右スティック 0~32768</param>
	/// <returns>正しく取得できたか</returns>
	void SetJoystickDeadZone(int32_t stickNo, int32_t deadZoneL, int32_t deadZoneR);

	/// <summary>
	/// 接続されているジョイスティック数を取得する
	/// </summary>
	/// <returns>接続されているジョイスティック数</returns>
	size_t GetNumberOfJoysticks();

private: // コピー禁止
	Input() = default;
	~Input() = default;
	Input(const Input& obj) = delete;
	const Input& operator=(const Input& obj) = delete;

private:

	/// <summary>
	/// ジョイスティックのコールバック取得関数
	/// </summary>
	/// <param name="pdidInstance">インスタンス</param>
	/// <param name="pContext">コンテキスト</param>
	/// <returns>コールバックジョイスティック</returns>
	static BOOL CALLBACK
		EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext) noexcept;

	/// <summary>
	/// ジョイスティックの初期設定関数
	/// </summary>
	void SetupJoysticks();

};