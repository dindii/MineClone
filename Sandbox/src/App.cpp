#include <MC.h>

/*
* Detalhes sobre a implementação em Application.h
*/

class testLayer : public MC::Layer
{
public:
	testLayer() : Layer("testLayer")
	{
	
	
	};

	void OnUpdate() override;
	void OnEvent(MC::Event& e) override;
};

void testLayer::OnUpdate()
{
	MC_LOG_TRACE("Greetings from App!");
}

void testLayer::OnEvent(MC::Event& e)
{
	MC_LOG_TRACE(e);
}




class SandBoxApp : public MC::Application
{
public:
	SandBoxApp() { PushLayer(new testLayer()); };
	~SandBoxApp() {};
};

MC::Application* MC::CreateApplication()
{
	return new SandBoxApp();
}

//Separar todos os Layers em blocos proprios