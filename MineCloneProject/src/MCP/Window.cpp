#include "mcpch.h"
#include "Window.h"
#include "Utils/Logger.h"

//TEMPORARY
#include "glad/glad.h"

namespace MC
{

	Window::Window(uint32_t Width, uint32_t Height, const char* Name)
	{

		MC_LOG_TRACE("Initializing Engine!");

		m_Details = new WindowProperties(Width, Height, Name);
		m_WindowInput = new WindowInput(m_NativeWindow, /* @TODO: Tirar o width e height e deixar so o hwnd*/ m_Details->Width, m_Details->Height);


		WNDCLASSEX wc;
		wc.cbClsExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = NULL;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = NULL;
		wc.lpszClassName = "MCloneWindow";
		wc.lpszMenuName = "";
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = &WindowInput::WndProc;

		if (!RegisterClassEx(&wc)) 
		MC_LOG_FATAL("Failed to create Window!");


		m_NativeWindow = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MCloneWindow", m_Details->Name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			m_Details->Width, m_Details->Height,
			NULL, NULL, NULL, this);

		ShowWindow(m_NativeWindow, SW_SHOW);
		SetActiveWindow(m_NativeWindow);

		loadGraphicsContext();

	}

	void Window::loadGraphicsContext()
	{
		m_Context = GetDC(m_NativeWindow);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};


		int pixelFormatNumber = ChoosePixelFormat(m_Context, &pfd);

		if (!pixelFormatNumber)
			MC_LOG_FATAL("Could not find a proper pixel format.");

		SetPixelFormat(m_Context, pixelFormatNumber, &pfd);

		HGLRC GLRC = wglCreateContext(m_Context);


		if (!wglMakeCurrent(m_Context, GLRC))
			MC_LOG_FATAL("Failed to make OpenGL as current context.");

		if (!gladLoadGL())
		{
			MC_LOG_FATAL("Failed to load OpenGL (Glad).");
		}


		MC_LOG_TRACE((char*)glGetString(GL_VENDOR));
		MC_LOG_TRACE((char*)glGetString(GL_VERSION));
		

		//Setup the first OpenGL call
		glViewport(0, 0, m_Details->Width, m_Details->Height); //@TODO: Mover isso para outro lugar que lide apenas com OpenGL calls.
	}

	Window::~Window()
	{
		delete m_Details;
		delete m_WindowInput;

		if (GetDC(m_NativeWindow))
			if (!wglMakeCurrent(NULL, NULL))

		DestroyWindow(m_NativeWindow);
	}

	void Window::onUpdate()
	{
		swapBuffers();
		pollEvents();
		

		// @TODO: Quando passar para MT, lockar a thread apos setar o clipcursor e atualizar o RECT em alguma mensagem de window resize.S

		//RECT r;
		//GetWindowRect(m_NativeWindow, &r);
		//ClipCursor(&r);
		//ShowCursor(false);

	}

	bool Window::pollEvents()
	{
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(0);

		return true;
	}

	void Window::swapBuffers() const
	{
		SwapBuffers(m_Context);
	}

}