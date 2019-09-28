#pragma once
#include <windows.h>
#include <tchar.h>
#include "WindowInput.h"

namespace MC
{
	struct WindowProperties
	{
		WindowProperties(uint32_t c_Width, uint32_t c_Height, const char* c_Name) :
		Width(c_Width), Height(c_Height), Name(c_Name) {};

		uint32_t Width, Height;
		const char* Name;
	};

	class Window
	{
	public:
		Window(uint32_t Width, uint32_t Height, const char* Name);
		~Window();

		void onUpdate();
		bool pollEvents();
		
		inline uint32_t	getWidth() const {  m_Details->Width; }
		inline uint32_t getHeight() const { m_Details->Height; }
		inline const char* getName() const { m_Details->Name; }

	private:
		void loadGraphicsContext();

	private:
		HWND m_NativeWindow;
		HDC m_Context;
		HGLRC m_OpenGLContext;

		WindowProperties* m_Details;
		WindowInput* m_WindowInput;
	};



}