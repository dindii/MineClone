#pragma once

namespace MC
{

	//Para manter a simplicidade, não vou usar de templates ou classes bases/derivadas.
	//4 Byte Vector

	struct uivec3
	{
		uivec3();
		uivec3(uint32_t xx, uint32_t yy, uint32_t zz);
		uivec3(uint32_t scalar);
		uivec3(const uint32_t xx, const uint32_t yy, const uint32_t zz, const uint32_t ww);

		std::string ToString() const;

		//Retornando uma referencia para o proprio objeto a fim de evitar criar novos objetos e podermos com eficiencia
		//juntar uma operação na outra
		uivec3& add(const uivec3& other);
		uivec3& subtract(const uivec3& other);
		uivec3& multiply(const uivec3& other);
		uivec3& divide(const uivec3& other);

		//Não precisa ser friend nem ser declarado aqui mas acho importante para fins de leitura
		friend uivec3 operator+(uivec3 left, const uivec3& right);
		friend uivec3 operator-(uivec3 left, const uivec3& right);
		friend uivec3 operator*(uivec3 left, const uivec3& right);
		friend uivec3 operator/(uivec3 left, const uivec3& right);


		uivec3& operator+=(const uivec3& other);
		uivec3& operator-=(const uivec3& other);
		uivec3& operator*=(const uivec3& other);
		uivec3& operator/=(const uivec3& other);

		bool operator==(const uivec3& other);
		bool operator!=(const uivec3& other);

		union {
			struct {
				uint32_t x, y, z;
			};
			struct {
				uint32_t r, g, b;
			};
			struct {
				uint32_t elements[3];
			};
		};
	};

	std::ostream& operator<<(std::ostream& os, const MC::uivec3& vec);

}