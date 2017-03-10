
#include "HomeScreen.hpp"
#include "EditAnimationScreen.hpp"

namespace flui
{
	HomeScreen::HomeScreen(fgl::AssetManager* assetManager)
	{
		openAnimationButton = new fgl::ButtonElement(fgl::RectangleD(20,20,200,40), "Open Animation", [=]{
			fgl::String animationPath = fgl::FileTools::openFilePicker();
			if(animationPath.length() > 0)
			{
				fl::AnimationData* animData = new fl::AnimationData();
				fgl::String error;
				if(animData->loadFromFile(animationPath, assetManager, &error))
				{
					//TODO push the animation editor screen
					EditAnimationScreen* editScreen = new EditAnimationScreen(animData);
					present(editScreen);
				}
				else
				{
					delete animData;
					fgl::MessageBox::show(nullptr, "Error", error);
				}
			}
		});
		openAnimationButton->setBorderWidth(1);
		openAnimationButton->getTitleElement()->setTextAlignment(fgl::TEXTALIGN_CENTER);
		
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 20);
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 15);
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 40);
		
		getElement()->addChildElement(openAnimationButton);
	}
	
	HomeScreen::~HomeScreen()
	{
		delete openAnimationButton;
	}
}
