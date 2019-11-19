#include "mcpch.h"
#include "Utils/Logger.h"
#include "Application.h"


int main()
{
	MC::Debug::Logger s_Logger;

	MC::Application* App = MC::CreateApplication();
	App->Run();

	delete App;

	return 0;
}