#include "SpotLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color SpotLight::ComputeLightColor(const Vec3& pos, const Vec3& normal)
{
	auto camera = Camera::Get();
	auto mm = MaterialManager::Get();

	Vec3 dirToLight = mPosition - pos;
	float distanceLight = MathHelper::Magnitud(dirToLight);
	dirToLight /= distanceLight;

	Vec3 lightDir = -dirToLight;
	float dirDot = MathHelper::Dot(lightDir, mDirection);
	if (dirDot < mCosAngle)
	{
		return 0.0f;
	}
	float spot = std::pow(dirDot, mDecay);
	float atten = spot / (mAttenConst + (mAttenLinear * distanceLight) + (mAttenQuadratic * distanceLight * distanceLight));
	float attenValue = X::Math::Clamp(atten, 0.0f, 1.0f);

	X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient() * attenValue;

	float dot = MathHelper::Dot(dirToLight, normal);
	X::Color colorDeffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * attenValue;

	Vec3 dirToEye = MathHelper::Normalize(camera->GetPosition() - pos);
	Vec3 half = MathHelper::Normalize(dirToLight + dirToEye);
	float fallOff = pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess());
	fallOff = X::Math::Max(fallOff, 0.0f);
	X::Color colorSpecular = mSpecular * mm->GetMaterialSpecular() * fallOff * attenValue;

	return colorAmbient + colorDeffuse + colorSpecular;
}

void SpotLight::SetPosition(const Vec3& position)
{
	mPosition = position;
}

void SpotLight::SetDirection(const Vec3& direction)
{
	mDirection = direction;
}

void SpotLight::SetAttenuation(float constant, float linear, float quadratic)
{
	mAttenConst = constant;
	mAttenLinear = linear;
	mAttenQuadratic = quadratic;
}

void SpotLight::SetAngle(float angle)
{
	mCosAngle = std::cos(angle);
}

void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}
