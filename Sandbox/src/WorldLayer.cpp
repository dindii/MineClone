#include "WorldLayer.h"


WorldLayer::WorldLayer() : Layer("WorldLayer")
{  
	camera = MC::Camera({ 0.0f, 0.0f, 0.0f });
	Projection = MC::mat4();
	Projection = MC::mat4::Perspective(45.0f, 1.8f, 0.1f, 100.0f);

	MC::RenderCommand::SetClearColor({ 1.0f, 0.0f, 0.5f, 1.0f });

	singleChunk = new MC::Chunk();

	shader = new MC::Shader("D:/dev/MineCloneProject/MineCloneProject/res/Shaders/chunkVertex.shader", "D:/dev/MineCloneProject/MineCloneProject/res/Shaders/chunkFragment.shader");
	shader->Bind();
}

void WorldLayer::OnUpdate()
{
	MC::Renderer::Clear();
	MC::Renderer::BeginScene(camera, Projection);
	MC::Renderer::Draw(singleChunk, shader);
}

void WorldLayer::OnEvent(MC::Event& e)
{
	MC_LOG_TRACE(e);
}