
#pragma once

#include <functional>
#include <GameLibrary/GameLibrary.hpp>

namespace flui
{
	class CarouselSelectorElement : public fgl::ScreenElement
	{
	public:
		static const size_t NO_SELECTION = -1;
		
		CarouselSelectorElement(fgl::AssetManager* assetManager, const fgl::ArrayList<fgl::Number>& optionList);
		CarouselSelectorElement(fgl::AssetManager* assetManager, const fgl::ArrayList<fgl::Number>& optionList, const fgl::RectangleD& frame);
		virtual ~CarouselSelectorElement();
		
		void setOptionList(const fgl::ArrayList<fgl::Number>& optionList);
		const fgl::ArrayList<fgl::Number>& getOptionList() const;
		
		void setSelectedOptionIndex(size_t optionIndex);
		size_t getSelectedOptionIndex() const;
		
		void setOptionTitleResolver(const std::function<fgl::String(fgl::Number)>& titleResolver);
		const std::function<fgl::String(fgl::Number)>& getOptionTitleResolver() const;
		
		fgl::String getOptionTitle(const fgl::Number& optionValue) const;
		
		void setHandler(const std::function<void()>& handler);
		const std::function<void()>& getHandler() const;
		
		void nextOption();
		void previousOption();
		
		fgl::TextElement* getOptionLabelElement() const;
		fgl::ButtonElement* getPreviousOptionButton() const;
		fgl::ButtonElement* getNextOptionButton() const;
		
	private:
		void reloadOptionLabelText();
		
		fgl::TextElement* optionLabel;
		fgl::ButtonElement* prevOptionButton;
		fgl::ButtonElement* nextOptionButton;
		
		fgl::ArrayList<fgl::Number> optionList;
		size_t selectedOptionIndex;
		std::function<fgl::String(fgl::Number)> optionTitleResolver;
		
		std::function<void()> handler;
	};
}
