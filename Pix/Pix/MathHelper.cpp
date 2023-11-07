#include "MathHelper.h"
#include <math.h>

Matrix4 Matrix4::Identity()
{
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::RotationX(float rad)
{
	const float s = sinf(rad);
	const float c = cosf(rad);
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c, s, 0.0f,
		0.0f, -s, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::RotationY(float rad)
{
	const float s = sinf(rad);
	const float c = cosf(rad);
	return Matrix4(
		c, 0.0f, -s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::RotationZ(float rad)
{
	const float s = sinf(rad);
	const float c = cosf(rad);
	return Matrix4(
		c, s, 0.0f, 0.0f,
		-s, c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::Scaling(float s)
{
	return Matrix4(
		s, 0.0f, 0.0f, 0.0f,
		0.0f, s, 0.0f, 0.0f,
		0.0f, 0.0f, s, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::Scaling(const Vec3& s)
{
	return Matrix4(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::Scaling(float sx, float sy, float sz)
{
	return Matrix4(
		sx, 0.0f, 0.0f, 0.0f,
		0.0f, sy, 0.0f, 0.0f,
		0.0f, 0.0f, sz, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
Matrix4 Matrix4::Translation(const Vec3& d)
{
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		d.x, d.y, d.z, 1.0f
	);
}
Matrix4 Matrix4::Translation(float dx, float dy, float dz)
{
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		dx, dy, dz, 1.0f
	);
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

bool MathHelper::CheckEqual(const Matrix4& a, const Matrix4& b)
{
	return CheckEqual(a._11, b._11)
		&& CheckEqual(a._12, b._12)
		&& CheckEqual(a._13, b._13)
		&& CheckEqual(a._14, b._14)
		&& CheckEqual(a._21, b._21)
		&& CheckEqual(a._22, b._22)
		&& CheckEqual(a._23, b._23)
		&& CheckEqual(a._24, b._24)
		&& CheckEqual(a._31, b._31)
		&& CheckEqual(a._32, b._32)
		&& CheckEqual(a._33, b._33)
		&& CheckEqual(a._34, b._34)
		&& CheckEqual(a._41, b._41)
		&& CheckEqual(a._42, b._42)
		&& CheckEqual(a._43, b._43)
		&& CheckEqual(a._44, b._44);
}

Vec3 MathHelper::TransformCoord(const Vec3& v, const Matrix4& m)
{
	const float w = ((v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44));
	const float invW = (w == 1.0f) ? 1.0f : 1.0f / w;
	return {
		((v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (1.0f * m._41)) * invW,
		((v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (1.0f * m._42)) * invW,
		((v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (1.0f * m._43)) * invW
	};
}

Vec3 MathHelper::TransformNormal(const Vec3& n, const Matrix4& m)
{
	return {
		((n.x * m._11) + (n.y * m._21) + (n.z * m._31)),
		((n.x * m._12) + (n.y * m._22) + (n.z * m._32)),
		((n.x * m._13) + (n.y * m._23) + (n.z * m._33))
	};
}

float MathHelper::Determinant(const Matrix4& m)
{
	float det = 0.0f;
	det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return det;
}

Matrix4 MathHelper::Adjoint(const Matrix4& m)
{
	return Matrix4(
		+(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
		+(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
		+(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
		+(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

		+(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
		+(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
		+(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
		+(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
	);
}

Matrix4 MathHelper::Transpose(const Matrix4& m)
{
	return Matrix4(
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44
	);
}

Matrix4 MathHelper::Inverse(const Matrix4& m)
{
	const float determinant = Determinant(m);
	const float invDet = 1.0f / determinant;
	return Adjoint(m) * invDet;
}
