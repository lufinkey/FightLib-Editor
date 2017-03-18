
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
		const fgl::ArrayList<fl::AnimationMetaPoint>& getMetaPoints() const;

		void setMetaPointChangeHandler(const std::function<void(size_t index)>& handler);
		const std::function<void(size_t)>& getMetaPointChangeHandler() const;

		void setMetaPointSelectHandler(const std::function<void(size_t index)>& handler);
		const std::function<void(size_t)>& getMetaPointSelectHandler() const;

		void setAnimationSize(const fgl::Vector2d& animationSize);
		const fgl::Vector2d& getAnimationSize() const;

		void setMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType, bool visible);
		bool isMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType) const;

		void setHorizontalMirroringEnabled(bool mirror);
		bool isHorizontalMirroringEnabled() const;

	private:
		fgl::ArrayList<fl::AnimationMetaPoint> metaPoints;
		fgl::ArrayList<MetaPointElement*> metaPointElements;
		std::function<void(size_t)> metaPointChangeHandler;
		std::function<void(size_t)> metaPointSelectHandler;
		fgl::Vector2d animationSize;
		fgl::BasicDictionary<fl::AnimationMetaPoint::Type, bool> enabledMetaPointTypes;
		bool horizontalMirroringEnabled;
	};
}
