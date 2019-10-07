#include "mcpch.h"
#include "WindowInput.h"
#include "Utils/Logger.h"
#include <windowsx.h>


namespace MC
{
	uint8_t* WindowInput::Keys = nullptr;
	EventCallbackFn WindowInput::EventCallback = nullptr;

	WindowInput::WindowInput()
	{
		Keys = new uint8_t[254];

		Keys[0x01] = MC_KEYS::MC_BUTTON_LBUTTON;
		Keys[0x02] = MC_KEYS::MC_BUTTON_RBUTTON;
		Keys[0x04] = MC_KEYS::MC_BUTTON_MBUTTON;
		Keys[0x05] = MC_KEYS::MC_BUTTON_EXTRA1;
		Keys[0x06] = MC_KEYS::MC_BUTTON_EXTRA2;
		Keys[0x08] = MC_KEYS::MC_KEY_BACKSPACE;
		Keys[0x09] = MC_KEYS::MC_KEY_TAB;
		Keys[0x0D] = MC_KEYS::MC_KEY_ENTER;
		Keys[0x10] = MC_KEYS::MC_KEY_SHIFT;
		Keys[0x11] = MC_KEYS::MC_KEY_CTRL;
		Keys[0x12] = MC_KEYS::MC_KEY_ALT;
		Keys[0x14] = MC_KEYS::MC_KEY_CAPS;
		Keys[0x1B] = MC_KEYS::MC_KEY_ESC;
		Keys[0x20] = MC_KEYS::MC_KEY_SPACE;
		Keys[0x21] = MC_KEYS::MC_KEY_PAGE_UP;
		Keys[0x22] = MC_KEYS::MC_KEY_PAGE_DOWN;
		Keys[0x23] = MC_KEYS::MC_KEY_END;
		Keys[0x24] = MC_KEYS::MC_KEY_HOME;
		Keys[0x25] = MC_KEYS::MC_KEY_LEFT;
		Keys[0x26] = MC_KEYS::MC_KEY_UP;
		Keys[0x27] = MC_KEYS::MC_KEY_RIGHT;
		Keys[0x28] = MC_KEYS::MC_KEY_DOWN;
		Keys[0x29] = MC_KEYS::MC_KEY_SELECT;
		Keys[0x2D] = MC_KEYS::MC_KEY_INSERT;
		Keys[0x2E] = MC_KEYS::MC_KEY_DELETE;


		Keys[0x30] = MC_KEYS::MC_KEY_0;
		Keys[0x31] = MC_KEYS::MC_KEY_1;
		Keys[0x32] = MC_KEYS::MC_KEY_2;
		Keys[0x33] = MC_KEYS::MC_KEY_3;
		Keys[0x34] = MC_KEYS::MC_KEY_4;
		Keys[0x35] = MC_KEYS::MC_KEY_5;
		Keys[0x36] = MC_KEYS::MC_KEY_6;
		Keys[0x37] = MC_KEYS::MC_KEY_7;
		Keys[0x38] = MC_KEYS::MC_KEY_8;
		Keys[0x39] = MC_KEYS::MC_KEY_9;

		Keys[0x41] = MC_KEYS::MC_KEY_A;
		Keys[0x42] = MC_KEYS::MC_KEY_B;
		Keys[0x43] = MC_KEYS::MC_KEY_C;
		Keys[0x44] = MC_KEYS::MC_KEY_D;
		Keys[0x45] = MC_KEYS::MC_KEY_E;
		Keys[0x46] = MC_KEYS::MC_KEY_F;
		Keys[0x47] = MC_KEYS::MC_KEY_G;
		Keys[0x48] = MC_KEYS::MC_KEY_H;
		Keys[0x49] = MC_KEYS::MC_KEY_I;
		Keys[0x4A] = MC_KEYS::MC_KEY_J;
		Keys[0x4B] = MC_KEYS::MC_KEY_K;
		Keys[0x4C] = MC_KEYS::MC_KEY_L;
		Keys[0x4D] = MC_KEYS::MC_KEY_M;
		Keys[0x4E] = MC_KEYS::MC_KEY_N;
		Keys[0x4F] = MC_KEYS::MC_KEY_O;
		Keys[0x50] = MC_KEYS::MC_KEY_P;
		Keys[0x51] = MC_KEYS::MC_KEY_Q;
		Keys[0x52] = MC_KEYS::MC_KEY_R;
		Keys[0x53] = MC_KEYS::MC_KEY_S;
		Keys[0x54] = MC_KEYS::MC_KEY_T;
		Keys[0x55] = MC_KEYS::MC_KEY_U;
		Keys[0x56] = MC_KEYS::MC_KEY_V;
		Keys[0x57] = MC_KEYS::MC_KEY_W;
		Keys[0x58] = MC_KEYS::MC_KEY_X;
		Keys[0x59] = MC_KEYS::MC_KEY_Y;
		Keys[0x5A] = MC_KEYS::MC_KEY_Z;

		Keys[0x60] = MC_KEYS::MC_KEY_NUMPAD_0;
		Keys[0x61] = MC_KEYS::MC_KEY_NUMPAD_1;
		Keys[0x62] = MC_KEYS::MC_KEY_NUMPAD_2;
		Keys[0x63] = MC_KEYS::MC_KEY_NUMPAD_3;
		Keys[0x64] = MC_KEYS::MC_KEY_NUMPAD_4;
		Keys[0x65] = MC_KEYS::MC_KEY_NUMPAD_5;
		Keys[0x66] = MC_KEYS::MC_KEY_NUMPAD_6;
		Keys[0x67] = MC_KEYS::MC_KEY_NUMPAD_7;
		Keys[0x68] = MC_KEYS::MC_KEY_NUMPAD_8;
		Keys[0x69] = MC_KEYS::MC_KEY_NUMPAD_9;

		Keys[0x70] = MC_KEYS::MC_KEY_F1;
		Keys[0x71] = MC_KEYS::MC_KEY_F2;
		Keys[0x72] = MC_KEYS::MC_KEY_F3;
		Keys[0x73] = MC_KEYS::MC_KEY_F4;
		Keys[0x74] = MC_KEYS::MC_KEY_F5;
		Keys[0x75] = MC_KEYS::MC_KEY_F6;
		Keys[0x76] = MC_KEYS::MC_KEY_F7;
		Keys[0x77] = MC_KEYS::MC_KEY_F8;
		Keys[0x78] = MC_KEYS::MC_KEY_F9;
		Keys[0x79] = MC_KEYS::MC_KEY_F10;
		Keys[0x7A] = MC_KEYS::MC_KEY_F11;
		Keys[0x7B] = MC_KEYS::MC_KEY_F12;

		Keys[0xA0] = MC_KEYS::MC_KEY_LSHIFT;
		Keys[0xA1] = MC_KEYS::MC_KEY_RSHIFT;
		Keys[0xA2] = MC_KEYS::MC_KEY_LCTRL;
		Keys[0xA3] = MC_KEYS::MC_KEY_RCTRL;
	}

	WindowInput::~WindowInput()
	{
		delete[] Keys;
	}

	//Deixei o processo de mensagem do Windows aqui pois a ideia de "Input" da Window seria para inputs gerais, tanto em GUI quanto de Hardware.
	LRESULT CALLBACK WindowInput::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			case WM_KEYDOWN:
			{
				KeyInfo Ki;
				Ki.lparam = lparam;

				MC::KeyPressedEvent event((MC_KEYS)Keys[wparam], Ki.nPrevious);
				EventCallback(event);

				break;
			}

			case WM_KEYUP:	
			{
				MC::KeyReleasedEvent event((MC_KEYS)Keys[wparam]);
				EventCallback(event);

				break;
			}

			case WM_LBUTTONDOWN:
			{
				//Usar o wparam para saber se alguma tecla especial estava sendo acionada no click (shift, control etc)
				MC::MouseButtonPressedEvent event(MC_KEYS::MC_BUTTON_LBUTTON);
				EventCallback(event);

				break;
			}

			case WM_LBUTTONUP:
			{
				MC::MouseButtoinReleasedEvent event(MC_KEYS::MC_BUTTON_LBUTTON);
				EventCallback(event);

				break;
			}

			case WM_RBUTTONDOWN:
			{
				MC::MouseButtonPressedEvent event(MC_KEYS::MC_BUTTON_RBUTTON);
				EventCallback(event);

				break;
			}

			case WM_RBUTTONUP:
			{
				MC::MouseButtoinReleasedEvent event(MC_KEYS::MC_BUTTON_RBUTTON);
				EventCallback(event);

				break;
			}


			case WM_MOUSEMOVE:
			{				
				MC::MouseMovedEvent event((lparam & 0xFFFF), ((lparam >> 16) & 0xFFFF)); //X in low order and Y in high order.
				EventCallback(event);

				break;
			}

			case WM_DESTROY:
			{
				MC::WindowCloseEvent event;
				EventCallback(event);
				PostQuitMessage(0);
			}


			default:
			{
				return DefWindowProc(hwnd, msg, wparam, lparam);
			}
		}

		return NULL;
	}


}