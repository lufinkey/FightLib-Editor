
#pragma once

#include <fightlib/fightlib.hpp>
#include "UI/AnimationEditorElement.hpp"

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
		
		fl::AnimationData* animationData;

		fgl::TextInputElement* nameInputElement;
		flui::AnimationEditorElement* animationEditorElement;
		
		fgl::TextElement* frameIndexLabel;
		fgl::ButtonElement* nextFrameButton;
		fgl::ButtonElement* prevFrameButton;
	};
}
