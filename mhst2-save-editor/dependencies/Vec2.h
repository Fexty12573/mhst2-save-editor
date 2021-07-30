#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

template<class T>
class Vec2
{
public:
	Vec2(T x, T y)
		: x(x), y(y)
	{
	}
	Vec2() : x(0), y(0)
	{
	}
	Vec2(const Vec2& v)
		: x(v.x), y(v.y)
	{
	}
	Vec2(Vec2&& v) noexcept
		: x(v.x), y(v.y)
	{
	}

	double length()
	{
		return std::sqrt(x * x + y * y);
	}
	double lensq()
	{
		auto l = length();
		return l * l;
	}
	Vec2& normalize()
	{
		auto l = length();
		x /= l; y /= l;
		return *this;
	}
	Vec2 get_normalized()
	{
		auto l = length();
		return Vec2(x / l, y / l);
	}

	void set_length(float len)
	{
		normalize() *= len;
	}
	void limit_length(float max) { if (length() > max) set_length(max); }

	template<class T2 = T>
	sf::Vector2<T2> sf_vector() const { return sf::Vector2<T2>(x, y); }

	template<class NewT>
	explicit operator Vec2<NewT>() const { return Vec2<NewT>((NewT)x, (NewT)y); }

	Vec2 operator+(const T& t) const { return Vec2(x + t, y + t); }
	Vec2 operator-(const T& t) const { return Vec2(x - t, y - t); }
	Vec2 operator*(const T& t) const { return Vec2(x * t, y * t); }
	Vec2 operator/(const T& t) const { return Vec2(x / t, y / t); }

	Vec2& operator+=(const T& t) { x += t; y += t; return *this; }
	Vec2& operator-=(const T& t) { x -= t; y -= t; return *this; }
	Vec2& operator*=(const T& t) { x *= t; y *= t; return *this; }
	Vec2& operator/=(const T& t) { x /= t; y /= t; return *this; }

	Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
	Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }

	Vec2 operator+(const Vec2& v) const { return Vec2(*this) += v; }
	Vec2 operator-(const Vec2& v) const { return Vec2(*this) -= v; }

	Vec2 operator-() const { return Vec2(-x, -y); }

	T operator*(const Vec2& v) const { return x * v.x + y * v.y; }
	Vec2& operator=(const Vec2& v) { x = v.x; y = v.y; return *this; }

	bool operator==(const Vec2& v) const { return x == v.x && y == v.y; }
	bool operator!=(const Vec2& v) const { return !((*this) == v); }

public:
	T x, y;
};

typedef Vec2<float>		Vec2f;
typedef Vec2<float>		vec2f;
typedef Vec2<double>	Vec2d;
typedef Vec2<double>	vec2d;
typedef Vec2<int>		Vec2i;
typedef Vec2<int>		vec2i;

template<class sf_T, class v2_T>
Vec2<v2_T> sf_to_vec2(const sf::Vector2<sf_T>& v)
{
	return Vec2<v2_T>((v2_T)v.x, (v2_T)v.y);
}
