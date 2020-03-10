#include "WorldLayer.h"

#include <iostream>

WorldLayer::WorldLayer() : Layer("WorldLayer")
{
	camera = MC::Camera({ 10.0f, 10.0f, 70.0f });
	Projection = MC::mat4::Perspective(45.0f, 1360 / 768, 0.1f, 100.0f);
	MC::Renderer::SetClearColor({ 1.0f, 0.0f, 0.5f, 1.0f });

	superChunk = new MC::Superchunk();
	
	//@TODO: Fazer o Draw no SuperChunk ao invés de ficar desenhando cubos individuais. 
	//16*16*16 chunks, 16*16*16*16 blocks.
	for (int x = 0; x < 64; x++)
		for (int y = 0; y < 64; y++)
			for (int z = 0; z < 64; z++)
				superChunk->Set(x, y, z, 1);

	shader = new MC::Shader("res/Shaders/chunkVertex.shader", "res/Shaders/chunkFragment.shader");
	shader->Bind();

	MC::InputHandler::lockCursorPosition(false);
}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	MovePlayer(deltaTime);


	MC::Renderer::Clear();
	MC::Renderer::BeginScene(camera, Projection);
	MC::Renderer::Draw(superChunk, shader);
}

void WorldLayer::OnEvent(MC::Event& e)
{
	MC_LOG_TRACE(e);
}

void WorldLayer::MovePlayer(MC::DeltaTime deltaTime)
{
	float dx = 0, dz = 0, dy = 0;

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_W))
	{
		dz = cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_S))
	{
		dz = -cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_D))
	{
		dx = cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_A))
	{
		dx = -cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_SPACE))
	{
		dy = cameraSpeed;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_CTRL))
	{
		dy = -cameraSpeed;
	}

	camera.AddCameraTargetPosition(MC::vec3(dx, dy, dz) * deltaTime);
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