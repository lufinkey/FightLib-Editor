
#include "EditAnimationScreen.hpp"

namespace flui
{
	EditAnimationScreen::EditAnimationScreen(fgl::AssetManager* assetManager, fl::AnimationData* animationData_arg, const fgl::String& savePath)
		: animationData(animationData_arg),
		savePath(savePath),
		selectedMetaPointFrameIndex(-1),
		selectedMetaPointIndex(-1),
		addingMetaPoint(false)
	{
		overlayElement = new fgl::TouchElement();
		overlayElement->setBackgroundColor(fgl::Color::BLACK);
		overlayElement->setAlpha(0.5);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);

		// Save button
		saveButtonElement = new fgl::ButtonElement();
		saveButtonElement->setTitle("Save", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		saveButtonElement->getTitleElement()->setFontSize(16);
		saveButtonElement->setBorderWidth(1);
		saveButtonElement->setTapHandler([=]{
			fgl::String error;
			bool success = animationData->saveToFile(savePath, &error);
			if(!success)
			{
				fgl::MessageBox::show(nullptr, "Error", error);
			}
		});
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);

		// Name input
		nameInputElement = new fgl::TextInputElement();
		nameInputElement->setText(animationData->getName());
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 60);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		nameInputElement->setFontSize(24);
		nameInputElement->setResigningOnOutsideTouchEnabled(true);

		// Animation editor
		animationEditorElement = new AnimationEditorElement();
		animationEditorElement->setAnimationData(animationData);
		animationEditorElement->setMetaPointChangeHandler([=](size_t index){
			if(selectedMetaPointFrameIndex!=-1 && selectedMetaPointIndex!=-1
				&& selectedMetaPointFrameIndex==animationEditorElement->getAnimationFrameIndex()
				&& selectedMetaPointIndex==index)
			{
				metaPointInfoElement->setMetaPoint(animationEditorElement->getMetaPoint(selectedMetaPointFrameIndex, selectedMetaPointIndex));
			}
		});
		animationEditorElement->setMetaPointSelectHandler([=](size_t index){
			selectedMetaPointFrameIndex = animationEditorElement->getAnimationFrameIndex();
			selectedMetaPointIndex = index;
			metaPointInfoElement->setMetaPoint(animationEditorElement->getMetaPoint(selectedMetaPointFrameIndex, selectedMetaPointIndex));
			leftSidebarContainer->setToolboxElement(metaPointInfoElement);
		});
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.2, fgl::LAYOUTVALUE_RATIO);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.2, fgl::LAYOUTVALUE_RATIO);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 52);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 10);
		
		// Sidebar containers
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
		
		// Right sidebar
		double rOffsetY = 10;

		frameIndexLabel = new fgl::TextElement();
		frameIndexLabel->setText(getFrameIndexLabelString());
		frameIndexLabel->setFontSize(24);
		frameIndexLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		frameIndexLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, rOffsetY+(40/2));
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		rOffsetY += 40;
		
		assetManager->loadTexture("assets/images/arrow_button.png");
		
		nextFrameButton = new fgl::ButtonElement();
		nextFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextFrameButton->setTapHandler([=] {
			nextFrame();
		});
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.5, fgl::LAYOUTVALUE_RATIO);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		
		prevFrameButton = new fgl::ButtonElement();
		prevFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevFrameButton->getImageElement()->setHorizontalImageMirroringEnabled(true);
		prevFrameButton->setTapHandler([=]{
			previousFrame();
		});
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.5, fgl::LAYOUTVALUE_RATIO);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		rOffsetY += 40;

		addMetapointButton = new fgl::ButtonElement();
		addMetapointButton->setBorderWidth(1);
		addMetapointButton->setTitle("Add Meta Point", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		addMetapointButton->getTitleElement()->setFontSize(14);
		addMetapointButton->setTapHandler([=]{
			beginUserAddMetaPoint();
		});
		rOffsetY += 16;
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;
		
		metapointCheckboxHeaderLabel = new fgl::TextElement();
		metapointCheckboxHeaderLabel->setFontSize(18);
		metapointCheckboxHeaderLabel->setText("Meta Points");
		metapointCheckboxHeaderLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		metapointCheckboxHeaderLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		rOffsetY += 16;
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;

		fgl::ArrayList<fl::AnimationMetaPoint::Type> metaPointTypes = {
			fl::AnimationMetaPoint::POINTTYPE_HITBOX,
			fl::AnimationMetaPoint::POINTTYPE_HEAD,
			fl::AnimationMetaPoint::POINTTYPE_LEFTHAND,
			fl::AnimationMetaPoint::POINTTYPE_RIGHTHAND,
			fl::AnimationMetaPoint::POINTTYPE_BOUNDS_TOPLEFT,
			fl::AnimationMetaPoint::POINTTYPE_BOUNDS_BOTTOMRIGHT,
			fl::AnimationMetaPoint::POINTTYPE_HANDLE
		};

		for(auto metaPointType : metaPointTypes)
		{
			auto metapointCheckbox = new LabeledCheckboxElement();
			metapointCheckbox->setText(MetaPointInfoElement::getMetaPointTypeName(metaPointType));
			metapointCheckbox->getLabelElement()->setFontSize(14);
			metapointCheckbox->setToggle(animationEditorElement->isMetaPointTypeVisible(metaPointType));
			metapointCheckbox->setToggleHandler([=](bool value){
				animationEditorElement->setMetaPointTypeVisible(metaPointType, value);
			});
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_LEFT, 4);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 26);

			metapointCheckboxElements[metaPointType] = metapointCheckbox;

			rOffsetY += 28;
		}

		rightSidebarContainer->addChildElement(frameIndexLabel);
		rightSidebarContainer->addChildElement(nextFrameButton);
		rightSidebarContainer->addChildElement(prevFrameButton);
		rightSidebarContainer->addChildElement(addMetapointButton);
		rightSidebarContainer->addChildElement(metapointCheckboxHeaderLabel);
		for(auto checkboxPair : metapointCheckboxElements)
		{
			rightSidebarContainer->addChildElement(checkboxPair.second);
		}
		
		//Left sidebar
		
		metaPointInfoElement = new MetaPointInfoElement(assetManager);
		metaPointInfoElement->setAnimationSize(animationData->getSize(animationEditorElement->getAnimationFrameIndex()));
		metaPointInfoElement->setMetaPointChangeHandler([=](fl::AnimationMetaPoint metaPoint) {
			if(selectedMetaPointFrameIndex!=-1 && selectedMetaPointIndex!=-1)
			{
				animationEditorElement->setMetaPoint(selectedMetaPointFrameIndex, selectedMetaPointIndex, metaPoint);
			}
		});
		
		getElement()->addChildElement(saveButtonElement);
		getElement()->addChildElement(nameInputElement);
		getElement()->addChildElement(leftSidebarContainer);
		getElement()->addChildElement(rightSidebarContainer);
		getElement()->addChildElement(animationEditorElement);
	}
	
	EditAnimationScreen::~EditAnimationScreen()
	{
		delete overlayElement;
		delete saveButtonElement;
		delete nameInputElement;
		delete animationEditorElement;
		delete leftSidebarContainer;
		delete rightSidebarContainer;
		delete frameIndexLabel;
		delete nextFrameButton;
		delete prevFrameButton;
		delete addMetapointButton;
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
				metaPointInfoElement->setAnimationSize(animationData->getSize(frameIndex));
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
				metaPointInfoElement->setAnimationSize(animationData->getSize(frameIndex));
			}
		}
	}

	void EditAnimationScreen::beginUserAddMetaPoint()
	{
		if(addingMetaPoint)
		{
			throw fgl::IllegalStateException("already adding meta point");
		}
		addingMetaPoint = true;
		size_t editorElementIndex = getElement()->getChildElements().indexOf(animationEditorElement);
		getElement()->addChildElement(editorElementIndex, overlayElement);
		animationEditorElement->beginUserAddMetaPoint([=](fl::AnimationMetaPoint metaPoint){
			overlayElement->removeFromParentElement();
			addingMetaPoint = false;
		});
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
