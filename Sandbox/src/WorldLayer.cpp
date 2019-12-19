#include "WorldLayer.h"


WorldLayer::WorldLayer() : Layer("WorldLayer")
{
	Camera.reset(new MC::Camera({ 0.0f, 0.0f, 0.0f }));
	Projection.reset(new MC::mat4);
	*Projection = MC::mat4::Perspective(45.0f, 1.8f, 0.1f, 100.0f);

	MC::RenderCommand::SetClearColor({ 1.0f, 0.0f, 0.5f, 1.0f });
}

void WorldLayer::OnUpdate()
{
	MC::Renderer::Clear();
	//Draw
	//End
}

void WorldLayer::OnEvent(MC::Event& e)
{
	MC_LOG_TRACE(e);
}