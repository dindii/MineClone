#include "WorldLayer.h"
#include "imgui/imgui.h"

WorldLayer::WorldLayer() : Layer("WorldLayer"), terrain(64, 64, 64)
{
	camera = MC::Camera(1362 / 701, { 0.0f, 0.0f, 500.0f });
	camera.SetCameraLag(true);
	camera.SetCameraLagValue(0.15000f);

	terrain.GenNoiseTerrain(MC::VoxelTerrain::TerrainType::Terrain3D, 1, 0.0f, 0.25f, 0.0f, 0.0f);

}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	
	MovePlayer(deltaTime);

	MC::VoxelRenderer::Clear();
	MC::VoxelRenderer::BeginScene(camera);
	MC::VoxelRenderer::Draw(terrain.GetTerrainData());
	MC::VoxelRenderer::EndScene();
}

void WorldLayer::OnEvent(MC::Event& e)
{
	camera.OnEvent(e);
	//MC_LOG_TRACE(e);
}

void WorldLayer::OnImGuiRender()
{
	ImGui::Image((void*)(intptr_t)terrain.GetTerrainPreview().GetID(),
	ImVec2{ previewSize , previewSize });

	ImGui::Text("Terrain size: %i x %i", terrain.GetTerrainPreview().GetWidth(), terrain.GetTerrainPreview().GetHeight());
	ImGui::SliderFloat("Image preview size", &previewSize, 0, 1000);

	ImGui::NewLine();

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
