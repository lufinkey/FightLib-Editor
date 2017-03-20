
#include "HomeScreen.hpp"
#include "EditAnimationScreen.hpp"

namespace flui
{
	HomeScreen::HomeScreen(fgl::AssetManager* assetManager)
	{
		openAnimationButton = new fgl::ButtonElement(fgl::RectangleD(0,0,0,0), "Open Animation", [=]{
			fgl::String animationPath = fgl::FileTools::openFilePicker("Open","",true,"plist");
			if(animationPath.length() > 0)
			{
				fl::AnimationData* animData = new fl::AnimationData();
				fgl::String error;
				if(animData->loadFromFile(animationPath, assetManager, &error))
				{
					//TODO delete this animation sometime
					EditAnimationScreen* editScreen = new EditAnimationScreen(assetManager, animData, animationPath);
					editScreen->setCloseHandler([=]{
						delete editScreen;
						delete animData;
					});
					presentChildScreen(editScreen);
				}
				else
				{
					delete animData;
					fgl::MessageBox::show(getWindow(), "Error", error);
				}
			}
		});
		openAnimationButton->setBorderWidth(1);
		
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 10);
		openAnimationButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.51, fgl::LAYOUTVALUE_RATIO);

		newAnimationButton = new fgl::ButtonElement(fgl::RectangleD(0, 0, 0, 0), "New Animation", [=] {
			fgl::String animationPath = fgl::FileTools::openFilePicker("Save","",false,"plist");
			if(animationPath.length() > 0)
			{
				fl::AnimationData* animData = new fl::AnimationData();
				animData->setName("Untitled");
				fgl::String error;
				if(animData->saveToFile(animationPath, &error))
				{
					//TODO delete this animation sometime
					EditAnimationScreen* editScreen = new EditAnimationScreen(assetManager, animData, animationPath);
					editScreen->setCloseHandler([=]{
						delete editScreen;
						delete animData;
					});
					presentChildScreen(editScreen);
				}
				else
				{
					delete animData;
					fgl::MessageBox::show(getWindow(), "Error", error);
				}
			}
		});
		newAnimationButton->setBorderWidth(1);

		newAnimationButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		newAnimationButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		newAnimationButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.51, fgl::LAYOUTVALUE_RATIO);
		newAnimationButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 10);
		
		getElement()->addChildElement(openAnimationButton);
		getElement()->addChildElement(newAnimationButton);
	}
	
	HomeScreen::~HomeScreen()
	{
		delete openAnimationButton;
		delete newAnimationButton;
	}
}
