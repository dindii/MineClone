#pragma once
#include <windows.h>
#include "MCP/Event/Event.h"
#include "MCP/Event/KeyEvent.h"
#include "MCP/Event/MouseEvent.h"
#include "MCP/Event/ApplicationEvent.h"
#include <functional>

namespace MC
{
	union KeyInfo
	{
		LPARAM lparam;

		struct
		{
			WORD nRepeatCount : 16;
			BYTE nScanCode : 8;
			BYTE nExtended : 1;
			BYTE nReserved : 4;
			BYTE nContext : 1;
			BYTE nPrevious : 1;
			BYTE nTransition : 1;
		};
	};
	
	using EventCallbackFn = std::function<void(Event&)>;

	class WindowInput
	{
	public:
		WindowInput();
		~WindowInput();

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	public:

		inline void setEventCallback(const EventCallbackFn& callback) { EventCallback = callback; }
	private:
		static uint8_t* Keys;
		static EventCallbackFn EventCallback;
	};


	enum MC_KEYS : unsigned char
	{
		MC_BUTTON_LBUTTON = 1,
		MC_BUTTON_RBUTTON = 2,
		MC_BUTTON_MBUTTON = 3,
		MC_BUTTON_EXTRA1 = 4,
		MC_BUTTON_EXTRA2 = 5,

		MC_KEY_CTRL = 6,
		MC_KEY_TAB = 7,
		MC_KEY_BACKSPACE = 8,
		MC_KEY_ENTER = 9,
		MC_KEY_SHIFT = 10,
		MC_KEY_ALT = 11,
		MC_KEY_CAPS = 12,
		MC_KEY_ESC = 13,
		MC_KEY_SPACE = 14,
		MC_KEY_PAGE_UP = 15,
		MC_KEY_PAGE_DOWN = 16,
		MC_KEY_END = 17,
		MC_KEY_HOME = 18,
		MC_KEY_LEFT = 19,
		MC_KEY_UP = 20,
		MC_KEY_RIGHT = 21,
		MC_KEY_DOWN = 22,
		MC_KEY_SELECT = 23,
		MC_KEY_INSERT = 24,
		MC_KEY_DELETE = 25,

		MC_KEY_0 = 26,
		MC_KEY_1 = 27,
		MC_KEY_2 = 28,
		MC_KEY_3 = 29,
		MC_KEY_4 = 30,
		MC_KEY_5 = 31,
		MC_KEY_6 = 32,
		MC_KEY_7 = 33,
		MC_KEY_8 = 34,
		MC_KEY_9 = 35,

		MC_KEY_A = 36,
		MC_KEY_B = 37,
		MC_KEY_C = 38,
		MC_KEY_D = 39,
		MC_KEY_E = 40,
		MC_KEY_F = 41,
		MC_KEY_G = 42,
		MC_KEY_H = 43,
		MC_KEY_I = 44,
		MC_KEY_J = 45,
		MC_KEY_K = 46,
		MC_KEY_L = 47,
		MC_KEY_M = 48,
		MC_KEY_N = 49,
		MC_KEY_O = 50,
		MC_KEY_P = 51,
		MC_KEY_Q = 52,
		MC_KEY_R = 53,
		MC_KEY_S = 54,
		MC_KEY_T = 55,
		MC_KEY_U = 56,
		MC_KEY_V = 57,
		MC_KEY_W = 58,
		MC_KEY_X = 59,
		MC_KEY_Y = 60,
		MC_KEY_Z = 61,

		MC_KEY_NUMPAD_0 = 62,
		MC_KEY_NUMPAD_1 = 63,
		MC_KEY_NUMPAD_2 = 64,
		MC_KEY_NUMPAD_3 = 65,
		MC_KEY_NUMPAD_4 = 66,
		MC_KEY_NUMPAD_5 = 67,
		MC_KEY_NUMPAD_6 = 68,
		MC_KEY_NUMPAD_7 = 69,
		MC_KEY_NUMPAD_8 = 70,
		MC_KEY_NUMPAD_9 = 71,

		MC_KEY_F1 = 72,
		MC_KEY_F2 = 73,
		MC_KEY_F3 = 74,
		MC_KEY_F4 = 75,
		MC_KEY_F5 = 76,
		MC_KEY_F6 = 77,
		MC_KEY_F7 = 78,
		MC_KEY_F8 = 79,
		MC_KEY_F9 = 80,
		MC_KEY_F10 = 81,
		MC_KEY_F11 = 82,
		MC_KEY_F12 = 83,

		MC_KEY_LSHIFT = 84,
		MC_KEY_RSHIFT = 85,
		MC_KEY_LCTRL = 86,
		MC_KEY_RCTRL = 87,
	};
}