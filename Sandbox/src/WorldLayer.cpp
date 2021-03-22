#include "WorldLayer.h"
#include "imgui/imgui.h"
#include "MCP/Physic/Utils.h"
#include "MCP/Physic/Ray.h"

#include <chrono>
WorldLayer::WorldLayer() : Layer("WorldLayer"), terrain(15, 32, 15)
{
	MC::Application* App = MC::Application::Get();

	float width  = (float)App->GetWindow().getWidth();
	float height = (float)App->GetWindow().getHeight();

	//Initialize camera's aspect ratio and its position in the world
	camera = MC::Camera(width / height, { 0.0f, 75.0f, 100.0f });

	//Camera lag is a linear interpolation between positions, just to make the camera movement smoother
	camera.SetCameraLag(true);
	camera.SetCameraLagValue(0.15000f);

	//Since we don't have any crosshair or support for it yet, we will make the mouse visible and we can use it to aim as it remain in the middle of the screen
	MC::InputHandler::showCursor(true);

	//Start our world check thread.
	WorldGenThread = new std::thread(&WorldLayer::ProcessTerrainNearPlayer, this, camera.GetCameraPos(), worldGenerationRadius);
}

WorldLayer::~WorldLayer()
{
	WorldGenThread->detach();
	delete WorldGenThread;
}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	//Let the player interact with the world
	LookAround();
	MovePlayer(deltaTime);

	//We don't have a queue of renderables objects or something like that for now, so we have to manually write the object we want to be shown
	MC::VoxelRenderer::Clear();
	MC::VoxelRenderer::BeginScene(camera);

	//Draw our terrain's data, this is, the super chunk with every chunk in this region (as well as its VBO inside)
	MC::VoxelRenderer::Draw(terrain.GetTerrainData());
	
	//Do some flush job or so
	MC::VoxelRenderer::EndScene();
}

void WorldLayer::OnEvent(MC::Event& e)
{
	//Our camera may need some events, for example, an window resize event would be good for the camera adjust its aspect ratio
	camera.OnEvent(e);

	//We then make an Dispatcher which is a class that takes the event and check if the type of this event matches with the template arg, if so, call this function
	//with this event
	MC::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MC::MouseButtonPressedEvent>(BIND_EVENT_FN(WorldLayer::ChangeBlock));
}

bool WorldLayer::ChangeBlock(MC::MouseButtonPressedEvent& event)
{
	MC::Application* App = MC::Application::Get();

	float width =  (float)App->GetWindow().getWidth();
	float height = (float)App->GetWindow().getHeight();
	
	//Trace from the center of the screen to the world
	MC::Trace direction((width / 2), (height / 2), camera);

	//Everytime we miss a block, we will add distancePerStep in our ray direction
	float   distancePerStep = 1.0f;

	//Store our actual step
	uint8_t stepCount = 0;
	
	//The resultant trace, i.e: the position where we trace the ray, plus the direction we are aiming times the step distance
	MC::vec3 trace;

	//This will be used for placing blocks. We take the last position before finding a block and fill this position thus placing a block before the existing block
	//and not setting the same block twice
	MC::vec3 lastTraceStep;

	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t z = 0;

	bool foundBlock = false;

	while (stepCount < rangeToInteractWithBlock)
	{
		trace = camera.GetCameraPos() + direction.getDirection() * distancePerStep;

		//Negative world positions conversions would result in negative array indexes, so avoid
		if (trace.x < 0.0f || trace.y < 0.0f || trace.z < 0.0f)
			return false;

		x = uint32_t(trace.x);
		y = uint32_t(trace.y);
		z = uint32_t(trace.z);

		if (terrain.GetTerrainData()->GetVoxel(x, y, z))
		{
			foundBlock = true;
			break;
		}

		//Everytime we miss a block, adds 0.5f to our distancePerStep so we can go even further. In this case it's 0.5f and not 1.0f because it is more precise
		distancePerStep += 0.5f;
		stepCount++;	

		lastTraceStep = trace;
	}

	//If we found a block, check the mouse button and interact with this block
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

void WorldLayer::ProcessTerrainNearPlayer(MC::vec3 CameraPosition, float radius)
{
	//This will be used to avoid unecessary calculations, this is, don't calc anything if we didn't move
	MC::vec3 cacheCamera(0.0f);

	while (true)
	{
		//Our center position, this is, where we are and we will gen the world around us (the center)
		MC::vec3 center = camera.GetCameraPos();

		//If the position is the same, don't calc
		if(center != cacheCamera)
			for (int x = (center.x - radius); x <= (center.x + radius); x += MC::CHUNK_SIZE) //We will gen our chunks in a circle fashion way
				for (int z = (center.z - radius); z <= center.z + radius; z += MC::CHUNK_SIZE)
				{
					float distance = sqrt(pow(x - center.x, 2) + pow(z - center.z, 2));      //For this, we will use this nested loop to calc its radius
			
					//If we are inside the radius, then, gen this chunk
					if (distance < radius)
						terrain.GenNoiseChunk(x, terrain.GetHeight(), z, octaves, frequency, persistence, 0.0f, 0.0f);
				}	

		
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			cacheCamera = center;
	}

}

void WorldLayer::OnImGuiRender()
{
	ImGui::SliderInt("Octaves", &octaves, 0, 8);
	ImGui::SliderFloat("Frequency", &frequency, 0.0f, 10.0f);
	ImGui::SliderFloat("Persistance", &persistence, 0.0f, 1.0f);

	ImGui::NewLine();

	//The buttons in our block selector
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

	//Add this vector on the Target Position, this is, where we are looking at, thus, making a free camera style
	camera.AddCameraTargetPosition(gotoCamera, deltaTime);	
}

void WorldLayer::LookAround()
{
	//Get the mouse delta, i.e: the relation between the last mouse position and the actual position
	MC::vec2 Delta = MC::InputHandler::GetMouseDelta();

	//Takes this delta, multiply by the current mouse sensitivity and applies to the camera pitch and yaw
	camera.SetCameraPitch(MC::toRadians(Delta.y * cameraSens));
	camera.SetCameraYaw(MC::toRadians(Delta.x * cameraSens));
}
