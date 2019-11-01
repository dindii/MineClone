#pragma once
#include "mcpch.h"
#include "vec2.h"
#include <sstream>

namespace MC
{
	vec2::vec2() : x(0.0f), y(0.0f)
	{
	}

	vec2::vec2(const float xx, const float yy) : x(xx), y(yy)
	{
	}

	vec2::vec2(float scalar) : x(scalar), y(scalar)
	{
	}


	std::string vec2::ToString() const
	{
		std::stringstream ss;
		ss << "vec2: (" << x << ", " << y << ")";
		return ss.str();
	}


	vec2& vec2::add(const vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}



	vec2& vec2::operator+=(const vec2& other)
	{
		return add(other);
	}

	vec2& vec2::operator-=(const vec2& other)
	{
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other)
	{
		return multiply(other);
	}

    vec2& vec2::operator/=(const vec2& other)
	{
		return divide(other);
	}



	bool vec2::operator==(const vec2& other)
	{
		return (x == other.x && y == other.y);
	}

	bool vec2::operator!=(const vec2& other)
	{
		return (!(*this == other));
	}


	std::ostream& operator<<(std::ostream& os, const MC::vec2& vec)
	{
		return os << vec.ToString();
	}


	vec2 operator+(vec2 left, const vec2& right)
	{
		return left.add(right);
	}
	vec2 operator-(vec2 left, const vec2& right)
	{
		return left.subtract(right);
	}
	vec2 operator*(vec2 left, const vec2& right)
	{
		return left.multiply(right);
	}
	vec2 operator/(vec2 left, const vec2& right)
	{
		return left.divide(right);
	}

}