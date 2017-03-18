
#include "ToolboxContainerElement.hpp"

namespace flui
{
#define HEADER_SIZE 44

	ToolboxContainerElement::ToolboxContainerElement() : ToolboxContainerElement(fgl::RectangleD(0, 0, 0, 0))
	{
		//
	}

	ToolboxContainerElement::ToolboxContainerElement(const fgl::RectangleD& frame) : ScreenElement(frame),
		toolboxElement(nullptr)
	{
		headerElement = new fgl::ScreenElement();
		headerElement->setVisible(false);
		headerElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		headerElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		headerElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		headerElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, HEADER_SIZE);

		closeButtonElement = new fgl::ButtonElement();
		closeButtonElement->setTitle("X", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		closeButtonElement->getTitleElement()->setFontSize(16);
		closeButtonElement->setTapHandler([=]{
			if(this->toolboxElement)
			{
				this->toolboxElement->onClose();
			}
			setToolboxElement(nullptr);
		});
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, HEADER_SIZE*0.4);

		titleElement = new fgl::TextElement();
		titleElement->setTextAlignment(fgl::TEXTALIGN_CENTER);
		titleElement->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		titleElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, HEADER_SIZE*0.4);
		titleElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, HEADER_SIZE*0.4);
		titleElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		titleElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

		headerElement->addChildElement(closeButtonElement);
		headerElement->addChildElement(titleElement);
		addChildElement(headerElement);
	}

	void ToolboxContainerElement::setToolboxElement(ToolboxElement* toolboxElement_arg)
	{
		if(toolboxElement!=nullptr)
		{
			toolboxElement->removeFromParentElement();
			toolboxElement->removeAllLayoutRules();
		}
		toolboxElement = toolboxElement_arg;
		if(toolboxElement!=nullptr)
		{
			titleElement->setText(toolboxElement->getTitle());
			toolboxElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			toolboxElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			toolboxElement->setLayoutRule(fgl::LAYOUTRULE_TOP, HEADER_SIZE);
			toolboxElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
			addChildElement(0, toolboxElement);
			headerElement->setVisible(true);
		}
		else
		{
			titleElement->setText("");
			headerElement->setVisible(false);
		}
	}

	ToolboxElement* ToolboxContainerElement::getToolboxElement() const
	{
		return toolboxElement;
	}
}
