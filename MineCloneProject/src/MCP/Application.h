#pragma once

namespace MC
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

	private:
		static Application* s_Instance;
		
	private:
		bool m_Running;
		
	};

	Application* CreateApplication();

}