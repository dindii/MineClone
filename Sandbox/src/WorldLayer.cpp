#include "WorldLayer.h"
#include "imgui/imgui.h"

#include <thread>

WorldLayer::WorldLayer() : Layer("WorldLayer"), terrain(48, 48, 48)
{
	camera = MC::Camera(1362 / 701, { 0.0f, 0.0f, 500.0f });
	camera.SetCameraLag(true);
	camera.SetCameraLagValue(0.15000f);

	//terrain.GenNoiseTerrain(MC::VoxelTerrain::TerrainType::Terrain3D, 1, 2.865f, 0.25f, 0.0f, 0.0f);
	terrain.GenNoiseTerrain(MC::VoxelTerrain::TerrainType::Terrain3D, 1, 0.0f, 0.25f, 0.0f, 0.0f);


	//terrain.GenFlatTerrain();

	//std::thread terrainth(&MC::VoxelTerrain::GenFlatTerrain, terrain);
	//terrainth.join();


	for (uint32_t x = 0; x < 100; x++)
	{
		Directions.Set(x, 0, 0, 1);
	}

	for (uint32_t y = 0; y < 100; y++)
	{
		Directions.Set(0, y, 0, 1);
	}

	//Por hora só temos um SC que detém 16 C (16*16 em uma direção) isto é, 256 blocos em linha reta.
	//Por isso, algo além de 256 iria causar alguns comportamentos estranhos até tornar SC dinamico.
	for (uint32_t z = 0; z < 256; z++)
	{
		Directions.Set(0, 0, z, 1);
	}


}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	
	MovePlayer(deltaTime);

	MC::VoxelRenderer::Clear();
	MC::VoxelRenderer::BeginScene(camera);
//	MC::VoxelRenderer::Draw(&Directions);
	MC::VoxelRenderer::Draw(terrain.GetTerrainData());
}

void WorldLayer::OnEvent(MC::Event& e)
{
	camera.OnEvent(e);
}

void WorldLayer::OnImGuiRender()
{
	ImGui::Image((void*)(intptr_t)terrain.GetTerrainPreview().GetID(),
	ImVec2{ previewSize , previewSize });

	ImGui::Text("Terrain size: %i x %i", terrain.GetTerrainPreview().GetWidth(), terrain.GetTerrainPreview().GetHeight());
	ImGui::SliderFloat("Image preview size", &previewSize, 0, 1000);

	ImGui::NewLine();

	//#TODO Generate 2D images without interference of the Z-terrain.
	if (ImGui::SliderInt("Octaves", &octaves, 0, 8) ||
		ImGui::SliderFloat("Frequency", &frequency, 0.0f, 10.0f) ||
		ImGui::SliderFloat("Persistance", &persistence, 0.0f, 1.0f) ||
		ImGui::SliderFloat(" X Offset", &xOffset, 0.0f, 10.0f) ||
		ImGui::SliderFloat(" Y Offset", &yOffset, 0.0f, 10.0f))
	{
		ReGenTerrain();
	}
}

void WorldLayer::ReGenTerrain()
{
	terrain.GenNoiseTerrain(MC::VoxelTerrain::TerrainType::Terrain3D, octaves, frequency, persistence, xOffset, yOffset);
}

void WorldLayer::MovePlayer(MC::DeltaTime deltaTime)
{
	MC::vec3 gotoCamera;

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_W))
		gotoCamera.z = -cameraSpeed;
	
	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_S))
		gotoCamera.z = cameraSpeed;
	
	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_D))
		gotoCamera.x = cameraSpeed;
	
	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_A))
		gotoCamera.x = -cameraSpeed;
	
	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_SPACE))
		gotoCamera.y = cameraSpeed;
	
	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_CTRL))
		gotoCamera.y = -cameraSpeed;

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_SHIFT))
		cameraSpeed = 360.0f;
	else
		cameraSpeed = 50.5f;
	

	camera.AddCameraTargetPosition(gotoCamera, deltaTime);	
//	camera.SetCameraPosition(MC::vec3(camera.GetCameraPos().x - gotoCamera.x,camera.GetCameraPos().y + gotoCamera.y, camera.GetCameraPos().z + gotoCamera.z));

}

//#TODO: mover para um controller
void WorldLayer::LookAround()
{
	MC::vec2 Delta = MC::InputHandler::GetMouseDelta();

	camera.SetCameraPitch(MC::toRadians(Delta.y * cameraSens));
	camera.SetCameraYaw(MC::toRadians(Delta.x * cameraSens));
}
