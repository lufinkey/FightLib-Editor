
#include "NumberAdjustElement.hpp"

namespace flui
{
	NumberAdjustElement::NumberAdjustElement(fgl::AssetManager* assetManager) : NumberAdjustElement(assetManager, fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	NumberAdjustElement::NumberAdjustElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame) : ArrowAdjustElement(assetManager, frame),
		value(0),
		increment(1),
		minValue(0),
		maxValue(100)
	{
		//
	}
	
	void NumberAdjustElement::setValue(const fgl::Number& value_arg)
	{
		value = value_arg;
		updateValueLabelString();
	}
	
	const fgl::Number& NumberAdjustElement::getValue() const
	{
		return value;
	}
	
	void NumberAdjustElement::setIncrement(const fgl::Number& increment_arg)
	{
		increment = increment_arg;
	}
	
	const fgl::Number& NumberAdjustElement::getIncrement() const
	{
		return increment;
	}
	
	void NumberAdjustElement::setMinValue(const fgl::Number& minValue_arg)
	{
		minValue = minValue_arg;
	}
	
	const fgl::Number& NumberAdjustElement::getMinValue() const
	{
		return minValue;
	}
	
	void NumberAdjustElement::setMaxValue(const fgl::Number& maxValue_arg)
	{
		maxValue = maxValue_arg;
	}
	
	const fgl::Number& NumberAdjustElement::getMaxValue() const
	{
		return maxValue;
	}
	
	fgl::String NumberAdjustElement::getValueString() const
	{
		return value.toString();
	}
	
	bool NumberAdjustElement::hasNextValue() const
	{
		if((value+increment)>maxValue)
		{
			return false;
		}
		return true;
	}
	
	bool NumberAdjustElement::hasPreviousValue() const
	{
		if((value-increment)<minValue)
		{
			return false;
		}
		return true;
	}
	
	void NumberAdjustElement::nextValue()
	{
		value += increment;
		ArrowAdjustElement::nextValue();
	}
	
	void NumberAdjustElement::previousValue()
	{
		value -= increment;
		ArrowAdjustElement::previousValue();
	}
}
