
#include "CarouselSelectorElement.hpp"

namespace flui
{
	const size_t CarouselSelectorElement::NO_SELECTION;
	
	CarouselSelectorElement::CarouselSelectorElement(fgl::AssetManager* assetManager, const fgl::ArrayList<fgl::Number>& optionList)
		: CarouselSelectorElement(assetManager, optionList, fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	CarouselSelectorElement::CarouselSelectorElement(fgl::AssetManager* assetManager, const fgl::ArrayList<fgl::Number>& optionList, const fgl::RectangleD& frame)
		: ScreenElement(frame),
		optionList(optionList),
		selectedOptionIndex(NO_SELECTION),
		optionTitleResolver(nullptr)
	{
		optionLabel = new fgl::TextElement();
		optionLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		optionLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		optionLabel->setFontSize(18);
		optionLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		optionLabel->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		optionLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		optionLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		
		assetManager->loadTexture("assets/images/arrow_button.png");
		
		prevOptionButton = new fgl::ButtonElement();
		prevOptionButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevOptionButton->getImageElement()->setHorizontalImageMirroringEnabled(true);
		prevOptionButton->setTapHandler([=]{
			previousOption();
			if(this->optionChangeHandler)
			{
				this->optionChangeHandler();
			}
		});
		prevOptionButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		prevOptionButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		prevOptionButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		prevOptionButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 10);
		
		nextOptionButton = new fgl::ButtonElement();
		nextOptionButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextOptionButton->setTapHandler([=]{
			nextOption();
			if(this->optionChangeHandler)
			{
				this->optionChangeHandler();
			}
		});
		nextOptionButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		nextOptionButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		nextOptionButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		nextOptionButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 10);
		
		addChildElement(optionLabel);
		addChildElement(prevOptionButton);
		addChildElement(nextOptionButton);
	}
	
	CarouselSelectorElement::~CarouselSelectorElement()
	{
		delete optionLabel;
		delete prevOptionButton;
		delete nextOptionButton;
	}
	
	void CarouselSelectorElement::setOptionList(const fgl::ArrayList<fgl::Number>& optionList_arg)
	{
		optionList = optionList_arg;
		reloadOptionLabelText();
	}
	
	const fgl::ArrayList<fgl::Number>& CarouselSelectorElement::getOptionList() const
	{
		return optionList;
	}
	
	void CarouselSelectorElement::setSelectedOptionIndex(size_t optionIndex)
	{
		selectedOptionIndex = optionIndex;
		reloadOptionLabelText();
	}
	
	size_t CarouselSelectorElement::getSelectedOptionIndex() const
	{
		return selectedOptionIndex;
	}
	
	void CarouselSelectorElement::setOptionTitleResolver(const std::function<fgl::String(fgl::Number)>& titleResolver)
	{
		optionTitleResolver = titleResolver;
		reloadOptionLabelText();
	}
	
	const std::function<fgl::String(fgl::Number)>& CarouselSelectorElement::getOptionTitleResolver() const
	{
		return optionTitleResolver;
	}
	
	fgl::String CarouselSelectorElement::getOptionTitle(const fgl::Number& optionValue) const
	{
		if(optionTitleResolver)
		{
			return optionTitleResolver(optionValue);
		}
		return optionValue.toString();
	}
	
	void CarouselSelectorElement::setOptionChangeHandler(const std::function<void()>& optionChangeHandler_arg)
	{
		optionChangeHandler = optionChangeHandler_arg;
	}
	
	const std::function<void()>& CarouselSelectorElement::getOptionChangeHandler() const
	{
		return optionChangeHandler;
	}
	
	void CarouselSelectorElement::nextOption()
	{
		if(optionList.size()==0)
		{
			selectedOptionIndex = NO_SELECTION;
		}
		else
		{
			selectedOptionIndex++;
			if(selectedOptionIndex >= optionList.size())
			{
				selectedOptionIndex = 0;
			}
		}
		reloadOptionLabelText();
	}
	
	void CarouselSelectorElement::previousOption()
	{
		if(optionList.size()==0)
		{
			selectedOptionIndex = NO_SELECTION;
		}
		else
		{
			if(selectedOptionIndex==0)
			{
				selectedOptionIndex = optionList.size()-1;
			}
			else
			{
				selectedOptionIndex--;
			}
			if(selectedOptionIndex >= optionList.size())
			{
				selectedOptionIndex = optionList.size()-1;
			}
		}
		reloadOptionLabelText();
	}
	
	void CarouselSelectorElement::reloadOptionLabelText()
	{
		fgl::String optionText = "";
		if(selectedOptionIndex < optionList.size())
		{
			optionText = getOptionTitle(optionList[selectedOptionIndex]);
		}
		optionLabel->setText(optionText);
	}
	
	fgl::TextElement* CarouselSelectorElement::getOptionLabelElement() const
	{
		return optionLabel;
	}
	
	fgl::ButtonElement* CarouselSelectorElement::getPreviousOptionButton() const
	{
		return prevOptionButton;
	}
	
	fgl::ButtonElement* CarouselSelectorElement::getNextOptionButton() const
	{
		return nextOptionButton;
	}
}
