#pragma once
#include <windows.h>
#include <tchar.h>
#include "IO/WindowInput.h"

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
		void swapBuffers() const;
		
		inline uint32_t	getWidth() const {  return m_Details->Width; }  
		inline uint32_t getHeight() const { return m_Details->Height; }

		inline void	setWidth(const uint32_t width)    { m_Details->Width = width; }  
		inline void setHeight(const uint32_t height)  { m_Details->Height = height; }

		inline const char* getName() const { return m_Details->Name; }
		inline HWND GetNativeWindow() const { return m_NativeWindow; }


		inline void setEventCallback(const EventCallbackFn& callback) { m_WindowInput->setEventCallback(callback); }

	private:
		void loadGraphicsContext();

	private:
		HWND m_NativeWindow;
		HDC m_Context;
		HGLRC m_OpenGLContext;

		WindowProperties* m_Details;
		MC_INTERNAL::WindowInput* m_WindowInput;

		EventCallbackFn EventCallback;
	};



}