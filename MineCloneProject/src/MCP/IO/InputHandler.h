#pragma once
#include "WindowInput.h"
#include "MCP/Maths/vec2.h"

namespace MC
{
	struct InputHandler
	{
		static bool isKeyPressed(const MC_KEYS& key);
		static bool isKeyHeld(const MC_KEYS& key);
		static vec2 GetMouseCoords();
		static vec2 GetMouseDelta();

		static void setMouseCoords(vec2 coords);
	};
}