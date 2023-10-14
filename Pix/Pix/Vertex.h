#pragma once
#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
	Vec3 pos;
	X::Color color;
};

inline static Vec3 LerpPos(const Vec3& a, const Vec3& b, float t)
{
	return MathHelper::Lerp(a, b, t);
}

inline static X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
	return { MathHelper::Lerp(a.r, b.r, t),
		     MathHelper::Lerp(a.g, b.g, t),
		     MathHelper::Lerp(a.b, b.b, t),
		     MathHelper::Lerp(a.a, b.a, t) };
}

inline static Vertex LerpVertex(const Vertex& a, const Vertex& b, float t)
{
	Vertex ret;
	ret.pos = LerpPos(a.pos, b.pos, t);
	ret.color = LerpColor(a.color, a.color, t);
	return ret;
}