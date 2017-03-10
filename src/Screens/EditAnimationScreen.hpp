
#pragma once

#include <fightlib/fightlib.hpp>
#include "UI/AnimationEditorElement.hpp"

namespace flui
{
	class EditAnimationScreen : public fgl::Screen
	{
	public:
		EditAnimationScreen(fl::AnimationData* animationData);

	private:
		fl::AnimationData* animationData;

		flui::AnimationEditorElement* animationEditorElement;
	};
}
