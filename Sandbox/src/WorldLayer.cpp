#include "WorldLayer.h"

#include <iostream>

WorldLayer::WorldLayer() : Layer("WorldLayer")
{
	camera = MC::Camera({ 10.0f, 10.0f, 70.0f });
	Projection = MC::mat4::Perspective(45.0f, 1360 / 768, 0.1f, 100.0f);

	MC::RenderCommand::SetClearColor({ 1.0f, 0.0f, 0.5f, 1.0f });

	singleChunk = new MC::Chunk();

	shader = new MC::Shader("D:/dev/MineCloneProject/MineCloneProject/res/Shaders/chunkVertex.shader", "D:/dev/MineCloneProject/MineCloneProject/res/Shaders/chunkFragment.shader");
	shader->Bind();
}

void WorldLayer::OnUpdate(MC::DeltaTime deltaTime)
{
	LookAround();
	MovePlayer(deltaTime);


	MC::Renderer::Clear();
	MC::Renderer::BeginScene(camera, Projection);
	MC::Renderer::Draw(singleChunk, shader);
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
		dz = 2;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_S))
	{
		dz = -2;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_D))
	{
		dx = 2;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_A))
	{
		dx = -2;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_SPACE))
	{
		dy = 2;
	}

	if (MC::InputHandler::isKeyPressed(MC::MC_KEY_CTRL))
	{
		dy = -2;
	}

	camera.AddCameraTargetPosition(MC::vec3(dx, dy, dz) * cameraSpeed * deltaTime);
}


void WorldLayer::LookAround()
{

	MC::vec2 Delta = MC::InputHandler::GetMouseDelta();

	camera.SetCameraYaw(MC::toRadians(Delta.x));
	camera.SetCameraPitch(MC::toRadians(Delta.y));
	
	float pitch = camera.GetCameraPitch();

	if (pitch > 89.0f)
		camera.SetCameraPitch(89.0f);
	if (pitch < -89.0f)
		camera.SetCameraPitch(-89.0f);

	camera.UpdateCameraVectors();
}