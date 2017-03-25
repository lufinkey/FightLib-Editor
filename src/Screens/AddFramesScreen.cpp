
#include "AddFramesScreen.hpp"

namespace flui
{
	AddFramesScreen::AddFramesScreen(fgl::AssetManager* assetManager_arg, fgl::Animation* animation_arg)
		: PopupScreen(new fgl::ScreenElement(fgl::RectangleD(0,0,100,100))),
		assetManager(assetManager_arg->getWindow(), assetManager_arg->getRootDirectory())
	{
		auto containerElement = getPopupElement();
		containerElement->setBackgroundColor(fgl::Color::WHITE);
		containerElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 0.8, fgl::LAYOUTVALUE_RATIO);
		containerElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 0.8, fgl::LAYOUTVALUE_RATIO);
		
		double offsetY = 10;
		
		browseButton = new fgl::ButtonElement();
		browseButton->setBorderWidth(1);
		browseButton->setBackgroundColor(fgl::Color::LIGHTGRAY, fgl::ButtonElement::BUTTONSTATE_NORMAL);
		browseButton->setTitle("Browse", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		browseButton->setTapHandler([=]{
			fgl::String imagePath = fgl::FileTools::openFilePicker("Select an image");
			if(imagePath.length()>0)
			{
				fgl::AssetManager newAssetManager(assetManager.getWindow(), assetManager.getRootDirectory());
				fgl::Animation newEditingAnimation;
				fgl::String error;
				unsigned int rows = rowsAdjuster->getValue();
				unsigned int cols = columnsAdjuster->getValue();
				if(newEditingAnimation.addFrames(&newAssetManager, imagePath, rows, cols, &error))
				{
					assetManager.unload();
					assetManager.moveAssetsFrom(newAssetManager);
					editingAnimation = newEditingAnimation;
					animationElement->setAnimationFrameIndex(0);
					filePathElement->setText(imagePath);

					fgl::TextureImage* image = assetManager.getTexture(imagePath);
					double frameWidth = (double)image->getWidth() / (double)cols;
					double frameHeight = (double)image->getHeight() / (double)rows;
					animationElement->setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, frameWidth/frameHeight);
					getPopupElement()->layoutChildElements();
				}
				else
				{
					fgl::MessageBox::show(getWindow(), "Error", error);
				}
			}
		});
		browseButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 100);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		
		filePathElement = new fgl::TextElement();
		filePathElement->setBorderWidth(1);
		filePathElement->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 120);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		offsetY += 50;

		rowsLabel = new fgl::TextElement();
		rowsLabel->setText("Rows");
		rowsLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		rowsLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		rowsLabel->setFontSize(16);
		rowsLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.35, fgl::LAYOUTVALUE_RATIO);
		rowsLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, offsetY+9);
		rowsLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 60);
		rowsLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 18);

		columnsLabel = new fgl::TextElement();
		columnsLabel->setText("Columns");
		columnsLabel->setTextAlignment(fgl::TEXTALIGN_CENTER);
		columnsLabel->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
		columnsLabel->setFontSize(16);
		columnsLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.65, fgl::LAYOUTVALUE_RATIO);
		columnsLabel->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, offsetY+9);
		columnsLabel->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 60);
		columnsLabel->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 18);
		offsetY += 18;

		rowsAdjuster = new NumberAdjustElement(assetManager_arg);
		rowsAdjuster->setMinValue(1);
		rowsAdjuster->setMaxValue(9999);
		rowsAdjuster->setIncrement(1);
		rowsAdjuster->setValue(1);
		rowsAdjuster->setValueChangeHandler([=]{
			auto& imagePath = filePathElement->getText();
			if(imagePath.length() > 0)
			{
				unsigned int rows = rowsAdjuster->getValue();
				unsigned int cols = columnsAdjuster->getValue();

				editingAnimation.removeAllFrames();
				editingAnimation.addFrames(&assetManager, filePathElement->getText(), rowsAdjuster->getValue(), columnsAdjuster->getValue());

				fgl::TextureImage* image = assetManager.getTexture(imagePath);
				double frameWidth = (double)image->getWidth() / (double)cols;
				double frameHeight = (double)image->getHeight() / (double)rows;
				animationElement->setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, frameWidth/frameHeight);
				getPopupElement()->layoutChildElements();
			}
		});
		rowsAdjuster->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.35, fgl::LAYOUTVALUE_RATIO);
		rowsAdjuster->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, offsetY+16);
		rowsAdjuster->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		rowsAdjuster->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);

		columnsAdjuster = new NumberAdjustElement(assetManager_arg);
		columnsAdjuster->setMinValue(1);
		columnsAdjuster->setMaxValue(9999);
		columnsAdjuster->setIncrement(1);
		columnsAdjuster->setValue(1);
		columnsAdjuster->setValueChangeHandler([=]{
			auto& imagePath = filePathElement->getText();
			if(imagePath.length() > 0)
			{
				unsigned int rows = rowsAdjuster->getValue();
				unsigned int cols = columnsAdjuster->getValue();

				editingAnimation.removeAllFrames();
				editingAnimation.addFrames(&assetManager, filePathElement->getText(), rowsAdjuster->getValue(), columnsAdjuster->getValue());

				fgl::TextureImage* image = assetManager.getTexture(imagePath);
				double frameWidth = (double)image->getWidth() / (double)cols;
				double frameHeight = (double)image->getHeight() / (double)rows;
				animationElement->setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, frameWidth/frameHeight);
				getPopupElement()->layoutChildElements();
			}
		});
		columnsAdjuster->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.65, fgl::LAYOUTVALUE_RATIO);
		columnsAdjuster->setLayoutRule(fgl::LAYOUTRULE_CENTER_Y, offsetY+16);
		columnsAdjuster->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 80);
		columnsAdjuster->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		offsetY+=32;

		animationElement = new fgl::AnimationElement(&editingAnimation, fgl::Animation::STOPPED);
		animationElement->setBorderWidth(1);
		offsetY += 20;
		animationElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		animationElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 20);
		animationElement->setLayoutRule(fgl::LAYOUTRULE_CENTER_X, 0.5, fgl::LAYOUTVALUE_RATIO);
		animationElement->setLayoutRule(fgl::LAYOUTRULE_ASPECTRATIO, 1.0);
		
		containerElement->addChildElement(browseButton);
		containerElement->addChildElement(filePathElement);
		containerElement->addChildElement(rowsLabel);
		containerElement->addChildElement(columnsLabel);
		containerElement->addChildElement(rowsAdjuster);
		containerElement->addChildElement(columnsAdjuster);
		containerElement->addChildElement(animationElement);
	}
	
	AddFramesScreen::~AddFramesScreen()
	{
		delete browseButton;
		delete filePathElement;
		delete rowsLabel;
		delete columnsLabel;
		delete rowsAdjuster;
		delete columnsAdjuster;
		delete animationElement;
	}
}
