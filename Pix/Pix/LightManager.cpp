#include "LightManager.h"

LightManager* LightManager::Get()
{
	static LightManager sInstance;
	return &sInstance;
}

void LightManager::OnNewFrame()
{
}

void LightManager::AddDirectionalLight(const Vec3& direction)
{
}

void LightManager::AddPointLight(const Vec3& pos, float constant, float linear, float quadratic)
{
}

void LightManager::SetLightingAmbient(const X::Color& ambient)
{
}

void LightManager::SetLightingDiffuse(const X::Color& diffuse)
{
}

void LightManager::SetLightingSpecular(const X::Color& specular)
{
}

X::Color LightManager::ComputeLightColor(const Vec3& position, const Vec3& normal) const
{
	return X::Color();
}
