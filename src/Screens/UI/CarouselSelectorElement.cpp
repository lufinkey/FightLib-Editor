
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
		: ArrowAdjustElement(assetManager, frame),
		optionList(optionList),
		selectedOptionIndex(NO_SELECTION),
		optionTitleResolver(nullptr)
	{
		//
	}
	
	void CarouselSelectorElement::setOptionList(const fgl::ArrayList<fgl::Number>& optionList_arg)
	{
		optionList = optionList_arg;
		updateValueLabelString();
	}
	
	const fgl::ArrayList<fgl::Number>& CarouselSelectorElement::getOptionList() const
	{
		return optionList;
	}
	
	void CarouselSelectorElement::setSelectedOptionIndex(size_t optionIndex)
	{
		selectedOptionIndex = optionIndex;
		updateValueLabelString();
	}
	
	size_t CarouselSelectorElement::getSelectedOptionIndex() const
	{
		return selectedOptionIndex;
	}
	
	void CarouselSelectorElement::setOptionTitleResolver(const std::function<fgl::String(fgl::Number)>& titleResolver)
	{
		optionTitleResolver = titleResolver;
		updateValueLabelString();
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
	
	bool CarouselSelectorElement::hasNextValue() const
	{
		if(optionList.size()==0)
		{
			return false;
		}
		return true;
	}
	
	void CarouselSelectorElement::nextValue()
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
		ArrowAdjustElement::nextValue();
	}
	
	bool CarouselSelectorElement::hasPreviousValue() const
	{
		if(optionList.size()==0)
		{
			return false;
		}
		return true;
	}
	
	void CarouselSelectorElement::previousValue()
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
		ArrowAdjustElement::previousValue();
	}
	
	fgl::String CarouselSelectorElement::getValueString() const
	{
		fgl::String optionText = "";
		if(selectedOptionIndex < optionList.size())
		{
			optionText = getOptionTitle(optionList[selectedOptionIndex]);
		}
		return optionText;
	}
}
