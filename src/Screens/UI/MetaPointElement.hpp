
#pragma once

#include <fightlib/fightlib.hpp>

namespace flui
{
	class MetaPointElement : public fgl::TouchElement
	{
	public:
		MetaPointElement();
		MetaPointElement(const fgl::RectangleD& frame);

		virtual bool isPointInside(const fgl::Vector2d& point) const override;

		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;
		void clearMetaPoint();

		void setAnimationSize(const fgl::Vector2u& animationSize);
		const fgl::Vector2u& getAnimationSize() const;

		void setMetaPointChangeHandler(const std::function<void(fl::AnimationMetaPoint)>& handler);
		const std::function<void(fl::AnimationMetaPoint)>& getMetaPointChangeHandler() const;

		void setSelectHandler(const std::function<void()>& handler);
		const std::function<void()>& getSelectHandler() const;

		void setDeselectHandler(const std::function<void()>& handler);
		const std::function<void()>& getDeselectHandler() const;

		void setAnchorSize(double pointSize);
		double getAnchorSize() const;

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
		fgl::Vector2d fromMetaPointCoordinates(const fgl::Vector2d& point) const;
		
		fl::AnimationMetaPoint metaPoint;
		fgl::Vector2u animationSize;
		std::function<void(fl::AnimationMetaPoint)> metaPointChangeHandler;
		std::function<void()> selectHandler;
		std::function<void()> deselectHandler;
		fgl::Vector2d initialPointTouchOffset;
		double anchorSize;
		bool createdPoint;
		bool trackingPoint;
	};
}
