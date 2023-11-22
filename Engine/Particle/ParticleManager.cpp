#include "ParticleManager.h"
#include "../Utility/MyUtility.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

#include "../../externals/DirectXTex/d3dx12.h"
#include "../Base/DirectXCommon.h"

using namespace Microsoft::WRL;


ParticleManager* ParticleManager::GetInstance()
{
	static ParticleManager ParticleManager;
	return &ParticleManager;
}

D3D12_CPU_DESCRIPTOR_HANDLE ParticleManager::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index) {
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += static_cast<UINT64>(descriptorSize) * static_cast<UINT64>(index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE ParticleManager::GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index) {
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += static_cast<UINT64>(descriptorSize) * static_cast<UINT64>(index);
	return handleGPU;
}


void ParticleManager::SetGraphicsDescriptorTable(uint32_t rootParameterIndex, uint32_t textureHandle)
{
	// テクスチャハンドルがテクスチャサイズを超過していないか確認する
	assert(textureHandle < textures_.size());

	// ディスクリプタヒープを取得
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	// 取得したディスクリプタヒープをコマンドリストにセット
	dxCommon_->GetCommandList()->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	rootParameterIndex;
}


void ParticleManager::Initialize(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	dxCommon_ = dxCommon;
	cIncrementSize_ = dxCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	Reset();
}

void ParticleManager::Reset()
{
	HRESULT hr = S_FALSE;

	// ディスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; // タイプ設定
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // フラッグ
	descHeapDesc.NumDescriptors = kDescriptorSize;
	// ディスクリプタヒープの生成
	hr = dxCommon_->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descriptorHeap_));
	// 生成出来ているか確認
	assert(SUCCEEDED(hr));

	// 次のディスクリプタヒープの番号を指定
	indexNextDescriptorHeap_ = 0;

	// 全てのテクスチャをリセットする
	for (size_t i = 0; i < kDescriptorSize; i++) {
		//textures_[i].resource_.Reset(); // リソース
		//textures_[i].cpuDescriptorHandleSRV_.ptr = 0; // ディスクリプタハンドル（CPU）
		//textures_[i].gpuDescriptorHandleSRV_.ptr = 0; // ディスクリプタハンドル（GPU）
		//textures_[i].name.clear(); // ファイル名
	}
}