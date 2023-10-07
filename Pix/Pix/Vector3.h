#pragma once

struct Vec3
{
	float x, y, z;

	Vec3() : x(0.0f), y(0.0f) , z(0.0f){};
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {};

	Vec3 operator-() const { return { -x, -y, -z }; }
	Vec3 operator+(const Vec3& b) const { return { x + b.x, y + b.y, z + b.z }; }
	Vec3 operator-(const Vec3& b) const { return { x - b.x, y - b.y, z - b.z }; }
	Vec3 operator*(const float& b) const { return { x * b, y * b, z * b }; }
	Vec3 operator/(const float& b) const { return { x / b, y / b, z / b }; }

	Vec3 operator+=(const Vec3& b) { x += b.x, y += b.y, z += b.z;  return *this; }
	Vec3 operator-=(const Vec3& b) { x -= b.x, y -= b.y, z -= b.z; return *this; }
	Vec3 operator*=(const float& b) { x *= b, y *= b, z *= b; return *this; }
	Vec3 operator/=(const float& b) { x /= b, y /= b, z /= b; return *this; }
};