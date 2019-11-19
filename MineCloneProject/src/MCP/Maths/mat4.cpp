#include "mcpch.h"
#include "mat4.h"
#include <sstream>
#include "Maths.h"

namespace MC
{
	mat4::mat4()
	{
		*this = mat4::Identity();
	}

	mat4 MC::mat4::Identity()
	{
		return mat4(1.0f);
	}

	mat4::mat4(const float diagonal)
	{
		memset(elements, 0, 4 * 4 * sizeof(float));

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4::mat4(const mat4& other)
	{
		//std::copy(&this->elements[0], &this->elements[16], &other[0]);
		memcpy(this->elements, other.elements, 4 * 4 * sizeof(float));
	}

	mat4 mat4::Multiply(const mat4& other)
	{
		float result[16];

		float sum = 0.0f;

		for (unsigned int y = 0; y < 4; y++)
		{
			for (unsigned int x = 0; x < 4; x++)
			{
				sum = 0.0f;

				for (unsigned int i = 0; i < 4; i++)
				{
					sum += elements[x + i * 4] * other[i + y * 4];
				}

				result[x + y * 4] = sum;
			}
		}
	 
		memcpy(this->elements, result, 4 * 4 * sizeof(float));

		return *this;
		/*return *this;*/
	}

	vec4 mat4::Multiply(const vec4& other) const
	{
		return vec4
		(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
			columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
		);
	}

	vec3 mat4::Multiply(const vec3& other) const
	{
		return vec3(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
		);
	}

	mat4 mat4::operator*=(const mat4& other)
	{
		return Multiply(other);
	}  

	mat4 mat4::Scale(const vec3& vector)
	{
		mat4 result(1.0f);

		result[0 + 0 * 4] = vector.x;
		result[1 + 1 * 4] = vector.y;
		result[2 + 2 * 4] = vector.z;

		return result;
	}

	mat4 mat4::Rotate(const float& angle, const vec3& axis)
	{	
		mat4 result(1.0f);

		float a = MC::toRadians(angle);
		float c = MC::cos(a);
		float s = MC::sin(a);
		float i = 1.0f - c;

		//JUST A TEST
		//const vec3 normalizedAxis = vec3::Normalize(axis);

 		float x = axis.x;
 		float y = axis.y;
 		float z = axis.z;
// 
// 		float x = normalizedAxis.x;
// 		float y = normalizedAxis.y;
//  	float z = normalizedAxis.z;

		result[0 + 0 * 4] = x * x * i + c;
		result[1 + 0 * 4] = x * y * i + z * s;
		result[2 + 0 * 4] = x * z * i - y * s;
									
		result[0 + 1 * 4] = x * y * i - z * s;
		result[1 + 1 * 4] = y * y * i + c;
		result[2 + 1 * 4] = y * z * i + x * s;
									
		result[0 + 2 * 4] = x * z * i + y * s;
		result[1 + 2 * 4] = y * z * i - x * s;
		result[2 + 2 * 4] = z * z * i + c;

		return result;
	}

	mat4 mat4::Translate(const vec3& vector)
	{
		mat4 result(1.0f);

		result[0 + 3 * 4] = vector.x;
		result[1 + 3 * 4] = vector.y;
		result[2 + 3 * 4] = vector.z;

		return result;
	}

	mat4 mat4::LookAt(const vec3& Position, const vec3& target, const vec3& up)
	{
// 		mat4 result = mat4::Identity();
// 
// 		vec3 cameraDir = (target - Position).Normalized();
// 		vec3 cameraRight = vec3::Normalize(cameraDir.Cross(up));
// 		vec3 cameraUp = cameraRight.Cross(cameraDir);
// 
// 		result[0 + 0 * 4] = cameraRight.x;
// 		result[1 + 0 * 4] = cameraRight.y;
// 		result[2 + 0 * 4] = cameraRight.z;
// 
// 		result[0 + 1 * 4] = cameraUp.x;
// 		result[1 + 1 * 4] = cameraUp.y;
// 		result[2 + 1 * 4] = cameraUp.z;
// 
// 		result[0 + 2 * 4] = -cameraDir.x;
// 		result[1 + 2 * 4] = -cameraDir.y;
// 		result[2 + 2 * 4] = -cameraDir.z;
// 
// 		return result * mat4::Translate(vec3(-Position.x, -Position.y, -Position.z));

// 
		mat4 result;

		vec3 cameraDir = vec3::Normalize(target - Position);
		vec3 cameraRight = vec3::Normalize(cameraDir.Cross(up));
		vec3 cameraUp = cameraRight.Cross(cameraDir);

		result[0 + 0 * 4] = cameraRight.x;
		result[1 + 0 * 4] = cameraRight.y;
		result[2 + 0 * 4] = cameraRight.z;

		result[0 + 1 * 4] = cameraUp.x;
		result[1 + 1 * 4] = cameraUp.y;
		result[2 + 1 * 4] = cameraUp.z;

		result[0 + 2 * 4] = -cameraDir.x;
		result[1 + 2 * 4] = -cameraDir.y;
		result[2 + 2 * 4] = -cameraDir.z;

		return result * mat4::Translate({ -Position.x, -Position.y, -Position.z });
	}

	std::string mat4::ToString() const
	{
		std::stringstream ss;

		ss << "mat4:\n" << columns[0].x << ", " << columns[0].y << ", " << columns[0].z << ", " << columns[0].w << '\n'
		                << columns[1].x << ", " << columns[1].y << ", " << columns[1].z << ", " << columns[1].w << '\n'
		                << columns[2].x << ", " << columns[2].y << ", " << columns[2].z << ", " << columns[2].w << '\n'
		                << columns[3].x << ", " << columns[3].y << ", " << columns[3].z << ", " << columns[3].w;

		return ss.str();
	}

	mat4 mat4::Inverse(const mat4& matrix)
	{
		mat4 temp = matrix;
		return temp.Invert();
	}

	mat4 mat4::Ortho(const float& left, const float& right, const float& bottom, const float& top, const float& Near, const float& Far)
	{
		mat4 result(1.0f);

		result[0 + 0 * 4] = 2.0f / (right - left);
		result[1 + 1 * 4] = 2.0f / (top - bottom);
		result[2 + 2 * 4] = 2.0f / (Near - Far);

		result[0 + 3 * 4] = (left + right) / (left - right);
		result[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result[2 + 3 * 4] = (Far + Near) / (Far - Near);

		return result;
	}

	mat4 mat4::Perspective(const float& FOV, const float& AR, const float& Near, const float& Far)
	{
		mat4 result(1.0f);

		float q = 1.0f / MC::tan(MC::toRadians(0.5f * FOV));
		float a = q / AR;
		float b = (Near + Far) / (Near - Far);
		float c = (2.0f * Near * Far) / (Near - Far);

		result[0 + 0 * 4] = a;
		result[1 + 1 * 4] = q;
		result[2 + 2 * 4] = b;
		result[2 + 3 * 4] = c;
		result[3 + 2 * 4] = -1.0f;

		return result;

	}

	mat4& mat4::Invert()
	{
		float temp[16];

		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		double determinant =
			elements[0] * temp[0] +
			elements[1] * temp[4] +
			elements[2] * temp[8] +
			elements[3] * temp[12];

		   determinant = 1.0 / determinant;

		   for (unsigned short int x = 0; x < 4 * 4; x++)
			   elements[x] = temp[x] * (float)determinant;

		   return *this;
	}

	mat4& mat4::Transpose()
	{
		mat4 temp(1.0f);

		for (unsigned short int y = 0; y < 4; y++)
			for (unsigned short int x = 0; x < 4; x++)
				temp[y * x * 4] = elements[x * y * 4];

		return *this;
	}

	mat4 mat4::Transpose(const mat4& matrix)
	{
		return mat4(1.0f);
	}


	vec4 operator*(const mat4& left, const vec4& right)
	{
		return left.Multiply(right);
	}
	vec3 operator*(const mat4& left, const vec3& right)
	{
		return left.Multiply(right);
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.Multiply(right);
	}

	std::ostream& operator<<(std::ostream& stream, const mat4& mat)
	{
		return stream << mat.ToString();
	}


}
