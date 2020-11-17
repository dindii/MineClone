#pragma once

#include "MCP/Core.h"
#include <string>
#include <functional>

namespace MC
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	* @brief Each EventCategory is shifted by N, in this way we can have multiple categories for an event using | or cheking
	* if a event is in a certain category using &.
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
	    EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	/**
	* @brief Each subclass of Event will define/override its category and type, making possible some degree of introspection.
	*/
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }



	class Event
	{
	public:
		bool Handled = false;

		/**
		* @brief Each subclass of Event will define/override its category and type, making possible some degree of introspection.
		*/
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		/**
		* @brief Allow us to print the type of the event and the info that it brings e.g: (WindowResize 1360, 720).
		*/
		virtual std::string ToString() const { return GetName(); }

		/**
		* @brief Each subclass of Event will define/override its category and type, making possible some degree of introspection.
		* @param category - The event category to check if the event is part of. 
		*/
		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    };

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		os << e.ToString();
		return os;
	}

	class EventDispatcher
	{
		/**
		* @brief Just a function pointer that returns a bool and takes a T.
		* @param T - this have to be an Event, it will be used as argument for the function in the dispatcher.
		*/
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		/**
		* @brief Constructor that takes an Event.
		* @param Event that will be used to set m_Event.
		*/
		EventDispatcher(Event& event) : m_Event(event) {};

		/**
		* @brief This function takes an Event T as template argument and changes the argument's function pointer to take a T as argument.
		* After checking if the T event type is the same as the m_Event, it calls the function with the casted event argument.
		* The cast is made to a reference so we can assign a handled status to the event
		*
		* @param func - A function that returns bool and expects a certain type T of event.
		* Example: dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		* in this case, OnWindowClose expects a WindowCloseEvent argument and returns a bool, so it can fit in the Dispatch requisite
		*/
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};


}