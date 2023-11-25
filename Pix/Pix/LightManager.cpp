#include "LightManager.h"

LightManager* LightManager::Get()
{
	static LightManager sInstance;
	return &sInstance;
}

void LightManager::OnNewFrame()
{
	mLights.clear();
}

void LightManager::AddDirectionalLight(const Vec3& direction)
{
}

void LightManager::AddPointLight(const Vec3& pos, float constant, float linear, float quadratic)
{
}

void LightManager::SetLightingAmbient(const X::Color& ambient)
{
	mAmbient = ambient;
}

void LightManager::SetLightingDiffuse(const X::Color& diffuse)
{
	mDiffuse = diffuse;
}

void LightManager::SetLightingSpecular(const X::Color& specular)
{
	mSpecular = specular;
}

X::Color LightManager::ComputeLightColor(const Vec3& position, const Vec3& normal) const
{
	if (mLights.empty())
	{
		return X::Colors::White;
	}

	X::Color color = X::Colors::Black;

	for (auto& light : mLights)
	{
		color += light->ComputeLightColor(position, normal);
	}

	return color;

}
