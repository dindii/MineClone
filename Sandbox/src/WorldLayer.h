#pragma once
#include "WorldLayer.h"
#include <MC.h>

class WorldLayer : public MC::Layer
{
public:
	WorldLayer();
	void OnUpdate() override;
	void OnEvent(MC::Event& e) override;

	MC::Chunk* singleChunk;

	MC::Shader* shader;
	MC::Camera camera;
	MC::mat4 Projection;
};
