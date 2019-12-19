#pragma once
#include "WorldLayer.h"
#include <MC.h>

class WorldLayer : public MC::Layer
{
public:
	WorldLayer();
	void OnUpdate() override;
	void OnEvent(MC::Event& e) override;



	MC::Ref<MC::Shader> Shader;
	MC::Ref<MC::Camera> Camera;
	MC::Ref<MC::mat4> Projection;
};
