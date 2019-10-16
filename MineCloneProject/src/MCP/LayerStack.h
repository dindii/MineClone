#pragma once

#include <vector>
#include "Layer.h"

namespace MC
{
	class LayerStack
	{
	public:
		LayerStack();
	   ~LayerStack();

	   void PushLayer(Layer* layer);
	   void PopLayer(Layer*  layer);

	   void PushOverLay(Layer* overlay);
	   void PopOverLay(Layer* overlay);

	   std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
	   std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex;
	};
}