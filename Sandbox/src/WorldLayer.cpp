#include "WorldLayer.h"

#include <iostream>

//EXPERIMENTAL CODE

WorldLayer::WorldLayer() : Layer("WorldLayer")
{


	camera = MC::Camera(1362 / 701, { 10.0f, 10.0f, 500.0f });

	superChunk = new MC::Superchunk();

	// x + y + z * 4

	//Colocar esse set numa função
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			for (int z = 0; z < 4; z++)
			{ 
				superChunk->Set(x, y, z, 1);

				//perlinPos[x + 4 * (y + 4 * z)] = noise.Gen(x, y, z);
				perlinPos[x][y][z] = noise.Gen(x, y, z);
		

				//Aqui eu seto os cubos do chunk e depois no onUpdate eu renderizo o chunk, onde ele ira renderizar tudo, porém, apenas com os cubos setados.
			}
	
}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	MovePlayer(deltaTime);

	MC::VoxelRenderer::Clear();
	MC::VoxelRenderer::BeginScene(camera);
	MC::VoxelRenderer::Draw(superChunk, perlinPos);
}

void WorldLayer::OnEvent(MC::Event& e)
{
	//MC_LOG_TRACE(e);
	camera.OnEvent(e);
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

//@TODO: mover também para um controller
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