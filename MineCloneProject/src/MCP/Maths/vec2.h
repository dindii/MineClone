#pragma once

namespace MC
{

	//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.

	struct vec2
	{
		vec2();
		vec2::vec2(float scalar);
		vec2(const float xx, const float yy);

		std::string ToString() const;

		//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
		//juntar uma operação na outra
		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);


		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		bool operator==(const vec2& other);
		bool operator!=(const vec2& other);

		union
		{
			struct {
				float x, y;
			};
			struct {
				float r, g;
			};
		};
	};

	std::ostream& operator<<(std::ostream& os, const MC::vec2& vec);
}

