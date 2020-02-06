#include "mcpch.h"
#include "WindowInput.h"
#include "MCP/Utils/Logger.h"
#include <windowsx.h>
#include "MCP/Application.h"


namespace MC
{
	Key* WindowInput::Keys = nullptr;
	vec2* WindowInput::MouseCoords = nullptr;
	EventCallbackFn WindowInput::EventCallback = nullptr;

   POINT WindowInput::currMousePos; 
   POINT WindowInput::lastMousePos; 
   POINT WindowInput::resetMousePos;
   POINT WindowInput::resultPos;

   vec2 WindowInput::MouseDelta;

	WindowInput::WindowInput(HWND windowHandler, float width, float height)
	{
		Keys = new Key[MAX_KEYS];
		MouseCoords = new vec2;

		Keys[0x01].KeyCode = MC_KEYS::MC_BUTTON_LBUTTON;
		Keys[0x02].KeyCode = MC_KEYS::MC_BUTTON_RBUTTON;
		Keys[0x04].KeyCode = MC_KEYS::MC_BUTTON_MBUTTON;
		Keys[0x05].KeyCode = MC_KEYS::MC_BUTTON_EXTRA1;
		Keys[0x06].KeyCode = MC_KEYS::MC_BUTTON_EXTRA2;
		Keys[0x08].KeyCode = MC_KEYS::MC_KEY_BACKSPACE;
		Keys[0x09].KeyCode = MC_KEYS::MC_KEY_TAB;
		Keys[0x0D].KeyCode = MC_KEYS::MC_KEY_ENTER;
		Keys[0x10].KeyCode = MC_KEYS::MC_KEY_SHIFT;
		Keys[0x11].KeyCode = MC_KEYS::MC_KEY_CTRL;
		Keys[0x12].KeyCode = MC_KEYS::MC_KEY_ALT;
		Keys[0x14].KeyCode = MC_KEYS::MC_KEY_CAPS;
		Keys[0x1B].KeyCode = MC_KEYS::MC_KEY_ESC;
		Keys[0x20].KeyCode = MC_KEYS::MC_KEY_SPACE;
		Keys[0x21].KeyCode = MC_KEYS::MC_KEY_PAGE_UP;
		Keys[0x22].KeyCode = MC_KEYS::MC_KEY_PAGE_DOWN;
		Keys[0x23].KeyCode = MC_KEYS::MC_KEY_END;
		Keys[0x24].KeyCode = MC_KEYS::MC_KEY_HOME;
		Keys[0x25].KeyCode = MC_KEYS::MC_KEY_LEFT;
		Keys[0x26].KeyCode = MC_KEYS::MC_KEY_UP;
		Keys[0x27].KeyCode = MC_KEYS::MC_KEY_RIGHT;
		Keys[0x28].KeyCode = MC_KEYS::MC_KEY_DOWN;
		Keys[0x29].KeyCode = MC_KEYS::MC_KEY_SELECT;
		Keys[0x2D].KeyCode = MC_KEYS::MC_KEY_INSERT;
		Keys[0x2E].KeyCode = MC_KEYS::MC_KEY_DELETE;
			
		Keys[0x30].KeyCode = MC_KEYS::MC_KEY_0;
		Keys[0x31].KeyCode = MC_KEYS::MC_KEY_1;
		Keys[0x32].KeyCode = MC_KEYS::MC_KEY_2;
		Keys[0x33].KeyCode = MC_KEYS::MC_KEY_3;
		Keys[0x34].KeyCode = MC_KEYS::MC_KEY_4;
		Keys[0x35].KeyCode = MC_KEYS::MC_KEY_5;
		Keys[0x36].KeyCode = MC_KEYS::MC_KEY_6;
		Keys[0x37].KeyCode = MC_KEYS::MC_KEY_7;
		Keys[0x38].KeyCode = MC_KEYS::MC_KEY_8;
		Keys[0x39].KeyCode = MC_KEYS::MC_KEY_9;
				
		Keys[0x41].KeyCode = MC_KEYS::MC_KEY_A;
		Keys[0x42].KeyCode = MC_KEYS::MC_KEY_B;
		Keys[0x43].KeyCode = MC_KEYS::MC_KEY_C;
		Keys[0x44].KeyCode = MC_KEYS::MC_KEY_D;
		Keys[0x45].KeyCode = MC_KEYS::MC_KEY_E;
		Keys[0x46].KeyCode = MC_KEYS::MC_KEY_F;
		Keys[0x47].KeyCode = MC_KEYS::MC_KEY_G;
		Keys[0x48].KeyCode = MC_KEYS::MC_KEY_H;
		Keys[0x49].KeyCode = MC_KEYS::MC_KEY_I;
		Keys[0x4A].KeyCode = MC_KEYS::MC_KEY_J;
		Keys[0x4B].KeyCode = MC_KEYS::MC_KEY_K;
		Keys[0x4C].KeyCode = MC_KEYS::MC_KEY_L;
		Keys[0x4D].KeyCode = MC_KEYS::MC_KEY_M;
		Keys[0x4E].KeyCode = MC_KEYS::MC_KEY_N;
		Keys[0x4F].KeyCode = MC_KEYS::MC_KEY_O;
		Keys[0x50].KeyCode = MC_KEYS::MC_KEY_P;
		Keys[0x51].KeyCode = MC_KEYS::MC_KEY_Q;
		Keys[0x52].KeyCode = MC_KEYS::MC_KEY_R;
		Keys[0x53].KeyCode = MC_KEYS::MC_KEY_S;
		Keys[0x54].KeyCode = MC_KEYS::MC_KEY_T;
		Keys[0x55].KeyCode = MC_KEYS::MC_KEY_U;
		Keys[0x56].KeyCode = MC_KEYS::MC_KEY_V;
		Keys[0x57].KeyCode = MC_KEYS::MC_KEY_W;
		Keys[0x58].KeyCode = MC_KEYS::MC_KEY_X;
		Keys[0x59].KeyCode = MC_KEYS::MC_KEY_Y;
		Keys[0x5A].KeyCode = MC_KEYS::MC_KEY_Z;
				
		Keys[0x60].KeyCode = MC_KEYS::MC_KEY_NUMPAD_0;
		Keys[0x61].KeyCode = MC_KEYS::MC_KEY_NUMPAD_1;
		Keys[0x62].KeyCode = MC_KEYS::MC_KEY_NUMPAD_2;
		Keys[0x63].KeyCode = MC_KEYS::MC_KEY_NUMPAD_3;
		Keys[0x64].KeyCode = MC_KEYS::MC_KEY_NUMPAD_4;
		Keys[0x65].KeyCode = MC_KEYS::MC_KEY_NUMPAD_5;
		Keys[0x66].KeyCode = MC_KEYS::MC_KEY_NUMPAD_6;
		Keys[0x67].KeyCode = MC_KEYS::MC_KEY_NUMPAD_7;
		Keys[0x68].KeyCode = MC_KEYS::MC_KEY_NUMPAD_8;
		Keys[0x69].KeyCode = MC_KEYS::MC_KEY_NUMPAD_9;
			
		Keys[0x70].KeyCode = MC_KEYS::MC_KEY_F1;
		Keys[0x71].KeyCode = MC_KEYS::MC_KEY_F2;
		Keys[0x72].KeyCode = MC_KEYS::MC_KEY_F3;
		Keys[0x73].KeyCode = MC_KEYS::MC_KEY_F4;
		Keys[0x74].KeyCode = MC_KEYS::MC_KEY_F5;
		Keys[0x75].KeyCode = MC_KEYS::MC_KEY_F6;
		Keys[0x76].KeyCode = MC_KEYS::MC_KEY_F7;
		Keys[0x77].KeyCode = MC_KEYS::MC_KEY_F8;
		Keys[0x78].KeyCode = MC_KEYS::MC_KEY_F9;
		Keys[0x79].KeyCode = MC_KEYS::MC_KEY_F10;
		Keys[0x7A].KeyCode = MC_KEYS::MC_KEY_F11;
		Keys[0x7B].KeyCode = MC_KEYS::MC_KEY_F12;
				
		Keys[0xA0].KeyCode = MC_KEYS::MC_KEY_LSHIFT;
		Keys[0xA1].KeyCode = MC_KEYS::MC_KEY_RSHIFT;
		Keys[0xA2].KeyCode = MC_KEYS::MC_KEY_LCTRL;
		Keys[0xA3].KeyCode = MC_KEYS::MC_KEY_RCTRL;



		resetMousePos.x = (width) / 2;
		resetMousePos.y = (height) / 2;

		currMousePos.x = resetMousePos.x;
		currMousePos.y = resetMousePos.y;
		lastMousePos = currMousePos;

		resultPos.x = 0;
		resultPos.y = 0;

		POINT temp = currMousePos;

		ClientToScreen(windowHandler, &temp);

		SetCursorPos(temp.x, temp.y);
	}

	WindowInput::~WindowInput()
	{
		delete[] Keys;
		delete MouseCoords;
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

				//Aqui gera o evento para o App
				MC::KeyPressedEvent event(Keys[wparam].KeyCode, (bool)Ki.nPrevious);
				EventCallback(event);

				//Aqui configura o state da tecla para qualquer momento que um usuário quiser saber o seu estado.
				Keys[wparam].isPressed = true;
				Keys[wparam].isRepeated = Ki.nPrevious;

				break;
			}

			case WM_KEYUP:	
			{
				MC::KeyReleasedEvent event(Keys[wparam].KeyCode);
				EventCallback(event);

				Keys[wparam].isPressed = false;
				Keys[wparam].isRepeated = false;

				break;
			}

			case WM_LBUTTONDOWN:
			{
				//Usar o wparam para saber se alguma tecla especial estava sendo acionada no click (shift, control etc)
				MC::MouseButtonPressedEvent event(MC_KEYS::MC_BUTTON_LBUTTON);
				EventCallback(event);

				Keys[wparam].isPressed = true;

				//@TODO: process drag

				break;
			}

			case WM_LBUTTONUP:
			{
				MC::MouseButtoinReleasedEvent event(MC_KEYS::MC_BUTTON_LBUTTON);
				EventCallback(event);

				Keys[wparam].isPressed = false;

				break;
			}

			case WM_RBUTTONDOWN:
			{
				MC::MouseButtonPressedEvent event(MC_KEYS::MC_BUTTON_RBUTTON);
				EventCallback(event);


				Keys[wparam].isPressed = true;

				break;
			}

			case WM_RBUTTONUP:
			{
				MC::MouseButtoinReleasedEvent event(MC_KEYS::MC_BUTTON_RBUTTON);
				EventCallback(event);


				Keys[wparam].isPressed = false;

				break;
			}


			case WM_MOUSEMOVE:
			{	
				//Create event
				MC::MouseMovedEvent event((lparam & 0xFFFF), ((lparam >> 16) & 0xFFFF)); //X em low order and Y em high order.

				MouseCoords->x = event.GetX();
				MouseCoords->y = event.GetY();

				EventCallback(event);





				//Mouse delta logic
				currMousePos.x = MouseCoords->x;
				currMousePos.y = MouseCoords->y;

				POINT difference;
				difference.x = currMousePos.x - lastMousePos.x;
				difference.y = currMousePos.y - lastMousePos.y;

				resultPos.x += difference.x;
				resultPos.y += difference.y;

				lastMousePos = currMousePos;

				MouseDelta = vec2((float)resultPos.x, (float)resultPos.y);
				

				//Reset mouse to the middle of screen
				POINT temp = resetMousePos;
				ClientToScreen(hwnd, &temp);

				// the new difference should be 0
				currMousePos.x = resetMousePos.x;
				currMousePos.y = resetMousePos.y;
				lastMousePos = currMousePos;

				SetCursorPos(temp.x, temp.y);
	

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


	void WindowInput::setMouseCoords(vec2 coords)
	{
		SetCursorPos(coords.x, coords.y);
	}
}