#pragma once
#include "WorldLayer.h"
#include <MC.h>

class WorldLayer : public MC::Layer
{
public:
	WorldLayer();
	void OnUpdate(MC::DeltaTime deltaTime) override;
	void OnEvent(MC::Event& e) override;


	//Gameplay Related Stuff
	void MovePlayer(MC::DeltaTime deltaTime);
	void LookAround();


	float cameraSpeed = 10.5f;
	float cameraSens = 0.5f;
	MC::vec2 DeltaReverse;


	MC::Chunk* singleChunk;

	MC::Shader* shader;
	MC::Camera camera;
	MC::mat4 Projection;
};
