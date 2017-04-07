
#pragma once

#include "MetaPointElement.hpp"

namespace flui
{
	class MetaPointGroupElement : public fgl::ScreenElement
	{
	public:
		MetaPointGroupElement();
		MetaPointGroupElement(const fgl::RectangleD& frame);
		virtual ~MetaPointGroupElement();

		virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;

		void setMetaPoints(const fgl::ArrayList<fl::AnimationMetaPoint>& metaPoints);
		void setMetaPoint(size_t index, const fl::AnimationMetaPoint& metaPoint);
		const fgl::ArrayList<fl::AnimationMetaPoint>& getMetaPoints() const;
		const fl::AnimationMetaPoint& getMetaPoint(size_t index) const;

		void setMetaPointChangeHandler(const std::function<void(size_t index)>& handler);
		const std::function<void(size_t)>& getMetaPointChangeHandler() const;

		void setMetaPointSelectHandler(const std::function<void(size_t index)>& handler);
		const std::function<void(size_t)>& getMetaPointSelectHandler() const;

		void setAnimationSize(const fgl::Vector2u& animationSize);
		const fgl::Vector2u& getAnimationSize() const;

		void setMetaPointTypeVisible(fl::MetaPointType metaPointType, bool visible);
		bool isMetaPointTypeVisible(fl::MetaPointType metaPointType) const;

		void setHorizontalMirroringEnabled(bool mirror);
		bool isHorizontalMirroringEnabled() const;

		void setBoundsDrawingEnabled(bool enabled);
		bool isBoundsDrawingEnabled() const;

		fgl::ArrayList<fl::TaggedBox> getBounds() const;

	protected:
		virtual void drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const override;

	private:
		fgl::ArrayList<fl::AnimationMetaPoint> metaPoints;
		fgl::ArrayList<MetaPointElement*> metaPointElements;
		std::function<void(size_t)> metaPointChangeHandler;
		std::function<void(size_t)> metaPointSelectHandler;
		fgl::Vector2u animationSize;
		fgl::BasicDictionary<fl::MetaPointType, bool> enabledMetaPointTypes;
		bool horizontalMirroringEnabled;
		bool boundsDrawingEnabled;
	};
}
