#pragma once

#include "Event.h"
#include <sstream>

namespace MC
{
	class WindowResizeEvent : public Event
	{
	public:
		/**
		* @brief Constructor which takes two uint32_t.
		* @param width  - uint32_t to store the new width value after  resize.
		* @param height - uint32_t to store the new height value after resize.
		*/
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {};

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		/**
		* @brief Return a string with the resize event name and the new width and height.
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		/**
		* @brief Setup the WindowResize event type and category in order to have some "introspection".
		*/
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:

		/**
		* @brief Constructor
		*/
		WindowCloseEvent() {};

		/**
		* @brief Setup the WindowClose event type and category in order to have some "introspection".
		*/
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		/**
		* @brief Constructor.
		*/
		AppTickEvent() {};

		/**
		* @brief Setup the AppTick event type and category in order to have some "introspection".
		*/
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
		/**
		* @brief Constructor.
		*/
		AppUpdateEvent() {};

		/**
		* @brief Setup the AppUpdate event type and category in order to have some "introspection".
		*/
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		/**
		* @brief Constructor.
		*/
		AppRenderEvent() {};

		/**
		* @brief Setup the AppRender event type and category in order to have some "introspection".
		*/
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}

