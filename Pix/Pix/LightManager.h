#pragma once
#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

	void OnNewFrame();

	void AddDirectionalLight(const Vec3& direction);
	void AddPointLight(const Vec3& pos, float constant, float linear, float quadratic);

	void SetLightingAmbient(const X::Color& ambient);
	void SetLightingDiffuse(const X::Color& diffuse);
	void SetLightingSpecular(const X::Color& specular);

	X::Color ComputeLightColor(const Vec3& position, const Vec3& normal) const;

private:
	std::vector<std::unique_ptr<Light>> mLights;
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};

