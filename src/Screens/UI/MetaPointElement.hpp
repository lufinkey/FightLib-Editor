
#pragma once

#include <fightlib/fightlib.hpp>

namespace flui
{
	class MetaPointElement : public fgl::ScreenElement
	{
	public:
		using ScreenElement::ScreenElement;

		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;

		void setAnimationSize(const fgl::Vector2d& animationSize);
		const fgl::Vector2d& getAnimationSize() const;

		void setMetaPointChangeHandler(const std::function<void(fl::AnimationMetaPoint)>& handler);
		const std::function<void(fl::AnimationMetaPoint)>& getMetaPointChangeHandler() const;

	protected:
		virtual void drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const override;

	private:
		fl::AnimationMetaPoint metaPoint;
		fgl::Vector2d animationSize;
		std::function<void(fl::AnimationMetaPoint)> metaPointChangeHandler;
	};
}
