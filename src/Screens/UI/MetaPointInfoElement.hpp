
#pragma once

#include <fightlib/fightlib.hpp>
#include "ToolboxElement.hpp"
#include "CarouselSelectorElement.hpp"
#include "LabeledCheckboxElement.hpp"
#include "NumberAdjustElement.hpp"

namespace flui
{
	class MetaPointInfoElement : public ToolboxElement
	{
	public:
		MetaPointInfoElement(fgl::AssetManager* assetManager);
		MetaPointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame);
		virtual ~MetaPointInfoElement();

		virtual fgl::String getTitle() const override;
		
		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;

		void setMetaPointChangeHandler(const std::function<void(fl::AnimationMetaPoint)>& handler);
		const std::function<void(fl::AnimationMetaPoint)>& getMetaPointChangeHandler() const;

		void setMetaPointDeleteHandler(const std::function<void()>& handler);
		const std::function<void()>& getMetaPointDeleteHandler() const;

		void setAnimationSize(const fgl::Vector2u& animationSize);
		const fgl::Vector2u& getAnimationSize() const;

		static fgl::String getMetaPointTypeName(fl::AnimationMetaPoint::Type metaPointType);
		
	private:
		fl::AnimationMetaPoint metaPoint;
		std::function<void(fl::AnimationMetaPoint)> metaPointChangeHandler;
		std::function<void()> metaPointDeleteHandler;
		fgl::Vector2u animationSize;

		fgl::TextElement* typeLabel;
		CarouselSelectorElement* typeSelectorElement;
		fgl::TextElement* xLabel;
		NumberAdjustElement* xAdjustElement;
		fgl::TextElement* yLabel;
		NumberAdjustElement* yAdjustElement;
		fgl::TextElement* radiusLabel;
		NumberAdjustElement* radiusAdjustElement;
		fgl::TextElement* rotationLabel;
		NumberAdjustElement* rotationAdjustElement;
		fgl::TextElement* orientationLabel;
		fgl::SegmentedSelectorElement* orientationSelector;
		LabeledCheckboxElement* behindCheckbox;
		LabeledCheckboxElement* visibleCheckbox;
		fgl::ButtonElement* deleteButtonElement;
	};
}
