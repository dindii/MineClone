#include "mcpch.h"
#include "WindowInput.h"
#include "Utils/Logger.h"
#include "MCP/Event/Event.h"
#include "MCP/Event/KeyEvent.h"
#include "MCP/Event/MouseEvent.h"


namespace MC
{
	uint8_t* WindowInput::Keys = nullptr;
	EventCallbackFn WindowInput::EventCallback = nullptr;

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
				//MC_LOG_TRACE("Something happened!");
				KeyInfo Ki;
				Ki.lparam = lparam;

				//@TODO: Gerar eventos, bindar um OnEvent para o Window e do Window para o Application.
				//debug info
				//std::cout << "Key: " << (MC_KEYS)Keys[wparam] << " Repeated: " << (uint16_t)Ki.nPrevious << Ki.nRepeatCount << std::endl;

				//@TODO: Fazer uma preparação aqui, verificar o repeat e gerar um evento repeat ou um evento single, um evento key up etc
				MC::KeyPressedEvent event((MC_KEYS)Keys[wparam], Ki.nRepeatCount);
				EventCallback(event);

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