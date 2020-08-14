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

	float cameraSpeed = 50.5f, cameraSens = 1.0f;

	MC::VoxelTerrain terrain;
	MC::Camera camera;

	int octaves = 0;
	float persistence = 0, frequency = 0, previewSize = 290.0f;

	
	MC::vec2 DeltaReverse; //@TDO: Improve the mouse input system and get rid of this.
};
