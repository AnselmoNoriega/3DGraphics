#pragma once
#include "Light.h"

class PointLight: public Light
{
public:
	X::Color ComputeLightColor(const Vec3& pos, const Vec3& normal) override;

	void SetPosition(const Vec3& position);
	void SetAttenuation(float constant, float linear, float quadratic);

private:
	Vec3 mPosition;
	float mAttenConst;
	float mAttenLinear;
	float mAttenQuadratic;
};

