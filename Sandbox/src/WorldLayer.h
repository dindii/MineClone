#pragma once
#include "WorldLayer.h"
#include <MC.h>
#include "VoxelTerrain.h"
#include <thread>

class WorldLayer : public MC::Layer
{
public:
	WorldLayer();
	~WorldLayer();

	///Native

	//Tick function, called every frame
	void OnUpdate(MC::DeltaTime deltaTime) override;
	
	//Function that receives an event if it occurs
	void OnEvent(MC::Event& e) override;

	//Function that can call ImGui functions (as well as update it)
	void OnImGuiRender() override;

	///Gameplay Related Stuff

	//This will check if the movement keys are being hold
	void MovePlayer(MC::DeltaTime deltaTime);

	//Takes input from the mouse and pass it to the camera
	void LookAround();

	//Trace a line from the camera to the block and based on the key, remove or place a block
	bool ChangeBlock(MC::MouseButtonPressedEvent& event);

	//Our range to place or remove blocks
	float rangeToInteractWithBlock = 32;

	//Camera properties
	MC::Camera camera;
	float cameraSprintSpeed = 200.0f, cameraWalkSpeed = 20.0f, cameraSpeed = 10.0f; 
	float cameraSens = 1.0f;

	//Terrain and Perlin Noise Properties
	VoxelTerrain terrain;
	int octaves = 1;
	float persistence = 0.25f, frequency = 0.800f;
	float worldGenerationRadius = 120.0f;
	
	//The actual selected block (in case of placing a block)
	EBlockType selectedBlock = EBlockType::BLOCK_GRASS;

	//This function constantly checks if theres a non existent chunk in a raidus and if so, gen a new chunk using noise.
	void ProcessTerrainNearPlayer(MC::vec3 CameraPosition, float radius);

	//A manual thread that will be responsible for generating the terrain in order to not block the renderer, inputs etc
	std::thread* WorldGenThread;

};
