
#include "HomeScreen.hpp"

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
				}
				else
				{
					fgl::MessageBox::show(nullptr, "Error", error);
				}
			}
		});
		openAnimationButton->setBorderWidth(1);
		openAnimationButton->getTitleElement()->setTextAlignment(fgl::TEXTALIGN_CENTER);
		
		getElement()->addChildElement(openAnimationButton);
	}
	
	HomeScreen::~HomeScreen()
	{
		delete openAnimationButton;
	}
}
