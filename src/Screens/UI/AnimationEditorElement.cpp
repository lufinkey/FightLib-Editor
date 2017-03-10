
#include "AnimationEditorElement.hpp"

namespace flui
{
	AnimationEditorElement::AnimationEditorElement() : AnimationEditorElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}

	AnimationEditorElement::AnimationEditorElement(const fgl::RectangleD& frame) : fgl::ScreenElement(frame),
		animationData(nullptr),
		checkerboardBackground(new CheckerboardElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		tracingAnimationElement(new fgl::AnimationElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		animationElement(new fgl::AnimationElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		metaPointsElement(new AnimationMetaPointsElement(fgl::RectangleD(0, 0, frame.width, frame.height)))
	{
		checkerboardBackground->setVisible(false);
		checkerboardBackground->setFirstBlockColor(fgl::Color(236,236,236));
		checkerboardBackground->setSecondBlockColor(fgl::Color(220,220,220));
		addChildElement(checkerboardBackground);

		tracingAnimationElement->getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
		tracingAnimationElement->setAnimationDirection(fgl::Animation::STOPPED);
		addChildElement(tracingAnimationElement);

		animationElement->getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
		animationElement->setAnimationDirection(fgl::Animation::STOPPED);
		addChildElement(animationElement);
		
		addChildElement(metaPointsElement);
	}

	AnimationEditorElement::~AnimationEditorElement()
	{
		delete metaPointsElement;
		delete animationElement;
		delete tracingAnimationElement;
		delete checkerboardBackground;
	}

	void AnimationEditorElement::layoutChildElements()
	{
		ScreenElement::layoutChildElements();
		fgl::RectangleD frame = getFrame();
		animationElement->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
		tracingAnimationElement->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
		if(animationData!=nullptr)
		{
			fgl::RectangleD displayFrame = animationElement->getImageElement()->getImageDisplayFrame();
			checkerboardBackground->setFrame(displayFrame);
			metaPointsElement->setFrame(displayFrame);
		}
		else
		{
			checkerboardBackground->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
			metaPointsElement->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
		}
	}
	
	void AnimationEditorElement::update(fgl::ApplicationData appData)
	{
		ScreenElement::update(appData);
		
		if(animationData!=nullptr && animationElement->getAnimationDirection()!=fgl::Animation::STOPPED)
		{
			metaPointsElement->setFrame(animationElement->getImageElement()->getImageDisplayFrame());
		}
	}

	void AnimationEditorElement::setAnimationData(fl::AnimationData* animationData_arg)
	{
		animationData = animationData_arg;
		if(animationData!=nullptr)
		{
			tracingAnimationElement->setAnimation(animationData->getAnimation(), fgl::Animation::NO_CHANGE);
			animationElement->setAnimation(animationData->getAnimation(), fgl::Animation::NO_CHANGE);
			checkerboardBackground->setVisible(true);
			checkerboardBackground->setFrame(animationElement->getImageElement()->getImageDrawFrame());
		}
		else
		{
			tracingAnimationElement->setAnimation(nullptr, fgl::Animation::NO_CHANGE);
			animationElement->setAnimation(nullptr, fgl::Animation::NO_CHANGE);
			checkerboardBackground->setVisible(false);
		}
		metaPointsElement->setAnimationData(animationData_arg);
		layoutChildElements();
	}

	fl::AnimationData* AnimationEditorElement::getAnimationData() const
	{
		return animationData;
	}

	void AnimationEditorElement::setAnimationFrame(size_t frameIndex)
	{
		animationElement->setAnimationFrame(frameIndex);
		metaPointsElement->setAnimationFrame(frameIndex);
		layoutChildElements();
	}

	size_t AnimationEditorElement::getAnimationFrame() const
	{
		return animationElement->getAnimationFrame();
	}

	void AnimationEditorElement::setTracingAnimationFrame(size_t frameIndex)
	{
		tracingAnimationElement->setAnimationFrame(frameIndex);
	}

	size_t AnimationEditorElement::getTracingAnimationFrame() const
	{
		return tracingAnimationElement->getAnimationFrame();
	}

	void AnimationEditorElement::setTracingAnimationVisible(bool visible)
	{
		tracingAnimationElement->setVisible(visible);
	}

	bool AnimationEditorElement::isTracingAnimationVisible() const
	{
		return tracingAnimationElement->isVisible();
	}
	
	void AnimationEditorElement::setAnimationDirection(const fgl::Animation::Direction& direction)
	{
		animationElement->setAnimationDirection(direction);
	}
	
	const fgl::Animation::Direction& AnimationEditorElement::getAnimationDirection() const
	{
		return animationElement->getAnimationDirection();
	}
}
