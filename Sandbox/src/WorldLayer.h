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
	float cameraSens = 1.0f;
	float lastX = 680, lastY = 380; //@TODO: MC::Aplication::GetWindow();

	MC::vec2 mMouseDelta, m_PrevMouseCoords, m_MouseCoords;
	//
	MC::Chunk* singleChunk;

	MC::Shader* shader;
	MC::Camera camera;
	MC::mat4 Projection;
};
