#include "ObjectManager.h"

ObjectManager* ObjectManager::GetInstance()
{
	static ObjectManager instance;
	return &instance;
}
