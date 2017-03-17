
#include "MetaPointElement.hpp"

namespace flui
{
	MetaPointElement::MetaPointElement() : MetaPointElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	MetaPointElement::MetaPointElement(const fgl::RectangleD& frame) : TouchElement(frame),
		createdPoint(false),
		trackingPoint(true)
	{
		setTouchEnabled(false);
	}
	
	void MetaPointElement::drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		if(createdPoint && animationSize.x != 0 && animationSize.y != 0)
		{
			fgl::RectangleD frame = getFrame();
			graphics.translate(frame.x, frame.y);
			graphics.scale(frame.width/animationSize.x, frame.height/animationSize.y);
			metaPoint.draw(graphics);
		}
	}

	void MetaPointElement::setMetaPoint(const fl::AnimationMetaPoint& metaPoint_arg)
	{
		createdPoint = true;
		metaPoint = metaPoint_arg;
	}

	const fl::AnimationMetaPoint& MetaPointElement::getMetaPoint() const
	{
		return metaPoint;
	}
	
	void MetaPointElement::clearMetaPoint()
	{
		createdPoint = false;
		metaPoint = fl::AnimationMetaPoint();
	}

	void MetaPointElement::setAnimationSize(const fgl::Vector2d& animationSize_arg)
	{
		animationSize = animationSize_arg;
	}

	const fgl::Vector2d& MetaPointElement::getAnimationSize() const
	{
		return animationSize;
	}

	void MetaPointElement::setMetaPointChangeHandler(const std::function<void(fl::AnimationMetaPoint)>& handler)
	{
		metaPointChangeHandler = handler;
	}

	const std::function<void(fl::AnimationMetaPoint)>& MetaPointElement::getMetaPointChangeHandler() const
	{
		return metaPointChangeHandler;
	}
	
	fgl::Vector2d MetaPointElement::getMetaPointCenter() const
	{
		if(!createdPoint || animationSize.x==0 || animationSize.y==0)
		{
			return fgl::Vector2d(0,0);
		}
		else
		{
			fgl::RectangleD frame = getFrame();
			return fgl::Vector2d(metaPoint.x*(frame.width/animationSize.x), metaPoint.y*(frame.height/animationSize.y));
		}
	}
	
	fgl::Vector2d MetaPointElement::toMetaPointCoordinates(const fgl::Vector2d& point) const
	{
		if(animationSize.x==0 || animationSize.y==0)
		{
			return fgl::Vector2d(0,0);
		}
		else
		{
			fgl::RectangleD frame = getFrame();
			return fgl::Vector2d(point.x*(animationSize.x/frame.width), point.y*(animationSize.y/frame.height));
		}
	}
	
	bool MetaPointElement::isTouchPointOnCenter(const fgl::Vector2d& point) const
	{
		fgl::Vector2d metaPointCenter = getMetaPointCenter();
		double xoff = metaPointCenter.x-point.x;
		double yoff = metaPointCenter.y-point.y;
		if(fgl::Math::abs(xoff) <= 10 && fgl::Math::abs(yoff) <= 10)
		{
			return true;
		}
		return false;
	}
	
	void MetaPointElement::onTouchDown(const TouchEvent& touchEvent)
	{
		if(!createdPoint)
		{
			createdPoint = true;
			fgl::Vector2d metaPointCoordinates = toMetaPointCoordinates(touchEvent.getPosition());
			metaPoint.x = metaPointCoordinates.x;
			metaPoint.y = metaPointCoordinates.y;
			initialPointTouchOffset = fgl::Vector2d(0,0);
			trackingPoint = true;
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		}
		else if(isTouchPointOnCenter(touchEvent.getPosition()))
		{
			fgl::Vector2d metaPointCenter = getMetaPointCenter();
			initialPointTouchOffset = metaPointCenter-touchEvent.getPosition();
			trackingPoint = true;
		}
	}
	
	bool MetaPointElement::onTouchMove(const TouchEvent& touchEvent)
	{
		if(trackingPoint)
		{
			fgl::Vector2d metaPointCenter = toMetaPointCoordinates(touchEvent.getPosition()+initialPointTouchOffset);
			metaPoint.x = metaPointCenter.x;
			metaPoint.y = metaPointCenter.y;
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		}
		return true;
	}
	
	void MetaPointElement::onTouchUpInside(const TouchEvent& touchEvent)
	{
		trackingPoint = false;
	}
	
	void MetaPointElement::onTouchUpOutside(const TouchEvent& touchEvent)
	{
		trackingPoint = false;
	}
	
	void MetaPointElement::onTouchCancel(const TouchEvent& touchEvent)
	{
		trackingPoint = false;
	}
}
