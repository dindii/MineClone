#include "WorldLayer.h"
#include <iostream>
#include "MCP/Noise/PerlinNoise2D.h"

#include "imgui/imgui.h"

WorldLayer::WorldLayer() : Layer("WorldLayer")
{

	MC::PerlinNoise Noise;

	camera = MC::Camera(1362 / 701, { 10.0f, 10.0f, 500.0f });

	superChunk = new MC::Superchunk();

	//Colocar esse set numa função
	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 64; y++)
			for (int z = 0; z < 32; z++)
			{ 
				double should = Noise.GenOctave(x / 32.0f, y / 64.0f, z / 32.0f, 4, 1.5f, 0.25f);

				 if(should * 32.0f > y)
					 superChunk->Set(x, y, z, 1);

				 else
					 superChunk->Set(x, y, z, 0);
				 
			}	
}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	MovePlayer(deltaTime);

	MC::VoxelRenderer::Clear();
	MC::VoxelRenderer::BeginScene(camera);
	MC::VoxelRenderer::Draw(superChunk);
}

void WorldLayer::OnEvent(MC::Event& e)
{
	camera.OnEvent(e);
}

void WorldLayer::OnImGuiRender()
{
	bool a = true;
	ImGui::ShowDemoWindow(&a);
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

//@TODO: mover para um controller
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