#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

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
	auto light = std::make_unique<DirectionalLight>();
	light->SetDirection(direction);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::AddPointLight(const Vec3& pos, float constant, float linear, float quadratic)
{
	auto light = std::make_unique<PointLight>();
	light->SetPosition(pos);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	light->SetAttenuation(constant, linear, quadratic);
	mLights.emplace_back(std::move(light));
}

void LightManager::AddSpotLight(const Vec3& pos, const Vec3& direction, float constant, float linear, float quadratic, float angle, float decay)
{
	auto light = std::make_unique<SpotLight>();
	light->SetPosition(pos);
	light->SetDirection(direction);
	light->SetAttenuation(constant, linear, quadratic);
	light->SetAngle(angle);
	light->SetDecay(decay);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
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
