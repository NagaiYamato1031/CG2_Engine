#pragma once

#include <vector>

#include "IObject.h"

class ObjectManager final
{
	std::vector<IObject*> objects_;




public:

	static ObjectManager* GetInstance();

public:



private:

	ObjectManager() = default;
	~ObjectManager() = default;
	ObjectManager(const ObjectManager& obj) = delete;
	const ObjectManager& operator=(const ObjectManager& obj) = delete;

};