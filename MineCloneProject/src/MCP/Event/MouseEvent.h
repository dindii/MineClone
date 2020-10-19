#pragma once
#include "Event.h"
#include <sstream>

namespace MC
{
	class MouseMovedEvent : public Event
	{
	public:
		/**
		* @brief Constructor, takes two uint16_t so i can set m_Mousex and m_MouseY.
		* @param x - X coord of where the mouse is now.
		* @param y - Y coord of where the mouse is now.
		*/
		MouseMovedEvent(uint16_t x, uint16_t y) : m_MouseX(x), m_MouseY(y) {};

		inline uint16_t GetX() const { return m_MouseX; }
		inline uint16_t GetY() const { return m_MouseY; }

		/**
		* @brief Stringfy the event so i can be printed easily.
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		/**
		* @brief Define it's category for some degree of introspection.
		* E.g: We can ask some type of input from the user and check if the next event is an
		* EventCategoryInput or EventCategoryMouse, maybe both.
		*/
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		uint16_t m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		/**
		* @brief Constructor, takes two f32 so i can track the X and Y wheel offset. Also used to set m_XOffset and m_YOffset.
		* @param xOffset - How much was scrolled horizontally.
		* @param yOffset - How much was scrolled vertically.
		*/
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {};

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		/**
		* @brief Stringfy the event so it can be printed easily.
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		/**
		* @brief Define it's category for some degree of introspection.
		* E.g: We can ask some type of input from the user and check if the next event is an
		* EventCategoryInput or EventCategoryMouse, maybe both.
		*/
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		/**
		* @brief Returns the button of the triggered event. Usually called through a child class.
		*/
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		/**
		* @brief Constructor, takes an uint32_t for m_Button initialization. Always called through a child class.
		*/
		MouseButtonEvent(int mouseButton) : m_Button(mouseButton) {};
		int m_Button;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/**
		* @brief Constructor, takes an uint32_t for m_Button initialization.
		*/
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {};

		/**
		* @brief Stringfy the event so it can be logged easier
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		/**
		* @brief Constructor, takes an uint32_t for m_Button initialization.
		*/
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {};

		/**
		* @brief Stringfy the event so it can be logged easier
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}