
#pragma once

#include <fightlib/fightlib.hpp>

namespace flui
{
	class MetaPointElement : public fgl::TouchElement
	{
	public:
		MetaPointElement();
		MetaPointElement(const fgl::RectangleD& frame);

		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;
		void clearMetaPoint();

		void setAnimationSize(const fgl::Vector2d& animationSize);
		const fgl::Vector2d& getAnimationSize() const;

		void setMetaPointChangeHandler(const std::function<void(fl::AnimationMetaPoint)>& handler);
		const std::function<void(fl::AnimationMetaPoint)>& getMetaPointChangeHandler() const;

	protected:
		virtual void drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
		
		virtual void onTouchDown(const TouchEvent& touchEvent) override;
		virtual bool onTouchMove(const TouchEvent& touchEvent) override;
		virtual void onTouchUpInside(const TouchEvent& touchEvent) override;
		virtual void onTouchUpOutside(const TouchEvent& touchEvent) override;
		virtual void onTouchCancel(const TouchEvent& touchEvent) override;

	private:
		fgl::Vector2d getMetaPointCenter() const;
		fgl::Vector2d toMetaPointCoordinates(const fgl::Vector2d& point) const;
		bool isTouchPointOnCenter(const fgl::Vector2d& point) const;
		
		fl::AnimationMetaPoint metaPoint;
		fgl::Vector2d animationSize;
		std::function<void(fl::AnimationMetaPoint)> metaPointChangeHandler;
		bool createdPoint;
		bool trackingPoint;
		fgl::Vector2d initialPointTouchOffset;
	};
}