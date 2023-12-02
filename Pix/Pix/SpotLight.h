#pragma once
#include "Light.h"

class SpotLight: public Light
{
public:
	X::Color ComputeLightColor(const Vec3& pos, const Vec3& normal) override;

	void SetPosition(const Vec3& position);
	void SetDirection(const Vec3& direction);
	void SetAttenuation(float constant, float linear, float quadratic);
	void SetAngle(float angle);
	void SetDecay(float decay);

private:
	Vec3 mPosition;
	Vec3 mDirection;
	float mAttenConst = -1.0f;
	float mAttenLinear = 0.0f;
	float mAttenQuadratic = 0.0f;
	float mCosAngle = cos(X::Math::kPiByTwo);
	float mDecay = 0.0f;
};

