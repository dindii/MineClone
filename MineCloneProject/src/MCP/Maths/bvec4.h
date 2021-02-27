#pragma once

namespace MC
{

	//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.
	//4 Byte Vector

	struct bvec4
	{
		bvec4();
		bvec4(uint8_t scalar);
		bvec4(const uint8_t xx, const uint8_t yy, const uint8_t zz, const uint8_t ww);

		std::string ToString() const;

		//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
		//juntar uma operação na outra
		bvec4& add(const bvec4& other);
		bvec4& subtract(const bvec4& other);
		bvec4& multiply(const bvec4& other);
		bvec4& divide(const bvec4& other);

		//Não precisa ser friend nem ser declarado aqui mas acho importante para fins de leitura
		friend bvec4 operator+(bvec4 left, const bvec4& right);
		friend bvec4 operator-(bvec4 left, const bvec4& right);
		friend bvec4 operator*(bvec4 left, const bvec4& right);
		friend bvec4 operator/(bvec4 left, const bvec4& right);


		bvec4& operator+=(const bvec4& other);
		bvec4& operator-=(const bvec4& other);
		bvec4& operator*=(const bvec4& other);
		bvec4& operator/=(const bvec4& other);

		bool operator==(const bvec4& other);
		bool operator!=(const bvec4& other);

		union {
			struct {
				uint8_t x, y, z, w;
			};
			struct {
				uint8_t r, g, b, a;
			};
			struct {
				uint8_t elements[4];
			};
		};
	};

	std::ostream& operator<<(std::ostream& os, const MC::bvec4& vec);

}