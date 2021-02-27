#pragma once
#include "mcpch.h"
#include "bvec3.h"
#include <sstream>

namespace MC
{
	bvec3::bvec3() : x(0), y(0), z(0)
	{
	}

	bvec3::bvec3(const uint8_t xx, const uint8_t yy, const uint8_t zz, const uint8_t ww) : x(xx), y(yy), z(zz)
	{
	}

	bvec3::bvec3(uint8_t scalar) : x(scalar), y(scalar), z(scalar)
	{
	}

	std::string bvec3::ToString() const
	{
		std::stringstream ss;
		ss << "bvec3: (" << x << ", " << y << ", " << z << ", " << ")";
		return ss.str();
	}

	bvec3& bvec3::add(const bvec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	bvec3& bvec3::subtract(const bvec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	bvec3& bvec3::multiply(const bvec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	bvec3& bvec3::divide(const bvec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	bvec3& bvec3::operator+=(const bvec3& other)
	{
		return add(other);
	}

	bvec3& bvec3::operator-=(const bvec3& other)
	{
		return subtract(other);
	}

	bvec3& bvec3::operator*=(const bvec3& other)
	{
		return multiply(other);
	}

	bvec3& bvec3::operator/=(const bvec3& other)
	{
		return divide(other);
	}



	bool bvec3::operator==(const bvec3& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool bvec3::operator!=(const bvec3& other)
	{
		return (!(*this == other));
	}


	std::ostream& operator<<(std::ostream& os, const MC::bvec3& vec)
	{
		return os << vec.ToString();
	}

	bvec3 operator+(bvec3 left, const bvec3& right)
	{
		return left.add(right);
	}
	bvec3 operator-(bvec3 left, const bvec3& right)
	{
		return left.subtract(right);
	}
	bvec3 operator*(bvec3 left, const bvec3& right)
	{
		return left.multiply(right);
	}
	bvec3 operator/(bvec3 left, const bvec3& right)
	{
		return left.divide(right);
	}

}