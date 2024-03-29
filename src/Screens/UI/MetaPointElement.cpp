
#include "MetaPointElement.hpp"

namespace flui
{
	MetaPointElement::MetaPointElement() : MetaPointElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	MetaPointElement::MetaPointElement(const fgl::RectangleD& frame) : TouchElement(frame),
		anchorSize(1.0),
		createdPoint(false),
		trackingPoint(false)
	{
		//
	}

	bool MetaPointElement::isPointInside(const fgl::Vector2d& point) const
	{
		if(!createdPoint)
		{
			return TouchElement::isPointInside(point);
		}
		else
		{
			fgl::Vector2d metaPointCenter = getMetaPointCenter();
			double xoff = metaPointCenter.x-point.x;
			double yoff = metaPointCenter.y-point.y;
			auto frame = getFrame();
			double xMult = (frame.width/(double)animationSize.x);
			double yMult = (frame.height/(double)animationSize.y);
			if(fgl::Math::abs(xoff) <= (anchorSize*xMult/2) && fgl::Math::abs(yoff) <= (anchorSize*yMult/2))
			{
				return true;
			}
			return false;
		}
	}
	
	void MetaPointElement::drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		TouchElement::drawMain(appData, graphics);
		if(createdPoint && animationSize.x != 0 && animationSize.y != 0)
		{
			fgl::RectangleD frame = getFrame();
			graphics.translate(frame.x, frame.y);
			graphics.scale(frame.width/(double)animationSize.x, frame.height/(double)animationSize.y);
			metaPoint.draw(graphics, anchorSize);
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

	void MetaPointElement::setAnimationSize(const fgl::Vector2u& animationSize_arg)
	{
		animationSize = animationSize_arg;
	}

	const fgl::Vector2u& MetaPointElement::getAnimationSize() const
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

	void MetaPointElement::setSelectHandler(const std::function<void()>& handler)
	{
		selectHandler = handler;
	}

	const std::function<void()>& MetaPointElement::getSelectHandler() const
	{
		return selectHandler;
	}

	void MetaPointElement::setDeselectHandler(const std::function<void()>& handler)
	{
		deselectHandler = handler;
	}

	const std::function<void()>& MetaPointElement::getDeselectHandler() const
	{
		return deselectHandler;
	}

	void MetaPointElement::setAnchorSize(double anchorSize_arg)
	{
		anchorSize = anchorSize_arg;
	}

	double MetaPointElement::getAnchorSize() const
	{
		return anchorSize;
	}
	
	fgl::Vector2d MetaPointElement::getMetaPointCenter() const
	{
		if(!createdPoint || animationSize.x==0 || animationSize.y==0)
		{
			return fgl::Vector2d(0,0);
		}
		else
		{
			return fromMetaPointCoordinates(fgl::Vector2d(metaPoint.x, metaPoint.y));
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
			return fgl::Vector2d(point.x*((double)animationSize.x/frame.width), point.y*((double)animationSize.y/frame.height));
		}
	}

	fgl::Vector2d MetaPointElement::fromMetaPointCoordinates(const fgl::Vector2d& point) const
	{
		if(animationSize.x==0 || animationSize.y==0)
		{
			return fgl::Vector2d(0, 0);
		}
		else
		{
			fgl::RectangleD frame = getFrame();
			return fgl::Vector2d(point.x*(frame.width/(double)animationSize.x), point.y*(frame.height/(double)animationSize.y));
		}
	}
	
	void MetaPointElement::onTouchDown(const TouchEvent& touchEvent)
	{
		if(!createdPoint)
		{
			createdPoint = true;
			fgl::Vector2d metaPointCoordinates = toMetaPointCoordinates(touchEvent.getPosition());
			metaPoint.x = fgl::Math::roundToMultiple(metaPointCoordinates.x, 0.5);
			metaPoint.y = fgl::Math::roundToMultiple(metaPointCoordinates.y, 0.5);
			initialPointTouchOffset = fgl::Vector2d(0,0);
			trackingPoint = true;
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		}
		else
		{
			fgl::Vector2d metaPointCenter = getMetaPointCenter();
			initialPointTouchOffset = metaPointCenter-touchEvent.getPosition();
			trackingPoint = true;
		}
		if(selectHandler)
		{
			selectHandler();
		}
	}
	
	bool MetaPointElement::onTouchMove(const TouchEvent& touchEvent)
	{
		if(trackingPoint)
		{
			fgl::Vector2d metaPointCenter = toMetaPointCoordinates(touchEvent.getPosition()+initialPointTouchOffset);
			metaPoint.x = fgl::Math::roundToMultiple(metaPointCenter.x, 0.5);
			metaPoint.y = fgl::Math::roundToMultiple(metaPointCenter.y, 0.5);
			if(metaPoint.x < 0)
			{
				metaPoint.x = 0;
			}
			else if(metaPoint.x > animationSize.x)
			{
				metaPoint.x = animationSize.x;
			}
			if(metaPoint.y < 0)
			{
				metaPoint.y = 0;
			}
			else if(metaPoint.y > animationSize.y)
			{
				metaPoint.y = animationSize.y;
			}
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		}
		return true;
	}
	
	void MetaPointElement::onTouchUpInside(const TouchEvent& touchEvent)
	{
		if(trackingPoint)
		{
			trackingPoint = false;
			if(deselectHandler)
			{
				deselectHandler();
			}
		}
	}
	
	void MetaPointElement::onTouchUpOutside(const TouchEvent& touchEvent)
	{
		if(trackingPoint)
		{
			trackingPoint = false;
			if(deselectHandler)
			{
				deselectHandler();
			}
		}
	}
	
	void MetaPointElement::onTouchCancel(const TouchEvent& touchEvent)
	{
		if(trackingPoint)
		{
			trackingPoint = false;
			if(deselectHandler)
			{
				deselectHandler();
			}
		}
	}
}
