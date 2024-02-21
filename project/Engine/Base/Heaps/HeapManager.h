#pragma once

#include <memory>

#include "RTV.h"
#include "SRV.h"
#include "DSV.h"

class HeapManager
{
private:

	std::unique_ptr<RTV> rtv_;
	std::unique_ptr<SRV> srv_;
	std::unique_ptr<DSV> dsv_;

public:

	RTV* rtv() { return rtv_.get(); }
	SRV* srv() { return srv_.get(); }
	DSV* dsv() { return dsv_.get(); }

public:
	HeapManager();
	~HeapManager() = default;

private:
	HeapManager(const HeapManager& obj) = delete;
	const HeapManager& operator=(const HeapManager& obj) = delete;

};