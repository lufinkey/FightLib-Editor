
#include "MetaPointGroupElement.hpp"

namespace flui
{
	MetaPointGroupElement::MetaPointGroupElement() : MetaPointGroupElement(fgl::RectangleD(0,0,0,0))
	{
		//
	}

	MetaPointGroupElement::MetaPointGroupElement(const fgl::RectangleD& frame) : ScreenElement(frame),
		horizontalMirroringEnabled(false)
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
			metaPointElement->setMetaPointChangeHandler([=](fl::AnimationMetaPoint){
				if(this->metaPointChangeHandler)
				{
					this->metaPointChangeHandler(metaPointIndex);
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

	const fgl::ArrayList<fl::AnimationMetaPoint>& MetaPointGroupElement::getMetaPoints() const
	{
		return metaPoints;
	}

	void MetaPointGroupElement::setMetaPointChangeHandler(const std::function<void(size_t)>& handler)
	{
		metaPointChangeHandler = handler;
	}

	const std::function<void(size_t)>& MetaPointGroupElement::getMetaPointChangeHandler() const
	{
		return metaPointChangeHandler;
	}

	void MetaPointGroupElement::setAnimationSize(const fgl::Vector2d& animationSize_arg)
	{
		animationSize = animationSize_arg;
		for(auto metaPointElement : metaPointElements)
		{
			metaPointElement->setAnimationSize(animationSize);
		}
	}

	const fgl::Vector2d& MetaPointGroupElement::getAnimationSize() const
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
		return enabledMetaPointTypes.get(metaPointType, false);
	}

	void MetaPointGroupElement::setHorizontalMirroringEnabled(bool mirror)
	{
		horizontalMirroringEnabled = mirror;
	}

	bool MetaPointGroupElement::isHorizontalMirroringEnabled() const
	{
		return horizontalMirroringEnabled;
	}
}