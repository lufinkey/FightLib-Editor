
#include "MetaPointGroupElement.hpp"

namespace flui
{
	MetaPointGroupElement::MetaPointGroupElement() : MetaPointGroupElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}

	MetaPointGroupElement::MetaPointGroupElement(const fgl::RectangleD& frame) : ScreenElement(frame),
		horizontalMirroringEnabled(false),
		boundsDrawingEnabled(false)
	{
		//
	}

	MetaPointGroupElement::~MetaPointGroupElement()
	{
		for(auto metaPointElement : metaPointElements)
		{
			delete metaPointElement;
		}
	}

	void MetaPointGroupElement::draw(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		fgl::RectangleD frame = getFrame();
		if(horizontalMirroringEnabled)
		{
			graphics.scale(fgl::Vector2d(-1, 1), fgl::Vector2d(frame.x+(frame.width/2), frame.y));
		}
		ScreenElement::draw(appData, graphics);
	}

	void MetaPointGroupElement::drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		if(boundsDrawingEnabled && animationSize.x > 0 && animationSize.y > 0)
		{
			fgl::RectangleD frame = getFrame();
			graphics.translate(frame.x, frame.y);
			graphics.setColor(fgl::Color::BLUE);
			double xRatio = frame.width/(double)animationSize.x;
			double yRatio = frame.height/(double)animationSize.y;
			for(auto& bound : getBounds())
			{
				graphics.drawRect(bound.rect.x*xRatio, bound.rect.y*yRatio, bound.rect.width*xRatio, bound.rect.height*yRatio);
			}
		}
	}

	void MetaPointGroupElement::setMetaPoints(const fgl::ArrayList<fl::AnimationMetaPoint>& metaPoints_arg)
	{
		metaPoints = metaPoints_arg;
		for(auto metaPointElement : metaPointElements)
		{
			metaPointElement->removeFromParentElement();
			delete metaPointElement;
		}
		metaPointElements.clear();
		metaPointElements.reserve(metaPoints.size());
		size_t metaPointIndex = 0;
		for(auto& metaPoint : metaPoints)
		{
			auto metaPointElement = new MetaPointElement();
			metaPointElement->setAnimationSize(animationSize);
			metaPointElement->setMetaPoint(metaPoint);
			metaPointElement->setMetaPointChangeHandler([=](fl::AnimationMetaPoint metaPoint){
				metaPoints[metaPointIndex] = metaPoint;
				if(metaPointChangeHandler)
				{
					metaPointChangeHandler(metaPointIndex);
				}
			});
			metaPointElement->setSelectHandler([=]{
				if(metaPointSelectHandler)
				{
					metaPointSelectHandler(metaPointIndex);
				}
			});
			metaPointElement->setVisible(isMetaPointTypeVisible(metaPoint.type));
			metaPointElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			metaPointElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			metaPointElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			metaPointElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
			metaPointElements.add(metaPointElement);
			addChildElement(metaPointElement);
			metaPointIndex++;
		}
	}

	void MetaPointGroupElement::setMetaPoint(size_t index, const fl::AnimationMetaPoint& metaPoint)
	{
		metaPoints[index] = metaPoint;
		metaPointElements[index]->setMetaPoint(metaPoint);
	}

	const fgl::ArrayList<fl::AnimationMetaPoint>& MetaPointGroupElement::getMetaPoints() const
	{
		return metaPoints;
	}

	const fl::AnimationMetaPoint& MetaPointGroupElement::getMetaPoint(size_t index) const
	{
		return metaPoints[index];
	}

	void MetaPointGroupElement::setMetaPointChangeHandler(const std::function<void(size_t)>& handler)
	{
		metaPointChangeHandler = handler;
	}

	const std::function<void(size_t)>& MetaPointGroupElement::getMetaPointChangeHandler() const
	{
		return metaPointChangeHandler;
	}

	void MetaPointGroupElement::setMetaPointSelectHandler(const std::function<void(size_t)>& handler)
	{
		metaPointSelectHandler = handler;
	}

	const std::function<void(size_t)>& MetaPointGroupElement::getMetaPointSelectHandler() const
	{
		return metaPointSelectHandler;
	}

	void MetaPointGroupElement::setAnimationSize(const fgl::Vector2u& animationSize_arg)
	{
		animationSize = animationSize_arg;
		for(auto metaPointElement : metaPointElements)
		{
			metaPointElement->setAnimationSize(animationSize);
		}
	}

	const fgl::Vector2u& MetaPointGroupElement::getAnimationSize() const
	{
		return animationSize;
	}

	void MetaPointGroupElement::setMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType, bool visible)
	{
		enabledMetaPointTypes[metaPointType] = visible;
		for(auto metaPointElement : metaPointElements)
		{
			if(metaPointElement->getMetaPoint().type==metaPointType)
			{
				metaPointElement->setVisible(visible);
			}
		}
	}

	bool MetaPointGroupElement::isMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType) const
	{
		return enabledMetaPointTypes.get(metaPointType, true);
	}

	void MetaPointGroupElement::setHorizontalMirroringEnabled(bool mirror)
	{
		horizontalMirroringEnabled = mirror;
	}

	bool MetaPointGroupElement::isHorizontalMirroringEnabled() const
	{
		return horizontalMirroringEnabled;
	}

	void MetaPointGroupElement::setBoundsDrawingEnabled(bool enabled)
	{
		boundsDrawingEnabled = enabled;
	}

	bool MetaPointGroupElement::isBoundsDrawingEnabled() const
	{
		return boundsDrawingEnabled;
	}

	fgl::ArrayList<fl::AnimationData::MetaBounds> MetaPointGroupElement::getBounds() const
	{
		fgl::ArrayList<fl::AnimationMetaPoint> topLefts;
		fgl::ArrayList<fl::AnimationMetaPoint> bottomRights;
		for(auto& metaPoint : metaPoints)
		{
			if(metaPoint.type==fl::AnimationMetaPoint::POINTTYPE_BOUNDS_TOPLEFT)
			{
				topLefts.add(metaPoint);
			}
			else if(metaPoint.type==fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT)
			{
				bottomRights.add(metaPoint);
			}
		}
		fgl::ArrayList<fl::AnimationData::MetaBounds> bounds;
		while(topLefts.size()>0)
		{
			auto& topLeft = topLefts[0];
			for(size_t i=0; i<bottomRights.size(); i++)
			{
				auto& bottomRight = bottomRights[i];
				if(topLeft.tag==bottomRight.tag)
				{
					fgl::RectangleD rect = fgl::RectangleD((double)topLeft.x, (double)topLeft.y, (double)(bottomRight.x-topLeft.x), (double)(bottomRight.y - topLeft.y));
					fl::AnimationData::MetaBounds metaBounds = { .tag=topLeft.tag, .rect=rect };
					bounds.add(metaBounds);
					bottomRights.remove(i);
					break;
				}
			}
			topLefts.remove(0);
		}
		return bounds;
	}
}
