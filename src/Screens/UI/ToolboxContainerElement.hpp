
#pragma once

#include "ToolboxElement.hpp"

namespace flui
{
	class ToolboxContainerElement : public fgl::ScreenElement
	{
	public:
		ToolboxContainerElement();
		ToolboxContainerElement(const fgl::RectangleD& frame);

		void setToolboxElement(ToolboxElement* toolboxElement);
		ToolboxElement* getToolboxElement() const;

	private:
		ToolboxElement* toolboxElement;

		fgl::ScreenElement* headerElement;
		fgl::TextElement* titleElement;
		fgl::ButtonElement* closeButtonElement;
	};
}
