#include "RTV.h"

#include "Base/DirectXCommon.h"

void RTV::Initialize()
{
	// スワップチェイン用のため 2 個
	heapSize_ = 2;
	// ディスクリプタ一つのサイズを取得
	kDescriptorSize_ = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	heap_ = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, heapSize_, false);
}
