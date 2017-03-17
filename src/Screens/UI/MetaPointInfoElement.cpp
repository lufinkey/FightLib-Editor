
#include "MetaPointInfoElement.hpp"

namespace flui
{
	MetaPointInfoElement::MetaPointInfoElement(fgl::AssetManager* assetManager) : MetaPointInfoElement(assetManager, fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	MetaPointInfoElement::MetaPointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame)
		: ScreenElement(frame)
	{
		double offsetY = 10;

		typeLabel = new fgl::TextElement();
		typeLabel->setText("Type");
		typeLabel->setFontSize(14);
		typeLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		typeLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		typeLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		typeLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		typeLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		typeLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;
		
		fgl::ArrayList<fgl::Number> typeOptionList = {
									fl::AnimationMetaPoint::POINTTYPE_HITBOX,
									fl::AnimationMetaPoint::POINTTYPE_HEAD,
									fl::AnimationMetaPoint::POINTTYPE_LEFTHAND,
									fl::AnimationMetaPoint::POINTTYPE_RIGHTHAND,
									fl::AnimationMetaPoint::POINTTYPE_BOUNDS_TOPLEFT,
									fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT,
									fl::AnimationMetaPoint::POINTTYPE_HANDLE };
		typeSelectorElement = new CarouselSelectorElement(assetManager, typeOptionList);
		typeSelectorElement->getValueLabel()->setFontSize(12);
		typeSelectorElement->setOptionTitleResolver([=](fgl::Number value) -> fgl::String {
			return getMetaPointTypeName(value.toArithmeticValue<fl::AnimationMetaPoint::Type>());
		});
		typeSelectorElement->setSelectedOptionIndex(0);
		offsetY += 1;
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
		offsetY += 14;
		
		radiusLabel = new fgl::TextElement();
		radiusLabel->setText("Radius");
		radiusLabel->setFontSize(14);
		radiusLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		radiusLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		offsetY += 10;
		radiusLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		radiusLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		radiusLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		radiusLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;
		
		radiusAdjustElement = new NumberAdjustElement(assetManager);
		radiusAdjustElement->getValueLabel()->setFontSize(12);
		radiusAdjustElement->setValue(0);
		radiusAdjustElement->setMinValue(0);
		radiusAdjustElement->setMaxValue(9999);
		radiusAdjustElement->setIncrement(0.5);
		offsetY += 1;
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
		
		addChildElement(typeLabel);
		addChildElement(typeSelectorElement);
		addChildElement(radiusLabel);
		addChildElement(radiusAdjustElement);
	}
	
	MetaPointInfoElement::~MetaPointInfoElement()
	{
		delete typeLabel;
		delete typeSelectorElement;
		delete radiusLabel;
		delete radiusAdjustElement;
	}
	
	void MetaPointInfoElement::setMetaPoint(const fl::AnimationMetaPoint& metaPoint_arg)
	{
		metaPoint = metaPoint_arg;
		size_t metaPointTypeIndex = typeSelectorElement->getOptionList().indexOf(metaPoint.type);
		typeSelectorElement->setSelectedOptionIndex(metaPointTypeIndex);
		radiusAdjustElement->setValue(metaPoint.radius);
	}

	const fl::AnimationMetaPoint& MetaPointInfoElement::getMetaPoint() const
	{
		return metaPoint;
	}

	fgl::String MetaPointInfoElement::getMetaPointTypeName(fl::AnimationMetaPoint::Type metaPointType)
	{
		switch(metaPointType)
		{
			case fl::AnimationMetaPoint::POINTTYPE_HITBOX:
			return "hitbox";

			case fl::AnimationMetaPoint::POINTTYPE_HEAD:
			return "head";

			case fl::AnimationMetaPoint::POINTTYPE_LEFTHAND:
			return "hand (L)";

			case fl::AnimationMetaPoint::POINTTYPE_RIGHTHAND:
			return "hand (R)";

			case fl::AnimationMetaPoint::POINTTYPE_BOUNDS_TOPLEFT:
			return "bounds (TL)";

			case fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT:
			return "bounds (BR)";

			case fl::AnimationMetaPoint::POINTTYPE_HANDLE:
			return "handle";
		}
		return (fgl::String)""+metaPointType;
	}
}
