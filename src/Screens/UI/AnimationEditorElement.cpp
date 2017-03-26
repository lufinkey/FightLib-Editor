
#include "AnimationEditorElement.hpp"

namespace flui
{
	AnimationEditorElement::AnimationEditorElement() : AnimationEditorElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}

	AnimationEditorElement::AnimationEditorElement(const fgl::RectangleD& frame) : fgl::ScreenElement(frame),
		animationData(nullptr),
		drawnOrientation(fl::ANIMATIONORIENTATION_NEUTRAL),
		checkerboardBackground(new CheckerboardElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		tracingAnimationElement(new fgl::AnimationElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		animationElement(new fgl::AnimationElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		metaPointsElement(new MetaPointGroupElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		addingMetaPointElement(new MetaPointElement(fgl::RectangleD(0, 0, frame.width, frame.height))),
		addingMetaPoint(false)
	{
		checkerboardBackground->setVisible(false);
		checkerboardBackground->setFirstBlockColor(fgl::Color(236,236,236));
		checkerboardBackground->setSecondBlockColor(fgl::Color(220,220,220));
		addChildElement(checkerboardBackground);

		tracingAnimationElement->getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
		tracingAnimationElement->setAnimationDirection(fgl::Animation::STOPPED);
		tracingAnimationElement->setAlpha(0.4);
		tracingAnimationElement->setVisible(false);
		addChildElement(tracingAnimationElement);

		animationElement->getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
		animationElement->setAnimationDirection(fgl::Animation::STOPPED);
		addChildElement(animationElement);
		
		metaPointsElement->setMetaPointChangeHandler([=](size_t index) {
			auto& metaPoint = metaPointsElement->getMetaPoint(index);
			animationData->setMetaPoint(getAnimationFrameIndex(), index, metaPoint);
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(index);
			}
		});
		addChildElement(metaPointsElement);

		addingMetaPointElement->setVisible(false);
		addChildElement(addingMetaPointElement);
	}

	AnimationEditorElement::~AnimationEditorElement()
	{
		delete addingMetaPointElement;
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
			addingMetaPointElement->setFrame(displayFrame);
		}
		else
		{
			checkerboardBackground->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
			metaPointsElement->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
			addingMetaPointElement->setFrame(fgl::RectangleD(0, 0, frame.width, frame.height));
		}
	}
	
	void AnimationEditorElement::update(fgl::ApplicationData appData)
	{
		ScreenElement::update(appData);
		
		if(animationData!=nullptr)
		{
			if(animationElement->getAnimationDirection()!=fgl::Animation::STOPPED)
			{
				refresh();
			}
			animationElement->getImageElement()->setHorizontalImageMirroringEnabled(animationData->isMirrored(drawnOrientation));
			metaPointsElement->setHorizontalMirroringEnabled(animationData->isMirrored(drawnOrientation));
		}
	}

	void AnimationEditorElement::refresh()
	{
		layoutChildElements();
		updateMetaPoints();
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
		updateMetaPoints();
		layoutChildElements();
	}

	fl::AnimationData* AnimationEditorElement::getAnimationData() const
	{
		return animationData;
	}

	void AnimationEditorElement::setAnimationFrameIndex(size_t frameIndex)
	{
		animationElement->setAnimationFrameIndex(frameIndex);
		updateMetaPoints();
		layoutChildElements();
	}

	size_t AnimationEditorElement::getAnimationFrameIndex() const
	{
		return animationElement->getAnimationFrameIndex();
	}

	void AnimationEditorElement::setTracingAnimationFrameIndex(size_t frameIndex)
	{
		tracingAnimationElement->setAnimationFrameIndex(frameIndex);
	}

	size_t AnimationEditorElement::getTracingAnimationFrameIndex() const
	{
		return tracingAnimationElement->getAnimationFrameIndex();
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
	
	void AnimationEditorElement::setDrawnOrientation(fl::AnimationOrientation orientation)
	{
		drawnOrientation = orientation;
		if(animationData!=nullptr)
		{
			animationElement->getImageElement()->setHorizontalImageMirroringEnabled(animationData->isMirrored(drawnOrientation));
			metaPointsElement->setHorizontalMirroringEnabled(animationData->isMirrored(drawnOrientation));
		}
	}
	
	fl::AnimationOrientation AnimationEditorElement::getDrawnOrientation() const
	{
		return drawnOrientation;
	}

	void AnimationEditorElement::setBoundsDrawingEnabled(bool enabled)
	{
		metaPointsElement->setBoundsDrawingEnabled(enabled);
	}

	bool AnimationEditorElement::isBoundsDrawingEnabled() const
	{
		return metaPointsElement->isBoundsDrawingEnabled();
	}
	
	void AnimationEditorElement::setMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType, bool visible)
	{
		metaPointsElement->setMetaPointTypeVisible(metaPointType, visible);
	}
	
	bool AnimationEditorElement::isMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType) const
	{
		return metaPointsElement->isMetaPointTypeVisible(metaPointType);
	}

	void AnimationEditorElement::setMetaPointSelectHandler(const std::function<void(size_t)>& handler)
	{
		metaPointsElement->setMetaPointSelectHandler(handler);
	}

	const std::function<void(size_t)>& AnimationEditorElement::getMetaPointSelectHandler() const
	{
		return metaPointsElement->getMetaPointSelectHandler();
	}

	void AnimationEditorElement::setMetaPointChangeHandler(const std::function<void(size_t)>& handler)
	{
		metaPointChangeHandler = handler;
	}

	const std::function<void(size_t)>& AnimationEditorElement::getMetaPointChangeHandler() const
	{
		return metaPointChangeHandler;
	}

	void AnimationEditorElement::setMetaPoints(size_t frameIndex, const fgl::ArrayList<fl::AnimationMetaPoint>& metaPoints)
	{
		animationData->setMetaPoints(frameIndex, metaPoints);
		if(frameIndex==getAnimationFrameIndex())
		{
			updateMetaPoints();
		}
	}

	fgl::ArrayList<fl::AnimationMetaPoint> AnimationEditorElement::getMetaPoints(size_t frameIndex) const
	{
		return animationData->getMetaPoints(frameIndex);
	}

	void AnimationEditorElement::setMetaPoint(size_t frameIndex, size_t metaPointIndex, const fl::AnimationMetaPoint& metaPoint)
	{
		animationData->setMetaPoint(frameIndex, metaPointIndex, metaPoint);
		if(frameIndex==getAnimationFrameIndex())
		{
			metaPointsElement->setMetaPoint(metaPointIndex, metaPoint);
		}
	}

	const fl::AnimationMetaPoint& AnimationEditorElement::getMetaPoint(size_t frameIndex, size_t metaPointIndex) const
	{
		return animationData->getMetaPoint(frameIndex, metaPointIndex);
	}

	void AnimationEditorElement::removeMetaPoint(size_t frameIndex, size_t metaPointIndex)
	{
		animationData->removeMetaPoint(frameIndex, metaPointIndex);
		if(frameIndex==getAnimationFrameIndex())
		{
			updateMetaPoints();
		}
	}

	void AnimationEditorElement::beginUserAddMetaPoint(const std::function<void(fl::AnimationMetaPoint)>& completion)
	{
		if(addingMetaPoint)
		{
			throw fgl::IllegalStateException("already adding meta point");
		}
		addingMetaPoint = true;
		addingMetaPointCompletionHandler = completion;
		addingMetaPointElement->setVisible(true);
		addingMetaPointElement->setDeselectHandler([=]{
			if(addingMetaPoint)
			{
				size_t frameIndex = getAnimationFrameIndex();
				fl::AnimationMetaPoint metaPoint = addingMetaPointElement->getMetaPoint();
				size_t metaPointIndex = animationData->addMetaPoint(frameIndex, metaPoint);
				addingMetaPointElement->clearMetaPoint();
				addingMetaPointElement->setVisible(false);
				updateMetaPoints();
				auto completion = addingMetaPointCompletionHandler;
				addingMetaPointCompletionHandler = nullptr;
				addingMetaPoint = false;
				auto& selectHandler = metaPointsElement->getMetaPointSelectHandler();
				if(selectHandler)
				{
					selectHandler(metaPointIndex);
				}
				if(completion)
				{
					completion(metaPoint);
				}
			}
		});
	}

	void AnimationEditorElement::updateMetaPoints()
	{
		if(animationData==nullptr || animationData->getAnimation()==nullptr || animationData->getAnimation()->getTotalFrames()==0)
		{
			metaPointsElement->setMetaPoints({});
			metaPointsElement->setAnimationSize(fgl::Vector2u(0, 0));
			addingMetaPointElement->setAnimationSize(fgl::Vector2u(0, 0));
		}
		else
		{
			metaPointsElement->setMetaPoints(animationData->getMetaPoints(animationElement->getAnimationFrameIndex()));
			metaPointsElement->setAnimationSize(animationData->getSize(animationElement->getAnimationFrameIndex()));
			addingMetaPointElement->setAnimationSize(animationData->getSize(animationElement->getAnimationFrameIndex()));
		}
	}
}
