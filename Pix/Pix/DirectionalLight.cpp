#include "DirectionalLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(const Vec3& pos, const Vec3& normal)
{
	auto camera = Camera::Get();
	auto mm = MaterialManager::Get();

	X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient();

	Vec3 dirToLight = -mDirection;
	float dot = MathHelper::Dot(dirToLight, normal);
	X::Color colorDeffuse = mDiffuse * mm->GetMaterialDiffuse() * dot;

	Vec3 dirToEye = MathHelper::Normalize(camera->GetPosition() - pos);
	Vec3 half = MathHelper::Normalize(dirToLight + dirToEye);
	float fallOff = pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess());
	fallOff = X::Math::Max(fallOff, 0.0f);
	X::Color colorSpecular = mSpecular * mm->GetMaterialSpecular() * fallOff;

	return colorAmbient + colorDeffuse + colorSpecular;
	
}

void DirectionalLight::SetDirection(const Vec3& direction)
{
	mDirection = direction;
}
