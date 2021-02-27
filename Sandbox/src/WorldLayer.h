#pragma once
#include "WorldLayer.h"
#include <MC.h>

class WorldLayer : public MC::Layer
{
public:
	//Inherited
	WorldLayer();
	void OnUpdate(MC::DeltaTime deltaTime) override;
	void OnEvent(MC::Event& e) override;
	void OnImGuiRender() override;

	//Gameplay Related Stuff
	void MovePlayer(MC::DeltaTime deltaTime);
	void LookAround();
	void ReGenTerrain();
	bool ChangeBlock(MC::MouseButtonPressedEvent& event);


	float cameraSpeed = 50.5f, cameraSens = 1.0f;

	MC::VoxelTerrain terrain;
	MC::Camera camera;

	int octaves = 1;
	float persistence = 0.25f, frequency = 2.865f, previewSize = 290.0f, xOffset = 0.0f, yOffset = 0.0f;
};
