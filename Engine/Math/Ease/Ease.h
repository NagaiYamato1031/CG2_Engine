#pragma once

#include "../Vector/Vector2.h"
#include "../Vector/Vector3.h"

float Lerp(float posA, float posB, float t);
Vector2 Lerp(const Vector2& posA, const Vector2& posB, float t);
Vector3 Lerp(const Vector3& posA, const Vector3& posB, float t);

float OutExpo(float t);
float OutExpo(float posA, float posB, float t);
Vector2 OutExpo(Vector2 posA, Vector2 posB, float t);
Vector3 OutExpo(Vector3 posA, Vector3 posB, float t);
float LerpShortAngle(float a, float b, float t);