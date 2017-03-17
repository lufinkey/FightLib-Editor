
#include "MetaPointElement.hpp"

namespace flui
{
	void MetaPointElement::drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		if(animationSize.x != 0 && animationSize.y != 0)
		{
			fgl::RectangleD frame = getFrame();
			graphics.translate(frame.x, frame.y);
			graphics.scale(frame.width/animationSize.x, frame.height/animationSize.y);
			metaPoint.draw(graphics);
		}
	}

	void MetaPointElement::setMetaPoint(const fl::AnimationMetaPoint& metaPoint_arg)
	{
		metaPoint = metaPoint_arg;
	}

	const fl::AnimationMetaPoint& MetaPointElement::getMetaPoint() const
	{
		return metaPoint;
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
}
