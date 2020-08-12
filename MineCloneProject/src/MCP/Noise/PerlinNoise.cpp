#include "mcpch.h"
#include "PerlinNoise.h"
#include "MCP/Maths/Maths.h"

namespace MC
{

	double lerpa(double a, double b, double x) {
		return a + x * (b - a);
	}

	PerlinNoise::PerlinNoise()
	{
		uint32_t p[256] = { 151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };


		for (int x = 0; x < 512; x++)
			permutation[x] = p[x % 256];
	}

	double PerlinNoise::fade(double t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);

	}

	int PerlinNoise::inc(int num)
	{
		num++;
		//if (repeat > 0) num %= repeat;

		return num;
	}

	double PerlinNoise::grad(int hash, double x, double y, double z)
	{
// 		switch (hash & 0xF)
// 		{
// 			case 0x0: return  x + y;
// 			case 0x1: return -x + y;
// 			case 0x2: return  x - y;
// 			case 0x3: return -x - y;
// 			case 0x4: return  x + z;
// 			case 0x5: return -x + z;
// 			case 0x6: return  x - z;
// 			case 0x7: return -x - z;
// 			case 0x8: return  y + z;
// 			case 0x9: return -y + z;
// 			case 0xA: return  y - z;
// 			case 0xB: return -y - z;
// 			case 0xC: return  y + x;
// 			case 0xD: return -y + z;
// 			case 0xE: return  y - x;	
// 			case 0xF: return -y - z;
// 			default: return 0;
// 		}

		int h = hash & 15;									// Take the hashed value and take the first 4 bits of it (15 == 0b1111)
		double u = h < 8 /* 0b1000 */ ? x : y;				// If the most significant bit (MSB) of the hash is 0 then set u = x.  Otherwise y.

		double v;											// In Ken Perlin's original implementation this was another conditional operator (?:).  I
															// expanded it for readability.

		if (h < 4 /* 0b0100 */)								// If the first and second significant bits are 0 set v = y
			v = y;
		else if (h == 12 /* 0b1100 */ || h == 14 /* 0b1110*/)// If the first and second significant bits are 1 set v = x
			v = x;
		else 												// If the first and second significant bits are not equal (0/1, 1/0) set v = z
			v = z;

		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	double PerlinNoise::GenOctave(double x, double y, double z, uint32_t octaves, float frequency, float persistence)
	{
// 		double total = 0;
// 		double amplitude = 1;
// 
// 		for (int i = 0; i < octaves; i++) {
// 			total += Gen(x * frequency, y * frequency, z * frequency) * amplitude; //Add offset a(z * frequency + offset)
// 
// 			amplitude *= persistence;
// 			frequency *= 1.5f; //Lacunarity goes here
// 		}
// 
// 		return total;

		double total = 0;
		double amplitude = 1;
		double maxValue = 0;			// Used for normalizing result to 0.0 - 1.0
		for (int i = 0; i < octaves; i++) {
			total += Gen(x * frequency, y * frequency, z * frequency) * amplitude;

			maxValue += amplitude;

			amplitude *= persistence;
			frequency *= 2;
		}

		return total / maxValue;

	}


	double PerlinNoise::Gen(double x, double y, double z)
	{
		//if (repeat > 0) {                                    // If we have any repeat on, change the coordinates to their "local" repetitions
		//	x = dmod(x, repeat);
		//	y = dmod(y, repeat);
		//	z = dmod(z, repeat);
		//}
		
		int xi = (int)x & 255;								// Calculate the "unit cube" that the point asked will be located in
		int yi = (int)y & 255;								// The left bound is ( |_x_|,|_y_|,|_z_| ) and the right bound is that
		int zi = (int)z & 255;								// plus 1.  Next we calculate the location (from 0.0 to 1.0) in that cube.
		double xf = x-(int)x;								// We also fade the location to smooth the result.
		double yf = y-(int)y;
		double zf = z-(int)z;

		double u = fade(xf);
		double v = fade(yf);
		double w = fade(zf);
															
		int aaa, aba, aab, abb, baa, bba, bab, bbb;
		aaa = permutation[permutation[permutation[    xi ]+    yi ]+    zi ];
		aba = permutation[permutation[permutation[    xi ]+inc(yi)]+    zi ];
		aab = permutation[permutation[permutation[    xi ]+    yi ]+inc(zi)];
		abb = permutation[permutation[permutation[    xi ]+inc(yi)]+inc(zi)];
		baa = permutation[permutation[permutation[inc(xi)]+    yi ]+    zi ];
		bba = permutation[permutation[permutation[inc(xi)]+inc(yi)]+    zi ];
		bab = permutation[permutation[permutation[inc(xi)]+    yi ]+inc(zi)];
		bbb = permutation[permutation[permutation[inc(xi)]+inc(yi)]+inc(zi)];
	
		double x1, x2, y1, y2;
		x1 = lerpa(	grad (aaa, xf  , yf  , zf),				// The gradient function calculates the dot product between a pseudorandom
					grad (baa, xf-1, yf  , zf),				// gradient vector and the vector from the input coordinate to the 8
					u);										// surrounding points in its unit cube.
		x2 = lerpa(	grad (aba, xf  , yf-1, zf),				// This is all then lerped together as a sort of weighted average based on the faded (u,v,w)
					grad (bba, xf-1, yf-1, zf),				// values we made earlier.
			          u);
		y1 = lerpa(x1, x2, v);

		x1 = lerpa(	grad (aab, xf  , yf  , zf-1),
					grad (bab, xf-1, yf  , zf-1),
					u);
		x2 = lerpa(	grad (abb, xf  , yf-1, zf-1),
		          	grad (bbb, xf-1, yf-1, zf-1),
		          	u);
		y2 = lerpa(x1, x2, v);
		
		return (lerpa(y1, y2, w)+1)/2;

	}
}