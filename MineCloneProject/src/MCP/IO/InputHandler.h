#pragma once
#include "WindowInput.h"


namespace MC
{
	struct InputHandler
	{
		static bool isKeyPressed(const MC_KEYS& key);
		static bool isKeyHeld(const MC_KEYS& key);
	};
}