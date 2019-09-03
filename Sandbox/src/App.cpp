#include <MC.h>


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