#pragma once
#include "mcpch.h"
#include "uivec3.h"
#include <sstream>

namespace MC
{
	uivec3::uivec3() : x(0), y(0), z(0)
	{
	}

	uivec3::uivec3(const uint32_t xx, const uint32_t yy, const uint32_t zz, const uint32_t ww) : x(xx), y(yy), z(zz)
	{
	}

	uivec3::uivec3(uint32_t scalar) : x(scalar), y(scalar), z(scalar)
	{
	}

	uivec3::uivec3(uint32_t xx, uint32_t yy, uint32_t zz) : x(xx), y(yy), z(zz)
	{

	}

	std::string uivec3::ToString() const
	{
		std::stringstream ss;
		ss << "uivec3: (" << x << ", " << y << ", " << z << ", " << ")";
		return ss.str();
	}

	uivec3& uivec3::add(const uivec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	uivec3& uivec3::subtract(const uivec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	uivec3& uivec3::multiply(const uivec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	uivec3& uivec3::divide(const uivec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	uivec3& uivec3::operator+=(const uivec3& other)
	{
		return add(other);
	}

	uivec3& uivec3::operator-=(const uivec3& other)
	{
		return subtract(other);
	}

	uivec3& uivec3::operator*=(const uivec3& other)
	{
		return multiply(other);
	}

	uivec3& uivec3::operator/=(const uivec3& other)
	{
		return divide(other);
	}



	bool uivec3::operator==(const uivec3& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool uivec3::operator!=(const uivec3& other)
	{
		return (!(*this == other));
	}


	std::ostream& operator<<(std::ostream& os, const MC::uivec3& vec)
	{
		return os << vec.ToString();
	}

	uivec3 operator+(uivec3 left, const uivec3& right)
	{
		return left.add(right);
	}
	uivec3 operator-(uivec3 left, const uivec3& right)
	{
		return left.subtract(right);
	}
	uivec3 operator*(uivec3 left, const uivec3& right)
	{
		return left.multiply(right);
	}
	uivec3 operator/(uivec3 left, const uivec3& right)
	{
		return left.divide(right);
	}

}