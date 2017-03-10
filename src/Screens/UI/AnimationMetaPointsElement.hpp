
#pragma once

#include <fightlib/fightlib.hpp>

namespace flui
{
	class AnimationMetaPointsElement : public fgl::ScreenElement
	{
	public:
		AnimationMetaPointsElement();
		AnimationMetaPointsElement(const fgl::RectangleD& frame);
		
		void setAnimationData(fl::AnimationData* animationData);
		fl::AnimationData* getAnimationData() const;
		
		void setAnimationFrame(size_t frameIndex);
		size_t getAnimationFrame() const;
		
		void setAnimationOrientation(fl::AnimationOrientation orientation);
		fl::AnimationOrientation getAnimationOrientation() const;
		
	protected:
		virtual void drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
		
	private:
		fl::AnimationData* animationData;
		size_t frameIndex;
		fl::AnimationOrientation orientation;
	};
}
