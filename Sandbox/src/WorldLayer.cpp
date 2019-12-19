#include "WorldLayer.h"


WorldLayer::WorldLayer() : Layer("WorldLayer")
{
	Shader.reset(new MC::Shader("D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testVertexShader.shader", "D:\\dev\\MineCloneProject\\MineCloneProject\\src\\MCP\\testFragmentShader.shader"));
	Camera.reset(new MC::Camera({ 0.0f, 0.0f, 0.0f }));
	Projection.reset(new MC::mat4);
	*Projection = MC::mat4::Perspective(45.0f, 1.8f, 0.1f, 100.0f);
}

void WorldLayer::OnUpdate()
{
	//Clear
	//Draw
	//End
}

void WorldLayer::OnEvent(MC::Event& e)
{
	MC_LOG_TRACE(e);
}