
#include "AnimationMetaPointsElement.hpp"

namespace flui
{
	AnimationMetaPointsElement::AnimationMetaPointsElement() : AnimationMetaPointsElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	AnimationMetaPointsElement::AnimationMetaPointsElement(const fgl::RectangleD& frame) : fgl::ScreenElement(frame),
		animationData(nullptr),
		frameIndex(0),
		orientation(fl::ANIMATIONORIENTATION_LEFT),
		mirrorHorizontally(false)
	{
		setBorderWidth(1);
	}
	
	void AnimationMetaPointsElement::setAnimationData(fl::AnimationData* animationData_arg)
	{
		animationData = animationData_arg;
	}
	
	fl::AnimationData* AnimationMetaPointsElement::getAnimationData() const
	{
		return animationData;
	}
	
	void AnimationMetaPointsElement::setAnimationFrame(size_t frameIndex_arg)
	{
		frameIndex = frameIndex_arg;
	}
	
	size_t AnimationMetaPointsElement::getAnimationFrame() const
	{
		return frameIndex;
	}
	
	void AnimationMetaPointsElement::setAnimationOrientation(fl::AnimationOrientation orientation_arg)
	{
		orientation = orientation_arg;
	}
	
	fl::AnimationOrientation AnimationMetaPointsElement::getAnimationOrientation() const
	{
		return orientation;
	}
	
	void AnimationMetaPointsElement::setHorizontalMirroringEnabled(bool toggle)
	{
		mirrorHorizontally = toggle;
	}
	
	bool AnimationMetaPointsElement::isHorizontalMirroringEnabled() const
	{
		return mirrorHorizontally;
	}
	
	void AnimationMetaPointsElement::drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		if(animationData!=nullptr)
		{
			fgl::RectangleD frame = getFrame();
			if(mirrorHorizontally)
			{
				frame.x = frame.x+frame.width;
				frame.width = -frame.width;
			}
			animationData->drawMetaPoints(frameIndex, frame, graphics, orientation);
		}
	}
}
