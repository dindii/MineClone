#pragma once
#include "mcpch.h"
#include "bvec4.h"
#include <sstream>

namespace MC
{
	bvec4::bvec4() : x(0), y(0), z(0), w(0)
	{
	}

	bvec4::bvec4(const uint8_t xx, const uint8_t yy, const uint8_t zz, const uint8_t ww) : x(xx), y(yy), z(zz), w(ww)
	{
	}

	bvec4::bvec4(uint8_t scalar) : x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	std::string bvec4::ToString() const
	{
		std::stringstream ss;
		ss << "bvec4: (" << x << ", " << y << ", " << z << ", " << w << ")";
		return ss.str();
	}

	bvec4& bvec4::add(const bvec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	bvec4& bvec4::subtract(const bvec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	bvec4& bvec4::multiply(const bvec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	bvec4& bvec4::divide(const bvec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	bvec4& bvec4::operator+=(const bvec4& other)
	{
		return add(other);
	}

	bvec4& bvec4::operator-=(const bvec4& other)
	{
		return subtract(other);
	}

	bvec4& bvec4::operator*=(const bvec4& other)
	{
		return multiply(other);
	}

	bvec4& bvec4::operator/=(const bvec4& other)
	{
		return divide(other);
	}



	bool bvec4::operator==(const bvec4& other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}

	bool bvec4::operator!=(const bvec4& other)
	{
		return (!(*this == other));
	}


	std::ostream& operator<<(std::ostream& os, const MC::bvec4& vec)
	{
		return os << vec.ToString();
	}

	bvec4 operator+(bvec4 left, const bvec4& right)
	{
		return left.add(right);
	}
	bvec4 operator-(bvec4 left, const bvec4& right)
	{
		return left.subtract(right);
	}
	bvec4 operator*(bvec4 left, const bvec4& right)
	{
		return left.multiply(right);
	}
	bvec4 operator/(bvec4 left, const bvec4& right)
	{
		return left.divide(right);
	}

}