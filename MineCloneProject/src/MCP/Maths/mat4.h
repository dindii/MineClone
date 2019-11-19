#pragma once

#include "vec3.h"
#include "vec4.h"

namespace MC
{

	//Quando eu começar a notar algum bottleneck nos calculos, começarei a converter as operações para SIMD.


	/*                                        Column Major order - Right Handed                                                        */

	struct mat4
	{
		mat4();
		mat4(const float diagonal);
		mat4(const mat4& other);

		

		inline float& operator[](const unsigned int index) { return elements[index]; }
		inline const float& operator[](const unsigned int index) const { return elements[index]; }
	    
		mat4 Multiply(const mat4& other);

		vec3 Multiply(const vec3& other) const;
		vec4 Multiply(const vec4& other) const;
	
		friend vec4 operator*(const mat4& left, const vec4& other);
		friend vec3 operator*(const mat4& left, const vec3& other);
		friend mat4 operator*(mat4 left, const mat4& right);


		 mat4 operator*=(const mat4& right);

		 mat4& Transpose();
		 mat4& Invert();

		 static mat4 Inverse(const mat4& matrix);
		 static mat4 Ortho(const float& left, const float& right, const float& bottom, const float& top, const float& Near, const float& Far);
		 static mat4 Identity();
		 static mat4 Transpose(const mat4& matrix);
		 static mat4 Perspective(const float& FOV, const float& AR, const float& Near, const float& Far);

		 //@TODO: Criar operações de transformação membro.
		 static mat4 Scale(const vec3& vector);
		 static mat4 Rotate(const float& angle, const vec3& axis);
		 static mat4 Translate(const vec3& vector);

		 static mat4 LookAt(const vec3& Position, const vec3& target, const vec3& up);

		 std::string ToString() const;

		 friend std::ostream& operator<<(std::ostream& stream, const mat4& mat);


		 union
		 {
			 struct 
			 {
				 float elements[4 * 4];
			 };
			 struct
			 {
				 float Elements[4][4];
			 };
			 struct 
			 {
				 vec4 columns[4];
			 };

		 };

	};
}