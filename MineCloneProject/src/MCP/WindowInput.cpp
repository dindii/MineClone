#include "mcpch.h"
#include "WindowInput.h"
#include "Utils/Logger.h"
namespace MC
{
	LRESULT CALLBACK WindowInput::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			case WM_KEYDOWN:
			{
				MC_LOG_TRACE("Something happened!");
				break;
			}

			default:
			{
				return DefWindowProc(hwnd, msg, wparam, lparam);
			}
		}

		return NULL;
	}

}