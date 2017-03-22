
#include "MetaPointInfoElement.hpp"

namespace flui
{
	MetaPointInfoElement::MetaPointInfoElement(fgl::AssetManager* assetManager) : MetaPointInfoElement(assetManager, fgl::RectangleD(0,0,0,0))
	{
		//
	}
	
	MetaPointInfoElement::MetaPointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame)
		: ToolboxElement(frame)
	{
		double offsetY = 10;

		typeLabel = new fgl::TextElement();
		typeLabel->setText("Type");
		typeLabel->setFontSize(14);
		typeLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		offsetY += 2;
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
		typeSelectorElement->setValueChangeHandler([=]{
			metaPoint.type = typeSelectorElement->getOptionList()[typeSelectorElement->getSelectedOptionIndex()].toArithmeticValue<fl::AnimationMetaPoint::Type>();
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 1;
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		typeSelectorElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
		offsetY += 14;

		xLabel = new fgl::TextElement();
		xLabel->setText("X");
		xLabel->setFontSize(14);
		xLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		xLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		offsetY += 10;
		xLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		xLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		xLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		xLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;

		xAdjustElement = new NumberAdjustElement(assetManager);
		xAdjustElement->getValueLabel()->setFontSize(12);
		xAdjustElement->setValue(0);
		xAdjustElement->setMinValue(0);
		xAdjustElement->setMaxValue(0);
		xAdjustElement->setIncrement(0.5);
		xAdjustElement->setValueChangeHandler([=] {
			metaPoint.x = xAdjustElement->getValue().toArithmeticValue<float>();
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 1;
		xAdjustElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		xAdjustElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		xAdjustElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		xAdjustElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
		offsetY += 14;

		yLabel = new fgl::TextElement();
		yLabel->setText("Y");
		yLabel->setFontSize(14);
		yLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		yLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		offsetY += 10;
		yLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		yLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		yLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		yLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;

		yAdjustElement = new NumberAdjustElement(assetManager);
		yAdjustElement->getValueLabel()->setFontSize(12);
		yAdjustElement->setValue(0);
		yAdjustElement->setMinValue(0);
		yAdjustElement->setMaxValue(0);
		yAdjustElement->setIncrement(0.5);
		yAdjustElement->setValueChangeHandler([=]{
			metaPoint.y = yAdjustElement->getValue().toArithmeticValue<float>();
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 1;
		yAdjustElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		yAdjustElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		yAdjustElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		yAdjustElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
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
		radiusAdjustElement->setValueChangeHandler([=]{
			metaPoint.radius = radiusAdjustElement->getValue().toArithmeticValue<float>();
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 1;
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		radiusAdjustElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
		offsetY += 14;

		rotationLabel = new fgl::TextElement();
		rotationLabel->setText("Rotation");
		rotationLabel->setFontSize(14);
		rotationLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		rotationLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		offsetY += 10;
		rotationLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		rotationLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		rotationLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		rotationLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;

		rotationAdjustElement = new NumberAdjustElement(assetManager);
		rotationAdjustElement->getValueLabel()->setFontSize(12);
		rotationAdjustElement->setValue(0);
		rotationAdjustElement->setMinValue(0);
		rotationAdjustElement->setMaxValue(160);
		rotationAdjustElement->setIncrement(1);
		rotationAdjustElement->setValueChangeHandler([=]{
			metaPoint.rotation = rotationAdjustElement->getValue().toArithmeticValue<float>();
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 1;
		rotationAdjustElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		rotationAdjustElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		rotationAdjustElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		rotationAdjustElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 14);
		offsetY += 14;
		
		orientationLabel = new fgl::TextElement();
		orientationLabel->setText("Orientation");
		orientationLabel->setFontSize(14);
		orientationLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		orientationLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		offsetY += 10;
		orientationLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		orientationLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		orientationLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		orientationLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;
		
		orientationSelector = new fgl::SegmentedSelectorElement();
		orientationSelector->setFontSize(12);
		orientationSelector->setItems({"Left", "Neutral", "Right"});
		orientationSelector->setSelectedItemIndex(1);
		orientationSelector->setSelectionHandler([=](size_t index){
			switch(index)
			{
				case 0:
					metaPoint.orientation = fl::ANIMATIONORIENTATION_LEFT;
					break;
					
				case 1:
					metaPoint.orientation = fl::ANIMATIONORIENTATION_NEUTRAL;
					break;
					
				case 2:
					metaPoint.orientation = fl::ANIMATIONORIENTATION_RIGHT;
					break;
			}
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 2;
		orientationSelector->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		orientationSelector->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		orientationSelector->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		orientationSelector->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		offsetY += 16;

		behindCheckbox = new LabeledCheckboxElement();
		behindCheckbox->setText("Behind");
		behindCheckbox->getLabelElement()->setFontSize(14);
		behindCheckbox->setToggleHandler([=](bool toggle){
			metaPoint.behind = toggle;
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 10;
		behindCheckbox->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		behindCheckbox->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		behindCheckbox->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		behindCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		offsetY += 20;

		visibleCheckbox = new LabeledCheckboxElement();
		visibleCheckbox->setText("Visible");
		visibleCheckbox->getLabelElement()->setFontSize(14);
		visibleCheckbox->setToggleHandler([=](bool toggle){
			metaPoint.visible = toggle;
			if(metaPointChangeHandler)
			{
				metaPointChangeHandler(metaPoint);
			}
		});
		offsetY += 10;
		visibleCheckbox->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		visibleCheckbox->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		visibleCheckbox->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		visibleCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		offsetY += 20;
		
		addChildElement(typeLabel);
		addChildElement(typeSelectorElement);
		addChildElement(xLabel);
		addChildElement(xAdjustElement);
		addChildElement(yLabel);
		addChildElement(yAdjustElement);
		addChildElement(radiusLabel);
		addChildElement(radiusAdjustElement);
		addChildElement(rotationLabel);
		addChildElement(rotationAdjustElement);
		addChildElement(orientationLabel);
		addChildElement(orientationSelector);
		addChildElement(behindCheckbox);
		addChildElement(visibleCheckbox);
	}
	
	MetaPointInfoElement::~MetaPointInfoElement()
	{
		delete typeLabel;
		delete typeSelectorElement;
		delete xAdjustElement;
		delete yAdjustElement;
		delete radiusLabel;
		delete radiusAdjustElement;
		delete rotationLabel;
		delete rotationAdjustElement;
		delete orientationLabel;
		delete orientationSelector;
		delete behindCheckbox;
		delete visibleCheckbox;
	}

	fgl::String MetaPointInfoElement::getTitle() const
	{
		return "Meta Point";
	}
	
	void MetaPointInfoElement::setMetaPoint(const fl::AnimationMetaPoint& metaPoint_arg)
	{
		metaPoint = metaPoint_arg;
		size_t metaPointTypeIndex = typeSelectorElement->getOptionList().indexOf(metaPoint.type);
		typeSelectorElement->setSelectedOptionIndex(metaPointTypeIndex);
		xAdjustElement->setValue(metaPoint.x);
		yAdjustElement->setValue(metaPoint.y);
		radiusAdjustElement->setValue(metaPoint.radius);
		rotationAdjustElement->setValue(metaPoint.rotation);
		switch(metaPoint.orientation)
		{
			case fl::ANIMATIONORIENTATION_LEFT:
				orientationSelector->setSelectedItemIndex(0);
				break;
				
			case fl::ANIMATIONORIENTATION_NEUTRAL:
				orientationSelector->setSelectedItemIndex(1);
				break;
				
			case fl::ANIMATIONORIENTATION_RIGHT:
				orientationSelector->setSelectedItemIndex(2);
				break;
		}
		behindCheckbox->setToggle(metaPoint.behind);
		visibleCheckbox->setToggle(metaPoint.visible);
	}

	const fl::AnimationMetaPoint& MetaPointInfoElement::getMetaPoint() const
	{
		return metaPoint;
	}

	void MetaPointInfoElement::setMetaPointChangeHandler(const std::function<void(fl::AnimationMetaPoint)>& handler)
	{
		metaPointChangeHandler = handler;
	}

	const std::function<void(fl::AnimationMetaPoint)>& MetaPointInfoElement::getMetaPointChangeHandler() const
	{
		return metaPointChangeHandler;
	}

	void MetaPointInfoElement::setAnimationSize(const fgl::Vector2u& animationSize_arg)
	{
		animationSize = animationSize_arg;
		xAdjustElement->setMaxValue(animationSize.x);
		yAdjustElement->setMaxValue(animationSize.y);
	}

	const fgl::Vector2u& MetaPointInfoElement::getAnimationSize() const
	{
		return animationSize;
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
