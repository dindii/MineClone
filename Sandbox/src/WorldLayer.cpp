#include "WorldLayer.h"

#include <iostream>

//EXPERIMENTAL CODE

WorldLayer::WorldLayer() : Layer("WorldLayer")
{


	camera = MC::Camera(1362 / 701, { 10.0f, 10.0f, 500.0f });
	MC::Renderer::SetClearColor({ 1.0f, 0.0f, 0.5f, 1.0f });

	superChunk = new MC::Superchunk();
	
	//@TODO: Fazer o Draw no SuperChunk ao invés de ficar desenhando cubos individuais. 
	//16*16*16 chunks, 16*16*16*16 blocks.

	std::vector<MC::vec3> noisePos;

	//float perlinPos[4 * 4 * 4];


	// x + y + z * 4


	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			for (int z = 0; z < 4; z++)
			{ 
				superChunk->Set(x, y, z, 1);

				//perlinPos[x + 4 * (y + 4 * z)] = noise.Gen(x, y, z);
				perlinPos[x][y][z] = noise.Gen(x, y, z);
		

				//Aqui eu seto os cubos do chunk e depois no onUpdate eu renderizo o chunk, onde ele ira renderizar tudo, porém, apenas com os cubos setados.
			}
	
	shader = new MC::Shader("res/Shaders/chunkVertex.shader", "res/Shaders/chunkFragment.shader");
	shader->Bind();

	//MC::InputHandler::lockCursorPosition(false);
	

}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	MovePlayer(deltaTime);

	MC::Renderer::Clear();
	MC::Renderer::BeginScene(camera);
	MC::Renderer::Draw(superChunk, shader, perlinPos);
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

	camera.AddCameraTargetPosition((gotoCamera) * deltaTime);	
}


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