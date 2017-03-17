
#pragma once

#include <functional>
#include <GameLibrary/GameLibrary.hpp>

namespace flui
{
	class ArrowAdjustElement : public fgl::ScreenElement
	{
	public:
		ArrowAdjustElement(fgl::AssetManager* assetManager);
		ArrowAdjustElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame);
		virtual ~ArrowAdjustElement();
		
		void setValueChangeHandler(const std::function<void()>& valueChangeHandler);
		const std::function<void()>& getValueChangeHandler() const;
		
		fgl::TextInputElement* getValueLabel() const;
		fgl::ButtonElement* getPreviousValueButton() const;
		fgl::ButtonElement* getNextValueButton() const;
		
	protected:
		virtual fgl::String getValueString() const = 0;
		
		virtual bool hasNextValue() const = 0;
		virtual bool hasPreviousValue() const = 0;
		
		virtual void nextValue();
		virtual void previousValue();
		
		void updateValueLabelString();
		
	private:
		fgl::TextInputElement* valueLabel;
		fgl::ButtonElement* prevValueButton;
		fgl::ButtonElement* nextValueButton;
		
		std::function<void()> valueChangeHandler;
	};
}
