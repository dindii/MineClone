#pragma once
#include "WorldLayer.h"
#include <MC.h>
#include "VoxelTerrain.h"

class WorldLayer : public MC::Layer
{
public:
	WorldLayer();

	//Native
	void OnUpdate(MC::DeltaTime deltaTime) override;
	void OnEvent(MC::Event& e) override;
	void OnImGuiRender() override;

	//Gameplay Related Stuff
	void MovePlayer(MC::DeltaTime deltaTime);
	void LookAround();
	void ReGenTerrain();
	bool ChangeBlock(MC::MouseButtonPressedEvent& event);

	//Camera properties
	MC::Camera camera;
	float cameraSprintSpeed = 200.0f, cameraWalkSpeed = 20.0f, cameraSpeed = 10.0f; 
	float cameraSens = 1.0f;

	//Terrain Properties
	VoxelTerrain terrain;
	int octaves = 1;
	float persistence = 0.25f, frequency = 1.000f, previewSize = 290.0f, xOffset = 0.0f, yOffset = 0.0f;
	EBlockType selectedBlock = EBlockType::BLOCK_GRASS;

	void ProcessTerrainNearPlayer(MC::vec3 CameraPosition, float GenChunkDistance, uint32_t ChunksGen, float radius);

	//Mechanics 
};
