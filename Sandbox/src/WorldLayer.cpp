#include "WorldLayer.h"
#include "imgui/imgui.h"
#include "MCP/Physic/AABB.h"
#include "MCP/Physic/Trace.h"

#include <thread>
WorldLayer::WorldLayer() : Layer("WorldLayer"), terrain(32, 32, 32)
{
	camera = MC::Camera(1362.0f / 701.0f, { 0.0f, 0.0f, 500.0f });
	camera.SetCameraLag(true);
	camera.SetCameraLagValue(0.15000f);


	terrain.GenNoiseTerrain(MC::VoxelTerrain::TerrainType::Terrain3D, octaves, frequency, persistence, 0.0f, 0.0f);
	//terrain.GenFlatTerrain();

	MC::InputHandler::showCursor(true);
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

	MC::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MC::MouseButtonPressedEvent>(BIND_EVENT_FN(WorldLayer::ChangeBlock));


	MC_LOG_TRACE(e);
}

bool WorldLayer::ChangeBlock(MC::MouseButtonPressedEvent& event)
{
	if ((MC::MC_KEYS)event.GetMouseButton() == MC::MC_KEYS::MC_BUTTON_LBUTTON)
	{
		MC::vec3 coords = MC::Trace::UnprojectCenterPixel(camera);

		uint32_t x = MC::floorf(coords.x);
		uint32_t y = MC::floorf(coords.y);
		uint32_t z = MC::floorf(coords.z);


		if (x > terrain.GetWidth() || y > terrain.GetHeight() || z > terrain.GetDepth() || x < 0 || y < 0 || z < 0)
			return false;

		terrain.RemoveBlock(x, y, z);


		return true;
	}

	if ((MC::MC_KEYS)event.GetMouseButton() == MC::MC_KEYS::MC_BUTTON_RBUTTON)
	{
		MC::vec3 coords = MC::Trace::UnprojectCenterPixel(camera);

		uint32_t x = MC::floorf(coords.x);
		uint32_t y = MC::floorf(coords.y);
		uint32_t z = MC::floorf(coords.z);

		int nx = x;
		int ny = y;
		int nz = z;

		if (x >= terrain.GetWidth() || y >= terrain.GetHeight() || z >= terrain.GetDepth() || x < 0 || y < 0 || z < 0)
			return false;

		if (MC::dti(coords.x) < MC::dti(coords.y))
			if (MC::dti(coords.x) < MC::dti(coords.z))
				if (camera.GetCameraPos().x > 0)
					nx--;
				else
					nx++;
			else
				if (camera.GetCameraPos().z > 0)
					nz--;
				else
					nz++;
		else
			if (MC::dti(coords.y) < MC::dti(coords.z))
				if (camera.GetCameraPos().y > 0)
					ny++;
				else
					ny--;
			else
				if (camera.GetCameraPos().z > 0)
					nz--;
				else
					nz++;

		terrain.PlaceBlock(nx, ny, nz);

		return true;
	}

	return false;
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
