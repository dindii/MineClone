#include "mcpch.h"
#include "Application.h"


int main()
{
	MC::Application* App = MC::CreateApplication();
	App->Run();

	delete App;

	return 0;
}