#pragma once
#include "MathHelper.h"

class Camera
{
public:
	static Camera* Get();

	void OnNewFrame();
	void SetPosition(const Vec3& direction);
	void SetDirection(const Vec3& direction);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFOV(float fov);
	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;

	const Vec3& GetPosition() const { return mPosition; }
	const Vec3& GetDiraction() const { return mDirection; }
private:
	Vec3 mPosition;
	Vec3 mDirection;
	float mNearplane;
	float mFarPlane;
	float mFov;
};

