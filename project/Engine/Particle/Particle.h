#pragma once

#include "../Math/Math.h"
#include "../Object/WorldTransform.h"

/*	パーティクルの最小単位
*
*
*
*/


class Particle
{
public:

	struct TransformMatrix
	{
		Matrix4x4 matWVP;
		Matrix4x4 matMorld;
	};

	struct ParticleData
	{
		Vector3 translate_;
		Vector3 velocity_;
		Vector4 color_;
		uint32_t textureHandle_;
	};

private:



public:

	void Initialize();

	void Update();

	void Draw();

};