#pragma once

namespace MC
{

	//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.

	struct vec4
	{
		vec4();
		vec4(float scalar);
		vec4(const float xx, const float yy, const float zz, const float ww);

		std::string ToString() const;

		float Dot(const vec4& other);


		//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
		//juntar uma operação na outra
		vec4& add(const vec4& other);
		vec4& subtract(const vec4& other);
		vec4& multiply(const vec4& other);
		vec4& divide(const vec4& other);

		//Não precisa ser friend nem ser declarado aqui mas acho importante para fins de leitura
		friend vec4 operator+(vec4 left, const vec4& right);
		friend vec4 operator-(vec4 left, const vec4& right);
		friend vec4 operator*(vec4 left, const vec4& right);
		friend vec4 operator/(vec4 left, const vec4& right);


		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator*=(const vec4& other);
		vec4& operator/=(const vec4& other);

		bool operator==(const vec4& other);
		bool operator!=(const vec4& other);

		union {
			struct {
				float x, y, z, w;
			};
			struct {
				float r, g, b, a;
			};
			struct {
				float elements[3];
			};
		};
	};

	std::ostream& operator<<(std::ostream& os, const MC::vec4& vec);

}