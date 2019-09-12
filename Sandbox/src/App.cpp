#include <MC.h>


/*
* Detalhes sobre a implementação em Application.h
*/

class SandBoxApp : public MC::Application
{
public:
	SandBoxApp() {};
	~SandBoxApp() {};
};

MC::Application* MC::CreateApplication()
{
	return new SandBoxApp();
}