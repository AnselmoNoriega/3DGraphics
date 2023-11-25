#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	X::Color ComputeLightColor(const Vec3& pos, const Vec3& normal) override;
	void SetDirection(const Vec3& direction);

private:
	Vec3 mDirection;

};

