#pragma once
#include "mcpch.h"
#include "InputHandler.h"

namespace MC
{
	bool InputHandler::isKeyPressed(const MC_KEYS& key)
	{
		Key* aux = WindowInput::getKeys();

		for (uint8_t x = 0; x< MAX_KEYS-1; x++ )
		{
			if (aux[x].KeyCode != MC_KEYS::MC_NO_KEY)
				if(aux[x].KeyCode == key)
					return aux[x].isPressed;
		}

		return false;
	}

	bool InputHandler::isKeyHeld(const MC_KEYS& key)
	{
		Key* aux = WindowInput::getKeys();

		for (uint8_t x = 0; x < MAX_KEYS-1; x++)
		{
			if (aux[x].KeyCode != MC_KEYS::MC_NO_KEY)
				if (aux[x].KeyCode == key)
					return aux[x].isRepeated;
		}

		return false;
	}
}