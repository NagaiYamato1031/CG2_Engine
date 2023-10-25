#pragma once
#include <dxgi.h>
#include <dxcapi.h>
#include <wrl.h>

#include <string>

class DXC
{
public: // メンバ関数
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns></returns>
	//static DXC* GetInstance();

	DXC();
	~DXC() = default;

	void Initialize();

public: // メンバ関数

	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(const std::wstring& filePath, const wchar_t* profile);

private: // メンバ変数

	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils_;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler_;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> dxcIncludeHandler_;

private: // 非公開のメンバ関数
	DXC(const DXC&) = delete;
	const DXC& operator=(const DXC&) = delete;

};

