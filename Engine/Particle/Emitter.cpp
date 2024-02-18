#include "Emitter.h"
#include "../Utility/MyUtility.h"

void Emitter::Initialize()
{
	data_.translate_ = { 0.0f,0.0f,0.0f };
	data_.radius_ = { 1.0f,1.0f,1.0f };
	data_.count_ = 10;
	isActive_ = true;
	particles_.clear();
}

Emitter::pList Emitter::Emit(const Emitter& emitter)
{
	pList particles;
	for (uint32_t i = 0; i < emitter.data_.count_; i++)
	{
		//particles.push_back();
	}

}

Particle Emitter::CreateParticle()
{

}

void Emitter::Update()
{
}

void Emitter::Draw()
{
}
