#pragma once
#include <windows.h>


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

	class WindowInput
	{
	public:
		WindowInput();
		~WindowInput();

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	private:

		static uint8_t* Keys;
	};
}