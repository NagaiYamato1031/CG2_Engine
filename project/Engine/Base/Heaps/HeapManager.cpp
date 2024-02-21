#include "HeapManager.h"

HeapManager::HeapManager()
{
	rtv_ = std::make_unique<RTV>();
	rtv_->Initialize();
	srv_ = std::make_unique<SRV>();
	srv_->Initialize();
	dsv_ = std::make_unique<DSV>();
	dsv_->Initialize();
}
