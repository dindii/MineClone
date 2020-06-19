#pragma once


namespace MC
{

	//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.

	// TODO OPTIMIZATION STAGE: Implementar operações em SIMD a fim de otimizar a velocidade dos calculos. 
	// Por enquanto vou deixar isso nas mãos do compilador usado.


	struct vec3
	{
		vec3();
		vec3(float scalar);
		vec3(const float xx, const float yy, const float zz);

		std::string ToString() const;

		float Length();
		float Length2();
		vec3 Normalized();

		static vec3 lerp(const vec3& start, const vec3& end, float alpha);

		static float Length(const vec3& vec);
		static float Length2(const vec3& vec);
		static vec3 Normalize(const vec3& vec)
			;
		static vec3 Cross(const vec3& first, const vec3& second);
		static float Dot(const vec3& first, const vec3& second);

		float Dot(const vec3& other) const;
		vec3 Cross(const vec3& other);

		//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
		//juntar uma operação na outra
		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		vec3& multiply(const float& other);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const float& other);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		vec3& operator*=(const float& other);


		bool operator==(const vec3& other);
		bool operator!=(const vec3& other);

		vec3 operator-() const { return { -x, -y, -z }; }


		vec3 operator-() { return { -this->x, -this->y, -this->z }; }

		union {
			struct {
				float x, y, z;
			};
			struct {
				float r, g, b;
			};
			struct {
				float elements[3];
			};
		};
	};
}

