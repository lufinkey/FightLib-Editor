
#pragma once

#include "ArrowAdjustElement.hpp"

namespace flui
{
	class NumberAdjustElement : public ArrowAdjustElement
	{
	public:
		NumberAdjustElement(fgl::AssetManager* assetManager);
		NumberAdjustElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame);
		
		void setValue(const fgl::Number& value);
		const fgl::Number& getValue() const;
		
		void setIncrement(const fgl::Number& increment);
		const fgl::Number& getIncrement() const;
		
		void setMinValue(const fgl::Number& minValue);
		const fgl::Number& getMinValue() const;
		
		void setMaxValue(const fgl::Number& maxValue);
		const fgl::Number& getMaxValue() const;
		
	protected:
		virtual fgl::String getValueString() const override;
		
		virtual bool hasNextValue() const override;
		virtual bool hasPreviousValue() const override;
		
		virtual void nextValue() override;
		virtual void previousValue() override;
		
	private:
		fgl::Number value;
		fgl::Number increment;
		fgl::Number minValue;
		fgl::Number maxValue;
	};
}
