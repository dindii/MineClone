#pragma once
#include <windows.h>
#include "MCP/Event/Event.h"
#include "MCP/Event/KeyEvent.h"
#include "MCP/Event/MouseEvent.h"
#include "MCP/Event/ApplicationEvent.h"
#include "MCP/Maths/vec2.h"
#include <functional>

namespace MC
{

	/**
	*  This is where i handle Windows window input. It's quite simple since i don't expect to have multiple windows/windows inputs and i didn't worry much
	*  about hidding some stuff from the user but this class is for internal purposes only, the input interface which the user can retrieve states and info 
	*  is the WindowInput class.
	*/ 

#define MAX_KEYS 255

	/**
	* Initializing our own keycodes. This is not better or worse than win32api native keycodes but i decided to make my own keycodes just for test purposes. 
	*/
	enum MC_KEYS : unsigned char
	{
		MC_NO_KEY = 0,
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


	/**
	* @brief This struct was made so we can read Windows params more easily, instead of bit shiftting every member, we can just create this struct
	* using lparam and it will automatically break every member by its number of bits ( : N )
	*/
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


	/**
	* @brief This struct will be serve as an array of Keys with its own states, the user through InputHandler can easily query for a key and check its state
	*/
	struct Key
	{
		/**
		* @brief Default contructor 
		*/
		Key() : KeyCode(MC_KEYS::MC_NO_KEY), isPressed(false), isRepeated(false) {};

		MC_KEYS KeyCode;
		bool isPressed;
		bool isRepeated;
	};
	

	using EventCallbackFn = std::function<void(Event&)>;

	//Users should use InputHandler, so i will naively hide this into internal namespace.
	namespace MC_INTERNAL
	{
		class WindowInput
		{
		public:
			WindowInput(HWND windowHandler, float width, float height); //@TODO: Realmente deixar esse construtor aqui? .. Ver uma forma melhor de conseguir width e height
			~WindowInput();

			static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
			static void setMouseCoords(vec2 coords);
			static void showCursor(bool showCursor);
			inline static Key* getKeys() { return Keys; }
			inline static vec2* getMouseCoords() { return MouseCoords; }
			inline static vec2 getMouseDelta() { return MouseDelta; }
			inline static void setMouseDelta(vec2 delta) { MouseDelta = delta; }
			inline static void lockDelta(bool lock) { deltaLock = lock; }
			inline static void lockCursor(bool lock) { cursorLock = lock; }

		public:
			inline void setEventCallback(const EventCallbackFn& callback) { EventCallback = callback; }


		private:
			static vec2* MouseCoords;
			static vec2 MouseDelta;
			static bool deltaLock, cursorLock;
			static Key* Keys;
			static EventCallbackFn EventCallback;
		private:
			static POINT currMousePos, lastMousePos, resetMousePos, resultPos;
		};


		struct Time
		{

			struct TimeProps
			{
				int Seconds = 0;
				float Miliseconds = 0;
			};

			static TimeProps getTime();
		};

	}
}