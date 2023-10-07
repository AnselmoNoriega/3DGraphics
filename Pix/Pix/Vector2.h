#pragma once

struct Vec2
{
	float x, y;

	Vec2() : x(0.0f), y(0.0f) {};
	Vec2(float x, float y) : x(x), y(y) {};

	Vec2 operator-() const { return { -x, -y }; }
	Vec2 operator+(const Vec2& b) const { return { x + b.x, y + b.y }; }
	Vec2 operator-(const Vec2& b) const { return { x - b.x, y - b.y }; }
	Vec2 operator*(const float& b) const { return { x * b, y * b }; }
	Vec2 operator/(const float& b) const { return { x / b, y / b }; }

	Vec2 operator+=(const Vec2& b) { x += b.x, y += b.y;  return *this; }
	Vec2 operator-=(const Vec2& b) { x -= b.x, y -= b.y; return *this; }
	Vec2 operator*=(const float& b)  { x *= b, y *= b ; return *this; }
	Vec2 operator/=(const float& b)  { x /= b, y /= b ; return *this; }
};