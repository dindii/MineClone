#include "mcpch.h"
#include "VoxelTerrain.h"

#include "MCP/Utils/Logger.h"

#include "MCP/Renderer/Misc/PNGimageWriter.h"

namespace MC
{
	VoxelTerrain::VoxelTerrain()
	{
		superChunk = new Superchunk;
	}

	VoxelTerrain::~VoxelTerrain()
	{
		delete superChunk;
		delete terrainPreviewTex;
	}

	//@TODO: INICIALIZADOR DA IMAGEM NA FUNÇÃO DE NOISE. PARA IMAGEM TER O MESMO TAMANHO DO TERRENO. (OU FIXO?)

	void VoxelTerrain::Gen3DNoiseTerrain(uint32_t xt, uint32_t yt, uint32_t zt)
	{
		PerlinNoise Noise;

		float xf = xt;
		float yf = yt;
		float zf = zt;


		for (int x = 0; x < xt; x++)
			for (int y = 0; y < yt; y++)
				for (int z = 0; z < zt; z++)
				{
					float should = Noise.GenOctave(x / xf, y / yf, z / zf, 4, 1.5f, 0.25f);

					(should * xf) > y ? superChunk->Set(x, y, z, 1) : superChunk->Set(x, y, z, 0);

					
		
				}	

		//terrainPreview.Write();
	}

	void VoxelTerrain::Gen2DNoiseTerrain(uint32_t xt, uint32_t yt, uint32_t zt)
	{
		PerlinNoise Noise;

		PNGimageWriter terrainPreview("terrainpreview.png", xt, yt);

		float xf = xt;
		float yf = yt;
		float should = 0.0f;

		for (int y = 0; y < yt; y++)
		{		
			for (int x = 0; x < xt; x++)
			{
				terrainPreview.Set(should);
				for (int z = 0; z <= zt; z++)
				{
					should = Noise.GenOctave(x / xf, y / yf, 0.0f, 8, 5.0f, 0.15f);
					(should * yf) > y ? superChunk->Set(x, y, z, 1) : superChunk->Set(x, y, z, 0);
				}
			}
		}
		terrainPreview.Write();
		terrainPreviewTex = new Texture2D(terrainPreview.GetData(), terrainPreview.getWidth(), terrainPreview.getHeight(), 1);
	}


	void VoxelTerrain::GenFlatTerrain(uint32_t xt, uint32_t yt, uint32_t zt)
	{
		for (int x = 0; x < xt; x++)
			for (int y = 0; y < yt; y++)
				for (int z = 0; z < zt; z++)		
						superChunk->Set(x, y, z, 1);	
	}

}