
#pragma once

#include <fightlib/fightlib.hpp>
#include "CarouselSelectorElement.hpp"
#include "LabeledCheckboxElement.hpp"
#include "NumberAdjustElement.hpp"

namespace flui
{
	class MetaPointInfoElement : public fgl::ScreenElement
	{
	public:
		MetaPointInfoElement(fgl::AssetManager* assetManager);
		MetaPointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame);
		virtual ~MetaPointInfoElement();
		
		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;

		static fgl::String getMetaPointTypeName(fl::AnimationMetaPoint::Type metaPointType);
		
	private:
		fl::AnimationMetaPoint metaPoint;

		fgl::TextElement* metaPointLabel;
		
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
		LabeledCheckboxElement* behindCheckbox;
		LabeledCheckboxElement* visibleCheckbox;
	};
}
