#include "WorldLayer.h"
#include "imgui/imgui.h"

WorldLayer::WorldLayer() : Layer("WorldLayer")
{
	camera = MC::Camera(1362 / 701, { 10.0f, 10.0f, 500.0f });
	terrain.Gen2DNoiseTerrain(64, 64, 0, 1, frequency, persistence);
}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	MovePlayer(deltaTime);

	MC::VoxelRenderer::Clear();
	MC::VoxelRenderer::BeginScene(camera);
	MC::VoxelRenderer::Draw(terrain);
}

void WorldLayer::OnEvent(MC::Event& e)
{
	camera.OnEvent(e);
}

void WorldLayer::OnImGuiRender()
{

	ImGui::Image((void*)(intptr_t)terrain.GetTerrainPreview().GetID(), 
		ImVec2{ previewSize , previewSize });
	
	ImGui::Text("size = %d x %d", terrain.GetTerrainPreview().GetWidth(), terrain.GetTerrainPreview().GetHeight());
	ImGui::Text("ID = %i", terrain.GetTerrainPreview().GetID());
	ImGui::SliderFloat("Preview Size", &previewSize, 0, 1000);
	
	ImGui::NewLine();
	
	//#TODO Generate 2D images without interference of the Z-terrain.
	if(ImGui::SliderInt("Octaves", &octaves, 0, 8) ||
	   ImGui::SliderFloat("Frequency", &frequency, 0.0f, 10.0f) ||
	   ImGui::SliderFloat("Persistance", &persistence, 0.0f, 1.0f))
	{
		ReGenTerrain();
	}
}

void WorldLayer::ReGenTerrain()
{
	terrain.Gen2DNoiseTerrain(64, 64, 0, octaves, frequency, persistence);
}

void WorldLayer::MovePlayer(MC::DeltaTime deltaTime)
{
	MC::vec3 gotoCamera;

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_W))
	{
		gotoCamera.z = cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_S))
	{
		gotoCamera.z = -cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_D))
	{
		gotoCamera.x = cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_A))
	{
		gotoCamera.x = -cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_SPACE))
	{
		gotoCamera.y = cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEYS::MC_KEY_CTRL))
	{
		gotoCamera.y = -cameraSpeed;
	}

	camera.AddCameraTargetPosition(gotoCamera, deltaTime);	
}

//#TODO: mover para um controller
void WorldLayer::LookAround()
{
	MC::vec2 Delta = MC::InputHandler::GetMouseDelta();

	camera.SetCameraPitch(MC::toRadians(Delta.y * cameraSens));
	camera.SetCameraYaw(MC::toRadians(Delta.x * cameraSens));

	float pitch = camera.GetCameraPitch();

 	if (pitch > 89.0f || pitch < -89.0f)
 	{
		DeltaReverse.x = Delta.x;
 		MC::InputHandler::setMouseDelta(DeltaReverse);
 	}
 	else
 	{
		DeltaReverse = Delta;
 	}
}
