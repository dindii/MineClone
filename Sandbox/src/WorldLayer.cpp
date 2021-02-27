#include "WorldLayer.h"
#include "imgui/imgui.h"
#include "MCP/Physic/Utils.h"
#include "MCP/Physic/Ray.h"


WorldLayer::WorldLayer() : Layer("WorldLayer"), terrain(32, 64, 32)
{
	MC::Application* App = MC::Application::Get();

	uint32_t width = App->GetWindow().getWidth();
	uint32_t height = App->GetWindow().getHeight();

	camera = MC::Camera(float(width) / float(height), { 0.0f, 0.0f, -500.0f });

	camera.SetCameraLag(true);
	camera.SetCameraLagValue(0.15000f);


	terrain.GenNoiseTerrain(MC::VoxelTerrain::TerrainType::Terrain3D, octaves, frequency, persistence, 0.0f, 0.0f);

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

	//MC_LOG_TRACE(e);
}

bool WorldLayer::ChangeBlock(MC::MouseButtonPressedEvent& event)
{
	MC::Application* App = MC::Application::Get();

	float width = App->GetWindow().getWidth();
	float height = App->GetWindow().getHeight();
	
	//Trace from viewport from world coords
	MC::Trace direction((width / 2), (height / 2), camera);

	float   distancePerStep = 1.0f;
	uint8_t stepCount = 0;
	MC::vec3 trace;
	MC::vec3 lastTraceStep;

	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t z = 0;

	bool foundBlock = false;

	while (stepCount < 30)
	{
		trace = camera.GetCameraPos() + direction.getDirection() * distancePerStep;

		x = (trace.x);
		y = (trace.y);
		z = (trace.z);

		if (terrain.GetTerrainData()->Get(x, y, z))
		{
			foundBlock = true;
			break;
		}

		distancePerStep += 1.0f;
		stepCount++;	

		lastTraceStep = trace;
	}

	if (foundBlock)
	{
		if (event.GetMouseButton() == MC::MC_KEYS::MC_BUTTON_LBUTTON)
			terrain.RemoveBlock(x, y, z);

		if (event.GetMouseButton() == MC::MC_KEYS::MC_BUTTON_RBUTTON)
		{
			x = lastTraceStep.x, y = lastTraceStep.y, z = lastTraceStep.z;
            terrain.PlaceBlock(x, y, z);
		}
	}

	return true;
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
}

void WorldLayer::LookAround()
{
	MC::vec2 Delta = MC::InputHandler::GetMouseDelta();

	camera.SetCameraPitch(MC::toRadians(Delta.y * cameraSens));
	camera.SetCameraYaw(MC::toRadians(Delta.x * cameraSens));
}
