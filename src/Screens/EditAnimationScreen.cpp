
#include "EditAnimationScreen.hpp"
#include "AddFramesScreen.hpp"

namespace flui
{
	EditAnimationScreen::EditAnimationScreen(fgl::AssetManager* assetManager, fl::AnimationData* animationData_arg, const fgl::String& savePath)
		: animationData(animationData_arg),
		savePath(savePath),
		lastSavedAnimationData(nullptr),
		selectedMetaPointFrameIndex(-1),
		selectedMetaPointIndex(-1),
		addingMetaPoint(false)
	{
		if(animationData==nullptr)
		{
			throw fgl::IllegalArgumentException("animationData", "cannot be null");
		}
		
		lastSavedAnimationData = new fl::AnimationData(*animationData);

		getElement()->setBackgroundColor(fgl::Color::WHITE);
		
		overlayElement = new fgl::TouchElement();
		overlayElement->setBackgroundColor(fgl::Color::BLACK);
		overlayElement->setAlpha(0.5);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
		overlayElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		
		// Close button
		closeButtonElement = new fgl::ButtonElement();
		closeButtonElement->setTitle("Close", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		closeButtonElement->getTitleElement()->setFontSize(14);
		closeButtonElement->setBorderWidth(1);
		closeButtonElement->setTapHandler([=]{
			closeScreen();
		});
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		closeButtonElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);

		// Save button
		saveButtonElement = new fgl::ButtonElement();
		saveButtonElement->setTitle("Save", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		saveButtonElement->getTitleElement()->setFontSize(14);
		saveButtonElement->setBorderWidth(1);
		saveButtonElement->setTapHandler([=]{
			saveAnimationData();
		});
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 60);
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		saveButtonElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);

		// Name input
		nameInputElement = new fgl::TextInputElement();
		nameInputElement->setText(animationData->getName());
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 110);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 168);
		nameInputElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		nameInputElement->setFontSize(24);
		nameInputElement->setResigningOnOutsideTouchEnabled(true);
		
		// Orientation selector
		orientationSelectorElement = new fgl::SegmentedSelectorElement();
		orientationSelectorElement->setFontSize(14);
		orientationSelectorElement->setItems({"Left", "Neutral", "Right"});
		switch(animationData->getOrientation())
		{
			case fl::ANIMATIONORIENTATION_LEFT:
				orientationSelectorElement->setSelectedItemIndex(0);
				break;
				
			case fl::ANIMATIONORIENTATION_NEUTRAL:
				orientationSelectorElement->setSelectedItemIndex(1);
				break;
				
			case fl::ANIMATIONORIENTATION_RIGHT:
				orientationSelectorElement->setSelectedItemIndex(2);
				break;
		}
		orientationSelectorElement->setSelectionHandler([=](size_t index){
			switch(index)
			{
				case 0:
					animationData->setOrientation(fl::ANIMATIONORIENTATION_LEFT);
					break;
					
				case 1:
					animationData->setOrientation(fl::ANIMATIONORIENTATION_NEUTRAL);
					break;
					
				case 2:
					animationData->setOrientation(fl::ANIMATIONORIENTATION_RIGHT);
					break;
			}
		});
		orientationSelectorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		orientationSelectorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		orientationSelectorElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 148);
		orientationSelectorElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);

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
		frameIndexLabel->setFontSize(18);
		frameIndexLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		frameIndexLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, rOffsetY+(24/2));
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;
		
		assetManager->loadTexture("assets/images/arrow_button.png");
		
		nextFrameButton = new fgl::ButtonElement();
		nextFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextFrameButton->setTapHandler([=] {
			nextFrame();
		});
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.5, fgl::LAYOUTVALUE_RATIO);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 24);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		
		prevFrameButton = new fgl::ButtonElement();
		prevFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevFrameButton->getImageElement()->setHorizontalImageMirroringEnabled(true);
		prevFrameButton->setTapHandler([=]{
			previousFrame();
		});
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.5, fgl::LAYOUTVALUE_RATIO);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 24);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;

		playToggleButton = new fgl::ButtonElement();
		playToggleButton->setBorderWidth(1);
		playToggleButton->setTitle("Play", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		playToggleButton->getTitleElement()->setFontSize(14);
		playToggleButton->setTapHandler([=]{
			if(animationEditorElement->getAnimationDirection() == fgl::Animation::STOPPED)
			{
				animationEditorElement->setAnimationDirection(fgl::Animation::FORWARD);
				playToggleButton->setTitle("Pause", fgl::ButtonElement::BUTTONSTATE_NORMAL);
			}
			else
			{
				animationEditorElement->setAnimationDirection(fgl::Animation::STOPPED);
				playToggleButton->setTitle("Play", fgl::ButtonElement::BUTTONSTATE_NORMAL);
			}
		});
		rOffsetY += 4;
		playToggleButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		playToggleButton->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		playToggleButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 60);
		playToggleButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;
		
		addFramesButton = new fgl::ButtonElement();
		addFramesButton->setBorderWidth(1);
		addFramesButton->setTitle("Add Frames", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		addFramesButton->getTitleElement()->setFontSize(14);
		addFramesButton->setTapHandler([=]{
			auto addFramesScreen = new AddFramesScreen(assetManager, animationData->getAnimation());
			presentScreen(addFramesScreen, nullptr, [=]{
				delete addFramesScreen;
				animationEditorElement->refresh();
			});
		});
		rOffsetY += 4;
		addFramesButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		addFramesButton->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		addFramesButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 100);
		addFramesButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;

		fpsLabel = new fgl::TextElement();
		fpsLabel->setText("FPS");
		fpsLabel->setFontSize(14);
		fpsLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		fpsLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		rOffsetY += 2;
		fpsLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		fpsLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		fpsLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 100);
		fpsLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 16);
		rOffsetY += 16;

		fpsAdjuster = new NumberAdjustElement(assetManager);
		fpsAdjuster->setMinValue(0.25);
		fpsAdjuster->setMaxValue(999);
		fpsAdjuster->setIncrement(0.25);
		fpsAdjuster->setValue(animationData->getAnimation()->getFPS());
		fpsAdjuster->setValueChangeHandler([=]{
			animationData->getAnimation()->setFPS(fpsAdjuster->getValue());
		});
		fpsAdjuster->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		fpsAdjuster->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		fpsAdjuster->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 60);
		fpsAdjuster->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;

		tracingFrameLabel = new fgl::TextElement();
		tracingFrameLabel->setText("Tracing Frame");
		tracingFrameLabel->setFontSize(18);
		tracingFrameLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		tracingFrameLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		rOffsetY += 10;
		tracingFrameLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		tracingFrameLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		tracingFrameLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		tracingFrameLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;

		tracingFrameCheckbox = new LabeledCheckboxElement();
		tracingFrameCheckbox->setText("visible");
		tracingFrameCheckbox->getLabelElement()->setFontSize(14);
		tracingFrameCheckbox->setToggle(animationEditorElement->isTracingAnimationVisible());
		tracingFrameCheckbox->setToggleHandler([=](bool value){
			animationEditorElement->setTracingAnimationVisible(value);
		});
		tracingFrameCheckbox->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		tracingFrameCheckbox->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		tracingFrameCheckbox->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 110);
		tracingFrameCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 18);
		rOffsetY += 18;

		tracingFrameIndexLabel = new fgl::TextElement();
		tracingFrameIndexLabel->setText(getTracingFrameIndexLabelString());
		tracingFrameIndexLabel->setFontSize(18);
		tracingFrameIndexLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		tracingFrameIndexLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		tracingFrameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		tracingFrameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, rOffsetY+(24/2));
		tracingFrameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		tracingFrameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;

		nextTracingFrameButton = new fgl::ButtonElement();
		nextTracingFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextTracingFrameButton->setTapHandler([=] {
			nextTracingFrame();
		});
		nextTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.5, fgl::LAYOUTVALUE_RATIO);
		nextTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		nextTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 24);
		nextTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);

		prevTracingFrameButton = new fgl::ButtonElement();
		prevTracingFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevTracingFrameButton->getImageElement()->setHorizontalImageMirroringEnabled(true);
		prevTracingFrameButton->setTapHandler([=] {
			previousTracingFrame();
		});
		prevTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.5, fgl::LAYOUTVALUE_RATIO);
		prevTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		prevTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 24);
		prevTracingFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;

		cloneMetaPointsButton = new fgl::ButtonElement();
		cloneMetaPointsButton->setTitle("Clone Meta Points", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		cloneMetaPointsButton->setBorderWidth(1);
		cloneMetaPointsButton->getTitleElement()->setFontSize(12);
		cloneMetaPointsButton->setTapHandler([=]{
			if(animationData->getAnimation()->getTotalFrames() > 0)
			{
				unsigned int choice = fgl::MessageBox::show(getWindow(), "Clone Meta Points", "This will overwrite any existing meta points for this frame. Continue?", {"Yes", "Cancel"});
				if(choice==0)
				{
					size_t tracingFrameIndex = animationEditorElement->getTracingAnimationFrameIndex();
					size_t frameIndex = animationEditorElement->getAnimationFrameIndex();
					animationEditorElement->setMetaPoints(frameIndex, animationEditorElement->getMetaPoints(tracingFrameIndex));
					if(leftSidebarContainer->getToolboxElement()==metaPointInfoElement)
					{
						leftSidebarContainer->setToolboxElement(nullptr);
					}
				}
			}
			else
			{
				fgl::MessageBox::show(getWindow(), "Error", "No frames have been added");
			}
		});
		rOffsetY += 4;
		cloneMetaPointsButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		cloneMetaPointsButton->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		cloneMetaPointsButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 110);
		cloneMetaPointsButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;
		
		metapointCheckboxHeaderLabel = new fgl::TextElement();
		metapointCheckboxHeaderLabel->setText("Meta Points");
		metapointCheckboxHeaderLabel->setFontSize(18);
		metapointCheckboxHeaderLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		metapointCheckboxHeaderLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		rOffsetY += 8;
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		metapointCheckboxHeaderLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 24);
		rOffsetY += 24;

		addMetapointButton = new fgl::ButtonElement();
		addMetapointButton->setBorderWidth(1);
		addMetapointButton->setTitle("Add Meta Point", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		addMetapointButton->getTitleElement()->setFontSize(14);
		addMetapointButton->setTapHandler([=]{
			if(animationData->getAnimation()->getTotalFrames() > 0)
			{
				beginUserAddMetaPoint();
			}
			else
			{
				fgl::MessageBox::show(getWindow(), "Error", "No frames have been added");
			}
		});
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 110);
		addMetapointButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;

		fgl::ArrayList<fl::MetaPointType> metaPointTypes = {
			fl::METAPOINT_HITBOX,
			fl::METAPOINT_HEAD,
			fl::METAPOINT_LEFTHAND,
			fl::METAPOINT_RIGHTHAND,
			fl::METAPOINT_BOUNDS_TOPLEFT,
			fl::METAPOINT_BOUNDS_BOTTOMRIGHT,
			fl::METAPOINT_HANDLE
		};

		rOffsetY += 5;
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
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 110);
			metapointCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 18);

			metapointCheckboxElements[metaPointType] = metapointCheckbox;

			rOffsetY += 20;
		}

		showBoundsCheckbox = new LabeledCheckboxElement();
		showBoundsCheckbox->setText("Show Bounds");
		showBoundsCheckbox->getLabelElement()->setFontSize(14);
		showBoundsCheckbox->setToggle(animationEditorElement->isBoundsDrawingEnabled());
		showBoundsCheckbox->setToggleHandler([=](bool value){
			animationEditorElement->setBoundsDrawingEnabled(value);
		});
		rOffsetY += 10;
		showBoundsCheckbox->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		showBoundsCheckbox->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		showBoundsCheckbox->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 110);
		showBoundsCheckbox->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 26);
		rOffsetY += 26;

		anchorSizeLabel = new fgl::TextElement();
		anchorSizeLabel->setText("Anchor Size");
		anchorSizeLabel->setFontSize(14);
		anchorSizeLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		anchorSizeLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		rOffsetY += 4;
		anchorSizeLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		anchorSizeLabel->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		anchorSizeLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
		anchorSizeLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 18);
		rOffsetY += 18;

		anchorSizeAdjuster = new NumberAdjustElement(assetManager);
		anchorSizeAdjuster->setMinValue(1.0);
		anchorSizeAdjuster->setMaxValue(10.0);
		anchorSizeAdjuster->setIncrement(1.0);
		anchorSizeAdjuster->setValue(animationEditorElement->getMetaPointAnchorSize());
		anchorSizeAdjuster->setValueChangeHandler([=] {
			animationEditorElement->setMetaPointAnchorSize(anchorSizeAdjuster->getValue().toArithmeticValue<double>());
		});
		rOffsetY += 2;
		anchorSizeAdjuster->setLayoutRule(fgl::LAYOUTRULE_TOP, rOffsetY);
		anchorSizeAdjuster->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		anchorSizeAdjuster->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 60);
		anchorSizeAdjuster->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 20);
		rOffsetY += 20;

		rightSidebarContainer->addChildElement(frameIndexLabel);
		rightSidebarContainer->addChildElement(nextFrameButton);
		rightSidebarContainer->addChildElement(prevFrameButton);
		rightSidebarContainer->addChildElement(playToggleButton);
		rightSidebarContainer->addChildElement(addFramesButton);
		rightSidebarContainer->addChildElement(fpsLabel);
		rightSidebarContainer->addChildElement(fpsAdjuster);
		rightSidebarContainer->addChildElement(tracingFrameLabel);
		rightSidebarContainer->addChildElement(tracingFrameCheckbox);
		rightSidebarContainer->addChildElement(tracingFrameIndexLabel);
		rightSidebarContainer->addChildElement(nextTracingFrameButton);
		rightSidebarContainer->addChildElement(prevTracingFrameButton);
		rightSidebarContainer->addChildElement(cloneMetaPointsButton);
		rightSidebarContainer->addChildElement(metapointCheckboxHeaderLabel);
		rightSidebarContainer->addChildElement(addMetapointButton);
		for(auto checkboxPair : metapointCheckboxElements)
		{
			rightSidebarContainer->addChildElement(checkboxPair.second);
		}
		rightSidebarContainer->addChildElement(showBoundsCheckbox);
		rightSidebarContainer->addChildElement(anchorSizeLabel);
		rightSidebarContainer->addChildElement(anchorSizeAdjuster);
		
		//Left sidebar
		
		metaPointInfoElement = new MetaPointInfoElement(assetManager);
		if(animationData->getAnimation()->getTotalFrames())
		{
			metaPointInfoElement->setAnimationSize(animationData->getSize(animationEditorElement->getAnimationFrameIndex()));
		}
		metaPointInfoElement->setMetaPointChangeHandler([=](fl::AnimationMetaPoint metaPoint) {
			if(selectedMetaPointFrameIndex!=-1 && selectedMetaPointIndex!=-1)
			{
				animationEditorElement->setMetaPoint(selectedMetaPointFrameIndex, selectedMetaPointIndex, metaPoint);
			}
		});
		metaPointInfoElement->setMetaPointDeleteHandler([=]{
			if(selectedMetaPointFrameIndex!=-1 && selectedMetaPointIndex!=-1)
			{
				animationEditorElement->removeMetaPoint(selectedMetaPointFrameIndex, selectedMetaPointIndex);
				leftSidebarContainer->setToolboxElement(nullptr);
				selectedMetaPointFrameIndex = -1;
				selectedMetaPointIndex = -1;
			}
		});
		
		getElement()->addChildElement(closeButtonElement);
		getElement()->addChildElement(saveButtonElement);
		getElement()->addChildElement(nameInputElement);
		getElement()->addChildElement(orientationSelectorElement);
		getElement()->addChildElement(leftSidebarContainer);
		getElement()->addChildElement(rightSidebarContainer);
		getElement()->addChildElement(animationEditorElement);
	}
	
	EditAnimationScreen::~EditAnimationScreen()
	{
		delete lastSavedAnimationData;
		
		delete overlayElement;
		delete closeButtonElement;
		delete saveButtonElement;
		delete nameInputElement;
		delete orientationSelectorElement;
		delete animationEditorElement;
		delete leftSidebarContainer;
		delete rightSidebarContainer;
		delete frameIndexLabel;
		delete nextFrameButton;
		delete prevFrameButton;
		delete playToggleButton;
		delete addFramesButton;
		delete fpsLabel;
		delete fpsAdjuster;
		delete tracingFrameLabel;
		delete tracingFrameCheckbox;
		delete tracingFrameIndexLabel;
		delete nextTracingFrameButton;
		delete prevTracingFrameButton;
		delete cloneMetaPointsButton;
		delete metapointCheckboxHeaderLabel;
		delete addMetapointButton;
		delete metaPointInfoElement;
		for(auto checkboxPair : metapointCheckboxElements)
		{
			delete checkboxPair.second;
		}
		delete showBoundsCheckbox;
		delete anchorSizeLabel;
		delete anchorSizeAdjuster;
	}
	
	void EditAnimationScreen::update(fgl::ApplicationData appData)
	{
		Screen::update(appData);
		frameIndexLabel->setText(getFrameIndexLabelString());
		tracingFrameIndexLabel->setText(getTracingFrameIndexLabelString());
		animationData->setName(nameInputElement->getText());
	}
	
	bool EditAnimationScreen::saveAnimationData()
	{
		fgl::String error;
		bool success = animationData->saveToFile(savePath, &error);
		if(success)
		{
			delete lastSavedAnimationData;
			lastSavedAnimationData = new fl::AnimationData(*animationData);
		}
		else
		{
			fgl::MessageBox::show(getWindow(), "Error", error);
		}
		return success;
	}
	
	bool EditAnimationScreen::closeScreen()
	{
		if(*animationData != *lastSavedAnimationData)
		{
			auto selection = fgl::MessageBox::show(getWindow(), "Unsaved Changes", "Would you like to save your changes?", {"Yes", "No", "Cancel"});
			if(selection==0)
			{
				if(!saveAnimationData())
				{
					return false;
				}
			}
			else if(selection==2)
			{
				return false;
			}
		}
		if(getPresentingScreen()==nullptr)
		{
			return false;
		}
		getPresentingScreen()->dismissPresentedScreen();
		return true;
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

	void EditAnimationScreen::nextTracingFrame()
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation!=nullptr || animation->getTotalFrames() > 0)
		{
			size_t frameIndex = animationEditorElement->getTracingAnimationFrameIndex();
			size_t frameCount = animation->getTotalFrames();
			frameIndex++;
			if(frameIndex < frameCount)
			{
				animationEditorElement->setTracingAnimationFrameIndex(frameIndex);
			}
		}
	}

	void EditAnimationScreen::previousTracingFrame()
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation!=nullptr || animation->getTotalFrames() > 0)
		{
			size_t frameIndex = animationEditorElement->getTracingAnimationFrameIndex();
			frameIndex--;
			if(frameIndex != -1)
			{
				animationEditorElement->setTracingAnimationFrameIndex(frameIndex);
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

	fgl::String EditAnimationScreen::getTracingFrameIndexLabelString() const
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation==nullptr || animation->getTotalFrames()==0)
		{
			return "0/0";
		}
		size_t frameIndex = animationEditorElement->getTracingAnimationFrameIndex();
		size_t frameCount = animation->getTotalFrames();
		return (fgl::String)""+(frameIndex+1)+"/"+frameCount;
	}
}
