
#include "EditAnimationScreen.hpp"

namespace flui
{
	EditAnimationScreen::EditAnimationScreen(fgl::AssetManager* assetManager, fl::AnimationData* animationData_arg)
		: animationData(animationData_arg)
	{
		nameInputElement = new fgl::TextInputElement();
		nameInputElement->setText(animationData->getName());
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		nameInputElement->setFontSize(24);
		nameInputElement->setResigningOnOutsideTouchEnabled(true);

		animationEditorElement = new AnimationEditorElement();
		animationEditorElement->setAnimationData(animationData);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.2, fgl::LAYOUTVALUE_RATIO);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.2, fgl::LAYOUTVALUE_RATIO);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 52);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 10);
		
		leftSidebarContainer = new ToolboxContainerElement();
		leftSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.8, fgl::LAYOUTVALUE_RATIO);
		leftSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		leftSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_TOP, 52);
		leftSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 10);

		rightSidebarContainer = new fgl::ScreenElement();
		rightSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.8, fgl::LAYOUTVALUE_RATIO);
		rightSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		rightSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_TOP, 52);
		rightSidebarContainer->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 10);
		
		//Right Sidebar

		frameIndexLabel = new fgl::TextElement();
		frameIndexLabel->setText(getFrameIndexLabelString());
		frameIndexLabel->setFontSize(24);
		frameIndexLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		frameIndexLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, 30);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		
		assetManager->loadTexture("assets/images/arrow_button.png");
		
		nextFrameButton = new fgl::ButtonElement();
		nextFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.5, fgl::LAYOUTVALUE_RATIO);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 50);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		nextFrameButton->setTapHandler([=]{
			nextFrame();
		});
		
		prevFrameButton = new fgl::ButtonElement();
		prevFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevFrameButton->getImageElement()->setHorizontalImageMirroringEnabled(true);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.5, fgl::LAYOUTVALUE_RATIO);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 50);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		prevFrameButton->setTapHandler([=]{
			previousFrame();
		});
		
		metapointCheckboxHeaderLabel = new fgl::TextElement();
		metapointCheckboxHeaderLabel->setFontSize(18);
		metapointCheckboxHeaderLabel->setText("Meta Points");
		metapointCheckboxHeaderLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		metapointCheckboxHeaderLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, 106);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);

		fgl::ArrayList<fl::AnimationMetaPoint::Type> metaPointTypes = {
			fl::AnimationMetaPoint::POINTTYPE_HITBOX,
			fl::AnimationMetaPoint::POINTTYPE_HEAD,
			fl::AnimationMetaPoint::POINTTYPE_LEFTHAND,
			fl::AnimationMetaPoint::POINTTYPE_RIGHTHAND,
			fl::AnimationMetaPoint::POINTTYPE_BOUNDS_TOPLEFT,
			fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT,
			fl::AnimationMetaPoint::POINTTYPE_HANDLE
		};

		double metapointCheckboxY = 130;
		for(auto metaPointType : metaPointTypes)
		{
			auto metapointCheckbox = new LabeledCheckboxElement();
			metapointCheckbox->setText(MetaPointInfoElement::getMetaPointTypeName(metaPointType));
			metapointCheckbox->getLabelElement()->setFontSize(14);
			metapointCheckbox->setToggle(false);
			metapointCheckbox->setToggleHandler([=](bool value){
				animationEditorElement->setMetaPointTypeVisible(metaPointType, value);
			});
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_TOP, metapointCheckboxY);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_LEFT, 4);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 26);

			metapointCheckboxElements[metaPointType] = metapointCheckbox;

			metapointCheckboxY += 28;
		}

		rightSidebarContainer->addChildElement(frameIndexLabel);
		rightSidebarContainer->addChildElement(nextFrameButton);
		rightSidebarContainer->addChildElement(prevFrameButton);
		rightSidebarContainer->addChildElement(metapointCheckboxHeaderLabel);
		for(auto checkboxPair : metapointCheckboxElements)
		{
			rightSidebarContainer->addChildElement(checkboxPair.second);
		}
		
		//Left Sidebar
		
		metaPointInfoElement = new MetaPointInfoElement(assetManager);
		
		getElement()->addChildElement(animationEditorElement);
		getElement()->addChildElement(nameInputElement);
		getElement()->addChildElement(leftSidebarContainer);
		getElement()->addChildElement(rightSidebarContainer);
	}
	
	EditAnimationScreen::~EditAnimationScreen()
	{
		delete nameInputElement;
		delete animationEditorElement;
		delete leftSidebarContainer;
		delete rightSidebarContainer;
		delete frameIndexLabel;
		delete nextFrameButton;
		delete prevFrameButton;
		delete metaPointInfoElement;
		delete metapointCheckboxHeaderLabel;
		for(auto checkboxPair : metapointCheckboxElements)
		{
			delete checkboxPair.second;
		}
	}
	
	void EditAnimationScreen::update(fgl::ApplicationData appData)
	{
		Screen::update(appData);
		frameIndexLabel->setText(getFrameIndexLabelString());
	}
	
	void EditAnimationScreen::nextFrame()
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation!=nullptr || animation->getTotalFrames() > 0)
		{
			size_t frameIndex = animationEditorElement->getAnimationFrameIndex();
			size_t frameCount = animation->getTotalFrames();
			frameIndex++;
			if(frameIndex < frameCount)
			{
				animationEditorElement->setAnimationFrameIndex(frameIndex);
			}
		}
	}
	
	void EditAnimationScreen::previousFrame()
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation!=nullptr || animation->getTotalFrames() > 0)
		{
			size_t frameIndex = animationEditorElement->getAnimationFrameIndex();
			frameIndex--;
			if(frameIndex != -1)
			{
				animationEditorElement->setAnimationFrameIndex(frameIndex);
			}
		}
	}
	
	fgl::String EditAnimationScreen::getFrameIndexLabelString() const
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation==nullptr || animation->getTotalFrames()==0)
		{
			return "0/0";
		}
		size_t frameIndex = animationEditorElement->getAnimationFrameIndex();
		size_t frameCount = animation->getTotalFrames();
		return (fgl::String)""+(frameIndex+1)+"/"+frameCount;
	}
}
