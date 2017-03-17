
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace flui
{
	class LabeledCheckboxElement : public fgl::ScreenElement
	{
	public:
		LabeledCheckboxElement();
		LabeledCheckboxElement(const fgl::RectangleD& frame);
		virtual ~LabeledCheckboxElement();

		void setToggle(bool toggle);
		bool getToggle() const;

		void setText(const fgl::String& text);
		const fgl::String& getText() const;

		void setHandler(const std::function<void(bool)>& handler);
		const std::function<void(bool)>& getHandler() const;

		fgl::CheckboxElement* getCheckboxElement() const;
		fgl::TextElement* getLabelElement() const;

	private:
		fgl::CheckboxElement* checkboxElement;
		fgl::TextElement* labelElement;
	};
}
