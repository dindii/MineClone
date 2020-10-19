#pragma once
#include "Event.h"
#include <sstream>

namespace MC
{
	class KeyEvent : public Event 
	{
	public:
		/**
		* @brief Returns the MCP KeyCode affected by an event. Usually called through a child class as "KeyPressedEvent".
		*/
		inline int GetKeyCode() const { return m_KeyCode; }

		/**
		* @brief Define it's category for some degree of introspection.
		* e.g: We can ask some type of input from the user and check if the next event is an
		* EventCategoryInput or EventCategoryKeyboard, maybe both.
		*/
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		/**
		* @brief Protected constructor that takes a int.
		* @param Keycode - uint32_t Keycode used to set the stored (m_KeyCode) keycode in the event.
		*/
		KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {};
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		/**
		* @brief Constructor that takes an int for set the KeyEvent keycode and a bool to check if it is a repeating key
		* @param keycode - keycode of the pressed key.
		* @param repeated - bool to check if the key is being repeated multiple times.
		*/
		KeyPressedEvent(int keycode, bool repeated) : KeyEvent(keycode), m_Repeated(repeated) {};
		
		/**
		* @brief Returns if the pressed key is a repeated key
		*/
		inline bool GetRepeated() const { return m_Repeated; }

		/**
		* @brief Stringfy the event, allowing it to be printed easily
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << (m_Repeated ? "Repeated)" : "Not Repeated)");
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		bool m_Repeated;
	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:
		/**
		* @brief Constructor that takes an int to set the KeyEvent keycode.
		* @param keycode - keycode of the pressed key.
		*/
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) { };

		/**
		* @brief Stringfy the event, allowing it to be printed easily
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		/**
		* @brief Constructor that takes an int to set the KeyEvent keycode.
		* @param keycode - keycode of the typed key.
		*/
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {};

		/**
		* @brief Stringfy the event, allowing it to be printed easily
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}