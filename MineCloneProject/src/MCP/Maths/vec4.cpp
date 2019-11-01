#pragma once
#include "mcpch.h"
#include "vec4.h"
#include <sstream>

namespace MC
{
	vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	vec4::vec4(const float xx, const float yy, const float zz, const float ww) : x(xx), y(yy), z(zz), w(ww)
	{
	}

	vec4::vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	std::string vec4::ToString() const
	{
		std::stringstream ss;
		ss << "vec4: (" << x << ", " << y << ", " << z << ", " << w << ")";
		return ss.str();
	}

	float vec4::Dot(const vec4& other)
	{
		return x * other.x + y * other.y + z * other.z +  w * other.w;
	}

	vec4& vec4::add(const vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vec4& vec4::subtract(const vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	vec4& vec4::multiply(const vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	vec4& vec4::divide(const vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	vec4& vec4::operator+=(const vec4& other)
	{
		return add(other);
	}

	vec4& vec4::operator-=(const vec4& other)
	{
		return subtract(other);
	}

	vec4& vec4::operator*=(const vec4& other)
	{
		return multiply(other);
	}

	vec4& vec4::operator/=(const vec4& other)
	{
		return divide(other);
	}



	bool vec4::operator==(const vec4& other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}

	bool vec4::operator!=(const vec4& other)
	{
		return (!(*this == other));
	}


	std::ostream& operator<<(std::ostream& os, const MC::vec4& vec)
	{
		return os << vec.ToString();
	}

	vec4 operator+(vec4 left, const vec4& right)
	{
		return left.add(right);
	}
	vec4 operator-(vec4 left, const vec4& right)
	{
		return left.subtract(right);
	}
    vec4 operator*(vec4 left, const vec4& right)
	{
		return left.multiply(right);
	}
	vec4 operator/(vec4 left, const vec4& right)
	{
		return left.divide(right);
	}

}