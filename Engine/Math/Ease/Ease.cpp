#include "Ease.h"

#include <cmath>
#include <numbers>

float Lerp(float posA, float posB, float t)
{
	return (1.0f - t) * posA + t * posB;
}

Vector2 Lerp(const Vector2& posA, const Vector2& posB, float t)
{
	return (1.0f - t) * posA + t * posB;
}

Vector3 Lerp(const Vector3& posA, const Vector3& posB, float t)
{
	return (1.0f - t) * posA + t * posB;
}

float OutExpo(float t)
{
	return t == 1.0f ? 1.0f : 1.0f - std::powf(2.0f, -10.0f * t);
}

float OutExpo(float posA, float posB, float t)
{
	return posA + (posB - posA) * OutExpo(t);
}

Vector2 OutExpo(Vector2 posA, Vector2 posB, float t)
{
	return posA + (posB - posA) * OutExpo(t);
}

Vector3 OutExpo(Vector3 posA, Vector3 posB, float t)
{
	return posA + (posB - posA) * OutExpo(t);
}

float LerpShortAngle(float a, float b, float t)
{
	float diff = b - a;
	float pi = static_cast<float>(std::numbers::pi);

	diff = std::fmod(diff, pi * 2.0f);

	if (diff <= -pi)
	{
		diff += 2 * pi;
	}
	else if (pi <= diff)
	{
		diff -= 2 * pi;
	}

	return a + diff * t;

}
