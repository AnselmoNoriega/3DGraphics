#pragma once
#include "MathHelper.h"
#include <XEngine.h>

class Light
{
public:
	virtual ~Light() = default;

	virtual X::Color ComputeLightColor(const Vec3& pos, const Vec3& normal) = 0;

	void SetAmbient(const X::Color& ambient) { mAmbient = ambient; }
	void SetDiffuse(const X::Color& diffuse) { mDiffuse = diffuse; }
	void SetSpecular(const X::Color& specular) { mSpecular = specular; }

protected:
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;


};

