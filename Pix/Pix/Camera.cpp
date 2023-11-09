#include "Camera.h"
#include <math.h>

extern float gResolutionX;
extern float gResolutionY;

Camera* Camera::Get()
{
	static Camera sInstance;
	return &sInstance;
}

void Camera::OnNewFrame()
{
	mPosition = { 0.0f,0.0f,0.0f };
	mDirection = { 0.0f,0.0f,0.0f };
	mNearplane = 0;
}

void Camera::SetPosition(const Vec3& position)
{
	mPosition = position;
}

void Camera::SetDirection(const Vec3& direction)
{
	mDirection = direction;
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearplane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::SetFOV(float fov)
{
	mFov = fov;
}

Matrix4 Camera::GetViewMatrix() const
{
	Vec3 u = { 0.0f, 1.0f, 0.0f };
	const Vec3 l = mDirection;
	const Vec3 r = MathHelper::Normalize(MathHelper::Cross(u, l));
	u = MathHelper::Normalize(MathHelper::Cross(l, r));

	const float dx = -MathHelper::Dot(r, mPosition);
	const float dy = -MathHelper::Dot(u, mPosition);
	const float dz = -MathHelper::Dot(l, mPosition);

	return Matrix4(
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		dx, dy, dz, 1.0
	);
}

Matrix4 Camera::GetProjectionMatrix() const
{
	const float a = gResolutionX / gResolutionY;
	const float d = 1 / tanf(mFov * 0.5f);
	const float zf = mFarPlane;
	const float zn = mNearplane;
	const float q = zf / (zf - zn);

	return Matrix4(
		d / a, 0.0f, 0.0f, 0.0f,
		0.0f,     d, 0.0f, 0.0f,
		0.0f, 0.0f,     q, 1.0f,
		0.0f, 0.0f,-zn * q, 0.0f
	);
}