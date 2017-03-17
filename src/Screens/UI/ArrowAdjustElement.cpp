
#include "ArrowAdjustElement.hpp"

namespace flui
{
	ArrowAdjustElement::ArrowAdjustElement(fgl::AssetManager* assetManager) : ArrowAdjustElement(assetManager, fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	ArrowAdjustElement::ArrowAdjustElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame) : ScreenElement(frame)
	{
		valueLabel = new fgl::TextInputElement();
		valueLabel->setEditable(false);
		valueLabel->setResigningOnOutsideTouchEnabled(true);
		valueLabel->setBorderWidth(0);
		valueLabel->getTextElement()->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		valueLabel->getTextElement()->setTextAlignment(fgl::TEXTALIGN_CENTER);
		valueLabel->getTextElement()->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		valueLabel->setFontSize(18);
		valueLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		valueLabel->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		valueLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		valueLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		
		assetManager->loadTexture("assets/images/arrow_button.png");
		
		prevValueButton = new fgl::ButtonElement();
		prevValueButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevValueButton->getImageElement()->setHorizontalImageMirroringEnabled(true);
		prevValueButton->setTapHandler([=]{
			if(hasPreviousValue())
			{
				previousValue();
				if(this->valueChangeHandler)
				{
					this->valueChangeHandler();
				}
			}
		});
		prevValueButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		prevValueButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		prevValueButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		prevValueButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 10);
		
		nextValueButton = new fgl::ButtonElement();
		nextValueButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextValueButton->setTapHandler([=]{
			if(hasNextValue())
			{
				nextValue();
				if(this->valueChangeHandler)
				{
					this->valueChangeHandler();
				}
			}
		});
		nextValueButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		nextValueButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		nextValueButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		nextValueButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 10);
		
		addChildElement(valueLabel);
		addChildElement(prevValueButton);
		addChildElement(nextValueButton);
	}
	
	ArrowAdjustElement::~ArrowAdjustElement()
	{
		delete valueLabel;
		delete prevValueButton;
		delete nextValueButton;
	}
	
	void ArrowAdjustElement::setValueChangeHandler(const std::function<void()>& valueChangeHandler_arg)
	{
		valueChangeHandler = valueChangeHandler_arg;
	}
	
	const std::function<void()>& ArrowAdjustElement::getValueChangeHandler() const
	{
		return valueChangeHandler;
	}
	
	fgl::TextInputElement* ArrowAdjustElement::getValueLabel() const
	{
		return valueLabel;
	}
	
	fgl::ButtonElement* ArrowAdjustElement::getPreviousValueButton() const
	{
		return prevValueButton;
	}
	
	fgl::ButtonElement* ArrowAdjustElement::getNextValueButton() const
	{
		return nextValueButton;
	}
	
	void ArrowAdjustElement::nextValue()
	{
		//somebody has to make the next value happen here
		updateValueLabelString();
	}
	
	void ArrowAdjustElement::previousValue()
	{
		//somebody has to make the previous value happen here
		updateValueLabelString();
	}
	
	void ArrowAdjustElement::updateValueLabelString()
	{
		valueLabel->setText(getValueString());
	}
}
