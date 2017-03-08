
#pragma once

#include <fightlib/fightlib.hpp>
#include "CheckerboardElement.hpp"

namespace flui
{
	class AnimationEditorElement : public fgl::TouchElement
	{
	public:
		AnimationEditorElement();
		AnimationEditorElement(const fgl::RectangleD& frame);
		virtual ~AnimationEditorElement();

		virtual void setFrame(const fgl::RectangleD& frame) override;

		void setAnimationData(fl::AnimationData* animationData);
		fl::AnimationData* getAnimationData() const;

		void setAnimationFrame(size_t frameIndex);
		size_t getAnimationFrame() const;

		void setTracingAnimationFrame(size_t frameIndex);
		size_t getTracingAnimationFrame() const;

		void setTracingAnimationVisible(bool visible);
		bool isTracingAnimationVisible() const;
		
		void setAnimationDirection(const fgl::Animation::Direction& direction);
		const fgl::Animation::Direction& getAnimationDirection() const;

	private:
		fl::AnimationData* animationData;

		fgl::AnimationElement* animationElement;
		fgl::AnimationElement* tracingAnimationElement;
		CheckerboardElement* checkerboardBackground;
	};
}
