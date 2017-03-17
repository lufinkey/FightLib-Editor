
#include "LabeledCheckboxElement.hpp"

namespace flui
{
	LabeledCheckboxElement::LabeledCheckboxElement() : LabeledCheckboxElement(fgl::RectangleD(0,0,100,40))
	{
		//
	}

	LabeledCheckboxElement::LabeledCheckboxElement(const fgl::RectangleD& frame) : ScreenElement(frame)
	{
		checkboxElement = new fgl::CheckboxElement();
		checkboxElement->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 10);
		checkboxElement->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, 0.5, fgl::LAYOUTVALUE_RATIO);

		labelElement = new fgl::TextElement();
		labelElement->setTextAlignment(fgl::TEXTALIGN_LEFT);
		labelElement->setVerticalAlignment(fgl::VERTICALALIGN_CENTER);
		labelElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 22);
		labelElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		labelElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		labelElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

		addChildElement(labelElement);
		addChildElement(checkboxElement);
	}

	LabeledCheckboxElement::~LabeledCheckboxElement()
	{
		delete checkboxElement;
		delete labelElement;
	}

	void LabeledCheckboxElement::setToggle(bool toggle)
	{
		checkboxElement->setToggle(toggle);
	}

	bool LabeledCheckboxElement::getToggle() const
	{
		return checkboxElement->getToggle();
	}

	void LabeledCheckboxElement::setText(const fgl::String& text)
	{
		labelElement->setText(text);
	}

	const fgl::String& LabeledCheckboxElement::getText() const
	{
		return labelElement->getText();
	}

	void LabeledCheckboxElement::setHandler(const std::function<void(bool)>& handler)
	{
		checkboxElement->setHandler(handler);
	}

	const std::function<void(bool)>& LabeledCheckboxElement::getHandler() const
	{
		return checkboxElement->getHandler();
	}

	fgl::CheckboxElement* LabeledCheckboxElement::getCheckboxElement() const
	{
		return checkboxElement;
	}

	fgl::TextElement* LabeledCheckboxElement::getLabelElement() const
	{
		return labelElement;
	}
}
