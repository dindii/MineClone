#include "mcpch.h"
#include "Application.h"

#include <thread>
int main()
{
	MC::Application* App = MC::CreateApplication();
	
	App->Run();
	delete App;

	return 0;
}