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


	float cameraSpeed = 100.5f;
	float cameraSens = 0.5f;
	float actualCameraSpeed = 0.0f;
	float accelRate = 5.0f;
	MC::vec2 DeltaReverse;


	MC::Superchunk* superChunk;

	MC::Shader* shader;
	MC::Camera camera;
};