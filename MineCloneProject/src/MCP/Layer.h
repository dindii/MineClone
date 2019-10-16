#pragma once

#include "MCP/Event/Event.h"
#include <string>

namespace MC
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}; 
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string getName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}