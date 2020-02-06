#pragma once

#include "MCP/Event/Event.h"
#include <string>
#include "MCP/Platform/DeltaTime.h"

namespace MC
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}; 
		virtual void OnDetach() {};
		virtual void OnUpdate(DeltaTime deltaTime) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string getName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}