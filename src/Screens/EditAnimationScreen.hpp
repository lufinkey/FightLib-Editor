
#pragma once

#include <fightlib/fightlib.hpp>
#include "UI/AnimationEditorElement.hpp"
#include "UI/MetapointInfoElement.hpp"
#include "UI/LabeledCheckboxElement.hpp"

namespace flui
{
	class EditAnimationScreen : public fgl::Screen
	{
	public:
		EditAnimationScreen(fgl::AssetManager* assetManager, fl::AnimationData* animationData);
		virtual ~EditAnimationScreen();
		
		virtual void update(fgl::ApplicationData appData) override;
		
		void nextFrame();
		void previousFrame();
		
	private:
		fgl::String getFrameIndexLabelString() const;
		void setLeftSidebarElement(fgl::ScreenElement* element);
		
		fl::AnimationData* animationData;

		fgl::TextInputElement* nameInputElement;
		flui::AnimationEditorElement* animationEditorElement;
		
		fgl::ScreenElement* leftSidebarContainer;
		fgl::ScreenElement* leftSidebarElement;
		fgl::ScreenElement* rightSidebarContainer;

		//right sidebar
		fgl::TextElement* frameIndexLabel;
		fgl::ButtonElement* nextFrameButton;
		fgl::ButtonElement* prevFrameButton;

		fgl::BasicDictionary<fl::AnimationMetaPoint::Type, LabeledCheckboxElement*> metapointCheckboxElements;
		
		//left sidebar
		MetapointInfoElement* metaPointInfoElement;
	};
}
