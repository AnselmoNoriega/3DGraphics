#pragma once

#include "Vector2.h"
#include "Vector3.h"

class MathHelper
{
public:
	static float MagnitudSqrd(const Vec2& v);
	static float MagnitudSqrd(const Vec3& v);
	static float Magnitud(const Vec2& v);
	static float Magnitud(const Vec3& v);
	static Vec2 Normalize(const Vec2& v);
	static Vec3 Normalize(const Vec3& v);
	static float Dot(const Vec2& v, const Vec2& b);
	static float Dot(const Vec3& v, const Vec3& b);
	static Vec3 Cross(const Vec3& v, const Vec3& b);
};
