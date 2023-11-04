#include "MathHelper.h"
#include <math.h>

Matrix4 Matrix4::Identity()
{

}

Matrix4 Matrix4::RotationX(float rad)
{

}

Matrix4 Matrix4::RotationY(float rad)
{

}

Matrix4 Matrix4::RotationZ(float rad)
{

}

Matrix4 Matrix4::Scaling(const Vector3& s)
{

}

Matrix4 Matrix4::Scaling(float sx, float sy, float sz)
{

}

Matrix4 Matrix4::Scaling(float s)
{

}

Matrix4 Matrix4::Translation(const Vector3& d)
{

}

Matrix4 Matrix4::Translation(float dx, float dy, float dz)
{

}

float MathHelper::MagnitudSqrd(const Vec2& v)
{
	return (v.x * v.x) + (v.y * v.y);
}

float MathHelper::MagnitudSqrd(const Vec3& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float MathHelper::Magnitud(const Vec2& v)
{
	return sqrtf(MagnitudSqrd(v));
}

float MathHelper::Magnitud(const Vec3& v)
{
	return sqrtf(MagnitudSqrd(v));
}

Vec2 MathHelper::Normalize(const Vec2& v)
{
	return v / Magnitud(v);
}

Vec3 MathHelper::Normalize(const Vec3& v)
{
	return v / Magnitud(v);
}

float MathHelper::Dot(const Vec2& v, const Vec2& b)
{
	return (v.x * b.x) + (v.y * b.y);
}

float MathHelper::Dot(const Vec3& v, const Vec3& b)
{
	return (v.x * b.x) + (v.y * b.y) + (v.z * b.z);
}

Vec3 MathHelper::Cross(const Vec3& v, const Vec3& b)
{
	return Vec3(
		v.y * b.z - b.y * v.z,
		b.x * v.z - v.x * b.z,
		v.x * b.y - b.x * v.y);

	//[][][]
	//[][][] i, -j, k
}

float MathHelper::Lerp(const float& v, const float& b, float t)
{
	return v + (b - v) * t;
}

Vec2 MathHelper::Lerp(const Vec2& v, const Vec2& b, float t)
{
	return { Lerp(v.x, b.x, t), Lerp(v.y, b.y, t) };
}

Vec3 MathHelper::Lerp(const Vec3& v, const Vec3& b, float t)
{
	return { Lerp(v.x, b.x, t), Lerp(v.y, b.y, t), Lerp(v.z, b.z, t) };
}

bool MathHelper::CheckEqual(float a, float b)
{
	return fabs(a - b) < 0.001f;
}

bool MathHelper::CheckEqual(const Vec2& a, const Vec2& b)
{
	return CheckEqual(a.x, b.x) && CheckEqual(a.y, b.y);
}

bool MathHelper::CheckEqual(const Vec3& a, const Vec3& b)
{
	return CheckEqual(a.x, b.x) && CheckEqual(a.y, b.y) && CheckEqual(a.z, b.z);
}

Vec3 MathHelper::TransformCoord(const Vec3& v, const Matrix4& m)
{
	return Vec3();
}

Vec3 MathHelper::TransformNormal(const Vec3& n, const Matrix4& m)
{
	return Vec3();
}

float MathHelper::Determinant(const Matrix4& m)
{
	return 0.0f;
}

float MathHelper::Adjoint(const Matrix4& m)
{
	return 0.0f;
}

float MathHelper::Transpose(const Matrix4& m)
{
	return 0.0f;
}

float MathHelper::Inverse(const Matrix4& m)
{
	return 0.0f;
}
