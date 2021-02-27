#pragma once

namespace MC
{

	//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.
	//4 Byte Vector

	struct bvec3
	{
		bvec3();
		bvec3(uint8_t scalar);
		bvec3(const uint8_t xx, const uint8_t yy, const uint8_t zz, const uint8_t ww);

		std::string ToString() const;

		//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
		//juntar uma operação na outra
		bvec3& add(const bvec3& other);
		bvec3& subtract(const bvec3& other);
		bvec3& multiply(const bvec3& other);
		bvec3& divide(const bvec3& other);

		//Não precisa ser friend nem ser declarado aqui mas acho importante para fins de leitura
		friend bvec3 operator+(bvec3 left, const bvec3& right);
		friend bvec3 operator-(bvec3 left, const bvec3& right);
		friend bvec3 operator*(bvec3 left, const bvec3& right);
		friend bvec3 operator/(bvec3 left, const bvec3& right);


		bvec3& operator+=(const bvec3& other);
		bvec3& operator-=(const bvec3& other);
		bvec3& operator*=(const bvec3& other);
		bvec3& operator/=(const bvec3& other);

		bool operator==(const bvec3& other);
		bool operator!=(const bvec3& other);

		union {
			struct {
				uint8_t x, y, z;
			};
			struct {
				uint8_t r, g, b;
			};
			struct {
				uint8_t elements[3];
			};
		};
	};

	std::ostream& operator<<(std::ostream& os, const MC::bvec3& vec);

}