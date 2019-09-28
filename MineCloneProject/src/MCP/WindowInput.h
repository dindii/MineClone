#pragma once
#include <windows.h>


namespace MC
{
	class WindowInput
	{
	public:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	};
}