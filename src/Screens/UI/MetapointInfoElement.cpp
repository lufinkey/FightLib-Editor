
#include "MetapointInfoElement.hpp"

namespace flui
{
	MetapointInfoElement::MetapointInfoElement(fgl::AssetManager* assetManager) : MetapointInfoElement(assetManager, fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	MetapointInfoElement::MetapointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame)
		: ScreenElement(frame)
	{
		fgl::ArrayList<fgl::Number> typeOptionList = {
									fl::AnimationMetaPoint::POINTTYPE_HITBOX,
									fl::AnimationMetaPoint::POINTTYPE_HEAD,
									fl::AnimationMetaPoint::POINTTYPE_LEFTHAND,
									fl::AnimationMetaPoint::POINTTYPE_RIGHTHAND,
									fl::AnimationMetaPoint::POINTTYPE_BOUNDS_TOPLEFT,
									fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT,
									fl::AnimationMetaPoint::POINTTYPE_HANDLE };
		typeSelectorElement = new CarouselSelectorElement(assetManager, typeOptionList);
		typeSelectorElement->setOptionTitleResolver([=](fgl::Number value) -> fgl::String {
			switch(value.toArithmeticValue<fl::AnimationMetaPoint::Type>())
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
					return "bound (TL)";
					
				case fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT:
					return "bounds (BR)";
					
				case fl::AnimationMetaPoint::POINTTYPE_HANDLE:
					return "handle";
			}
			return "";
		});
		typeSelectorElement->setSelectedOptionIndex(0);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 50);
		
		addChildElement(typeSelectorElement);
	}
	
	MetapointInfoElement::~MetapointInfoElement()
	{
		delete typeSelectorElement;
	}
	
	void MetapointInfoElement::setMetaPoint(const fl::AnimationMetaPoint& metaPoint_arg)
	{
		metaPoint = metaPoint_arg;
	}
}
