#include "./DXC.h"
#include "../../Utility/MyUtility.h"

#include <cassert>
#include <format>

#include <d3d12.h>
#include <d3dcompiler.h>

#pragma comment(lib, "dxcompiler.lib")
#pragma comment(lib, "d3dCompiler.lib")

using namespace Microsoft::WRL;
//
//DXC* DXC::GetInstance()
//{
//	static DXC instance;
//	return &instance;
//}

DXC::DXC()
{
}

void DXC::Initialize()
{
	HRESULT hr = S_FALSE;

	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils_));
	assert(SUCCEEDED(hr));
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler_));
	assert(SUCCEEDED(hr));
	// 現時点で include はしないが、include するための設定を行う
	hr = dxcUtils_->CreateDefaultIncludeHandler(&dxcIncludeHandler_);
	assert(SUCCEEDED(hr));
}

Microsoft::WRL::ComPtr<IDxcBlob> DXC::CompileShader(const std::wstring& filePath, const wchar_t* profile)
{
#pragma region hlsl ファイルを読む

	// これからシェーダーをコンパイルする旨をログに出す
	MyUtility::Log(MyUtility::ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
	// hlsl ファイルを読む
	Microsoft::WRL::ComPtr<IDxcBlobEncoding> shaderSource = nullptr;
	HRESULT hr = dxcUtils_->LoadFile(filePath.c_str(), nullptr, shaderSource.GetAddressOf());
	// 読めなかったら止める
	assert(SUCCEEDED(hr));
	// 読み込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	// UTF8 の文字コードであることを通知
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;

#pragma endregion

#pragma region Compile する

	LPCWSTR arguments[] = {
		filePath.c_str(),			// コンパイル対象の hlsl ファイル名
		L"-E",L"main",				// エントリーポイントの指定。基本的に main 以外にはしない
		L"-T", profile,				// ShaderProfile の設定
		L"-Zi", L"-Qembed_debug",	// デバッグ用の情報を埋め込む
		L"-Od",						// 最適化を外しておく
		L"-Zpr",					// メモリレイアウトは行優先
	};
	// 実際に Shader をコンパイルする
	Microsoft::WRL::ComPtr<IDxcResult> shaderResult = nullptr;
	hr = dxcCompiler_->Compile(
		&shaderSourceBuffer,		// 読み込んだファイル
		arguments,					// コンパイルオプション
		_countof(arguments),		// コンパイルオプションの数
		dxcIncludeHandler_.Get(),	// include が含まれた諸々
		IID_PPV_ARGS(&shaderResult)	// コンパイル結果
	);
	// コンパイルエラーではなく dxc が起動できないなどの致命的な状況
	assert(SUCCEEDED(hr));

#pragma endregion

#pragma region 警告・エラーが出ていないか確認する

	// 警告・エラーが出てたらログに出して止める
	Microsoft::WRL::ComPtr<IDxcBlobUtf8> shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		MyUtility::Log(shaderError->GetStringPointer());
		// 警告・エラーダメ絶対
		assert(false);
	}

#pragma endregion

#pragma region Compile 結果を受け取って返す

	// コンパイル結果から実行用のバイナリ部分を取得
	Microsoft::WRL::ComPtr<IDxcBlob> shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));
	// 成功したログを出す
	MyUtility::Log(MyUtility::ConvertString(std::format(L"Compile Succeeded, path:{}, profile:{}\n", filePath, profile)));
	// もう使わないリソースを解放
	//shaderSource->Release();
	//shaderResult->Release();
	// 実行用のバイナリを返却
	return shaderBlob;

#pragma endregion

}
