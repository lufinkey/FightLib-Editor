
#pragma once

#include <fightlib/fightlib.hpp>
#include "AnimationMetaPointsElement.hpp"
#include "CheckerboardElement.hpp"

namespace flui
{
	class AnimationEditorElement : public fgl::ScreenElement
	{
	public:
		AnimationEditorElement();
		AnimationEditorElement(const fgl::RectangleD& frame);
		virtual ~AnimationEditorElement();

		virtual void layoutChildElements() override;
		virtual void update(fgl::ApplicationData appData) override;

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

		CheckerboardElement* checkerboardBackground;
		fgl::AnimationElement* tracingAnimationElement;
		fgl::AnimationElement* animationElement;
		AnimationMetaPointsElement* metaPointsElement;
	};
}
