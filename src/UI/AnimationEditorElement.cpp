
#include "AnimationEditorElement.hpp"

namespace flui
{
	AnimationEditorElement::AnimationEditorElement() : AnimationEditorElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}

	AnimationEditorElement::AnimationEditorElement(const fgl::RectangleD& frame) : fgl::ScreenElement(frame),
		animationData(nullptr),
		animationElement(new fgl::AnimationElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		tracingAnimationElement(new fgl::AnimationElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		checkerboardBackground(new CheckerboardElement(fgl::RectangleD(0, 0, frame.width, frame.height)))
	{
		checkerboardBackground->setVisible(false);
		checkerboardBackground->setFirstBlockColor(fgl::Color(236,236,236));
		checkerboardBackground->setSecondBlockColor(fgl::Color(220,220,220));
		addChildElement(checkerboardBackground);

		tracingAnimationElement->getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
		tracingAnimationElement->setVisible(false);
		addChildElement(tracingAnimationElement);

		animationElement->getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
		animationElement->setVisible(false);
		addChildElement(animationElement);
	}

	AnimationEditorElement::~AnimationEditorElement()
	{
		delete animationElement;
		delete tracingAnimationElement;
		delete checkerboardBackground;
	}

	void AnimationEditorElement::setFrame(const fgl::RectangleD& frame)
	{
		ScreenElement::setFrame(frame);
	}

	void AnimationEditorElement::setAnimationData(fl::AnimationData* animationData_arg)
	{
		animationData = animationData_arg;
		if(animationData!=nullptr)
		{
			tracingAnimationElement->setAnimation(animationData->getAnimation(), fgl::Animation::STOPPED);
			animationElement->setAnimation(animationData->getAnimation(), fgl::Animation::STOPPED);
			checkerboardBackground->setVisible(true);
			checkerboardBackground->setFrame(animationElement->getImageElement()->getImageDrawFrame());
			tracingAnimationElement->setVisible(false);
			animationElement->setVisible(true);
		}
		else
		{
			tracingAnimationElement->setAnimation(nullptr, fgl::Animation::STOPPED);
			animationElement->setAnimation(nullptr, fgl::Animation::STOPPED);
			checkerboardBackground->setVisible(false);
			tracingAnimationElement->setVisible(false);
			animationElement->setVisible(false);
		}
	}

	fl::AnimationData* AnimationEditorElement::getAnimationData() const
	{
		return animationData;
	}
}
