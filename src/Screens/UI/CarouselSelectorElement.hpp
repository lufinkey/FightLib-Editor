
#pragma once

#include "ArrowAdjustElement.hpp"

namespace flui
{
	class CarouselSelectorElement : public ArrowAdjustElement
	{
	public:
		static const size_t NO_SELECTION = -1;
		
		CarouselSelectorElement(fgl::AssetManager* assetManager, const fgl::ArrayList<fgl::Number>& optionList);
		CarouselSelectorElement(fgl::AssetManager* assetManager, const fgl::ArrayList<fgl::Number>& optionList, const fgl::RectangleD& frame);
		
		void setOptionList(const fgl::ArrayList<fgl::Number>& optionList);
		const fgl::ArrayList<fgl::Number>& getOptionList() const;
		
		void setSelectedOptionIndex(size_t optionIndex);
		size_t getSelectedOptionIndex() const;
		
		void setOptionTitleResolver(const std::function<fgl::String(fgl::Number)>& titleResolver);
		const std::function<fgl::String(fgl::Number)>& getOptionTitleResolver() const;
		
		fgl::String getOptionTitle(const fgl::Number& optionValue) const;
		
		virtual void nextValue() override;
		virtual void previousValue() override;
		
	protected:
		virtual fgl::String getValueString() const override;
		
		virtual bool hasNextValue() const override;
		virtual bool hasPreviousValue() const override;
		
	private:
		fgl::ArrayList<fgl::Number> optionList;
		size_t selectedOptionIndex;
		std::function<fgl::String(fgl::Number)> optionTitleResolver;
	};
}
