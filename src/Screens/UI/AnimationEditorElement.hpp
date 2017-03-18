
#pragma once

#include <fightlib/fightlib.hpp>
#include "MetaPointGroupElement.hpp"
#include "CheckerboardElement.hpp"

namespace flui
{
	class AnimationEditorElement : public fgl::ScreenElement
	{
	public:
		AnimationEditorElement();
		AnimationEditorElement(const fgl::RectangleD& frame);
		virtual ~AnimationEditorElement();

		virtual void layoutChildElements() override;
		virtual void update(fgl::ApplicationData appData) override;

		void setAnimationData(fl::AnimationData* animationData);
		fl::AnimationData* getAnimationData() const;

		void setAnimationFrameIndex(size_t frameIndex);
		size_t getAnimationFrameIndex() const;

		void setTracingAnimationFrameIndex(size_t frameIndex);
		size_t getTracingAnimationFrameIndex() const;

		void setTracingAnimationVisible(bool visible);
		bool isTracingAnimationVisible() const;
		
		void setAnimationDirection(const fgl::Animation::Direction& direction);
		const fgl::Animation::Direction& getAnimationDirection() const;
		
		void setDrawnOrientation(fl::AnimationOrientation orientation);
		fl::AnimationOrientation getDrawnOrientation() const;
		
		void setMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType, bool visible);
		bool isMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType) const;

		void setMetaPoints(size_t frameIndex, const fgl::ArrayList<fl::AnimationMetaPoint>& metaPoints);
		void setMetaPoint(size_t frameIndex, size_t metaPointIndex, const fl::AnimationMetaPoint& metaPoint);
		fgl::ArrayList<fl::AnimationMetaPoint> getMetaPoints(size_t frameIndex) const;
		const fl::AnimationMetaPoint& getMetaPoint(size_t frameIndex, size_t metaPointIndex) const;

		void setMetaPointSelectHandler(const std::function<void(size_t index)>& handler);
		const std::function<void(size_t)>& getMetaPointSelectHandler() const;

	private:
		void updateMetaPoints();

		fl::AnimationData* animationData;

		CheckerboardElement* checkerboardBackground;
		fgl::AnimationElement* tracingAnimationElement;
		fgl::AnimationElement* animationElement;
		MetaPointGroupElement* metaPointsElement;
		fl::AnimationOrientation drawnOrientation;
	};
}
