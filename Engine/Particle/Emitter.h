#pragma once

#include <memory>
#include <list>

#include "../Math/Math.h"
#include "Particle.h"

/*	エミッターの最小単位
*
*
*
*/


class Emitter
{
public:

	using pList = std::list<Particle>;

	struct EmitterData
	{
		Vector3 translate_;
		Vector3 radius_;
		uint32_t count_;
	};

private:

	EmitterData data_;
	pList particles_;
	bool isActive_;

public:

	void Initialize();
	pList Emit(const Emitter& emitter);
	Particle CreateParticle();

	void Update();

	void Draw();

};