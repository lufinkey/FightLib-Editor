
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
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 100);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 100);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 52);
		animationEditorElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 10);
		
		frameIndexLabel = new fgl::TextElement();
		frameIndexLabel->setText(getFrameIndexLabelString());
		frameIndexLabel->setFontSize(24);
		frameIndexLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		frameIndexLabel->setVerticalAlignment(fgl::VERTICALALIGN_CENTER);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_TOP, 62);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		frameIndexLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		
		assetManager->loadTexture("assets/images/arrow_button.png");
		
		nextFrameButton = new fgl::ButtonElement();
		nextFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 102);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		nextFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		nextFrameButton->setHandler([=]{
			nextFrame();
		});
		
		prevFrameButton = new fgl::ButtonElement();
		prevFrameButton->setImage(assetManager->getTexture("assets/images/arrow_button.png"), fgl::ButtonElement::BUTTONSTATE_NORMAL);
		prevFrameButton->getImageElement()->setHorizontalMirroringEnabled(true);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 50);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 102);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 40);
		prevFrameButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 40);
		prevFrameButton->setHandler([=]{
			previousFrame();
		});
		
		metaPointInfoElement = new MetapointInfoElement(assetManager);
		metaPointInfoElement->setVisible(false);
		metaPointInfoElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
		metaPointInfoElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 52);
		metaPointInfoElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 100);
		metaPointInfoElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
		
		getElement()->addChildElement(animationEditorElement);
		getElement()->addChildElement(nameInputElement);
		getElement()->addChildElement(frameIndexLabel);
		getElement()->addChildElement(nextFrameButton);
		getElement()->addChildElement(prevFrameButton);
		getElement()->addChildElement(metaPointInfoElement);
	}
	
	EditAnimationScreen::~EditAnimationScreen()
	{
		delete nameInputElement;
		delete animationEditorElement;
		delete frameIndexLabel;
		delete nextFrameButton;
		delete prevFrameButton;
		delete metaPointInfoElement;
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
			size_t frameIndex = animationEditorElement->getAnimationFrame();
			size_t frameCount = animation->getTotalFrames();
			frameIndex++;
			if(frameIndex < frameCount)
			{
				animationEditorElement->setAnimationFrame(frameIndex);
			}
		}
	}
	
	void EditAnimationScreen::previousFrame()
	{
		fgl::Animation* animation = animationData->getAnimation();
		if(animation!=nullptr || animation->getTotalFrames() > 0)
		{
			size_t frameIndex = animationEditorElement->getAnimationFrame();
			frameIndex--;
			if(frameIndex != -1)
			{
				animationEditorElement->setAnimationFrame(frameIndex);
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
		size_t frameIndex = animationEditorElement->getAnimationFrame();
		size_t frameCount = animation->getTotalFrames();
		return (fgl::String)""+(frameIndex+1)+"/"+frameCount;
	}
}
