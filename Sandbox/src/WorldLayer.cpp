#include "WorldLayer.h"
#include "imgui/imgui.h"
#include "MCP/Physic/Utils.h"
#include "MCP/Physic/Ray.h"


WorldLayer::WorldLayer() : Layer("WorldLayer"), terrain(1, 1, 1)
{
	MC::Application* App = MC::Application::Get();

	float width  = (float)App->GetWindow().getWidth();
	float height = (float)App->GetWindow().getHeight();

	camera = MC::Camera(width / height, { 0.0f, 0.0f, -100.0f });

	camera.SetCameraLag(true);
	camera.SetCameraLagValue(0.15000f);

	terrain.GenNoiseTerrain(VoxelTerrain::TerrainType::Terrain3D, octaves, frequency, persistence, 0.0f, 0.0f);

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

	float width =  (float)App->GetWindow().getWidth();
	float height = (float)App->GetWindow().getHeight();
	
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

	while (stepCount < 64)
	{
		trace = camera.GetCameraPos() + direction.getDirection() * distancePerStep;

		if (trace.x < 0.0f || trace.y < 0.0f || trace.z < 0.0f)
			return false;

		x = uint32_t(trace.x);
		y = uint32_t(trace.y);
		z = uint32_t(trace.z);

		if (terrain.GetTerrainData()->Get(x, y, z))
		{
			foundBlock = true;
			break;
		}

		distancePerStep += 0.5f;
		stepCount++;	

		lastTraceStep = trace;
	}

	if (foundBlock)
	{
		if (event.GetMouseButton() == MC::MC_KEYS::MC_BUTTON_LBUTTON)
			terrain.RemoveBlock(x, y, z);

		if (event.GetMouseButton() == MC::MC_KEYS::MC_BUTTON_RBUTTON)
		{
			x = (uint32_t)lastTraceStep.x, y = (uint32_t)lastTraceStep.y, z = (uint32_t)lastTraceStep.z;
            terrain.PlaceBlock(x, y, z, selectedBlock);
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

	ImGui::NewLine();

	//Blocks image buttons
	{
		ImGui::Text("Blocks: ");

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_GRASS)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = BLOCK_GRASS;
		ImGui::SameLine();


		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_SAND)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_SAND;
		ImGui::SameLine();


		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_WOOD)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_WOOD;

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_STONE)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_STONE;
		ImGui::SameLine();


		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_BLACK_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_BLACK_WOOL;
		ImGui::SameLine();


		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_BLUE_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_BLUE_WOOL;

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_BROWN_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_BROWN_WOOL;
		ImGui::SameLine();


		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_CYAN_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_CYAN_WOOL;
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_GRAY_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_GRAY_WOOL;

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_GREEN_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_GREEN_WOOL;
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_LIGHT_BLUE_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_LIGHT_BLUE_WOOL;
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_LIGHT_GRAY_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_LIGHT_GRAY_WOOL;

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_LIME_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_LIME_WOOL;
		ImGui::SameLine();


		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_MAGENTA_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_MAGENTA_WOOL;
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_ORANGE_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_ORANGE_WOOL;

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_PURPLE_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_PURPLE_WOOL;
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_RED_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_RED_WOOL;
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_WHITE_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_WHITE_WOOL;

		if (ImGui::ImageButton((ImTextureID)terrain.GetTexture(EBlockType::BLOCK_YELLOW_WOOL)->TopTexture->GetID(), { 50.0f, 50.0f }))
			selectedBlock = EBlockType::BLOCK_YELLOW_WOOL;
	}
}

void WorldLayer::ReGenTerrain()
{
	terrain.GenNoiseTerrain(VoxelTerrain::TerrainType::Terrain3D, octaves, frequency, persistence, xOffset, yOffset);
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
