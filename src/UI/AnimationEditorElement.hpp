
#pragma once

#include <fightlib/fightlib.hpp>
#include "CheckerboardElement.hpp"

namespace flui
{
	class AnimationEditorElement : public fgl::ScreenElement
	{
	public:
		AnimationEditorElement();
		AnimationEditorElement(const fgl::RectangleD& frame);
		virtual ~AnimationEditorElement();

		virtual void setFrame(const fgl::RectangleD& frame) override;

		void setAnimationData(fl::AnimationData* animationData);
		fl::AnimationData* getAnimationData() const;

	private:
		fl::AnimationData* animationData;

		fgl::AnimationElement* animationElement;
		fgl::AnimationElement* tracingAnimationElement;
		CheckerboardElement* checkerboardBackground;
	};
}
