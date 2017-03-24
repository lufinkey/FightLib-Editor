
#include "AddFramesScreen.hpp"

namespace flui
{
	AddFramesScreen::AddFramesScreen(fgl::Animation* animation) : PopupScreen(new fgl::ScreenElement(fgl::RectangleD(0,0,100,100)))
	{
		auto containerElement = getPopupElement();
		containerElement->setBackgroundColor(fgl::Color::WHITE);
		containerElement->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 0.8, fgl::LAYOUTVALUE_RATIO);
		containerElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 0.6, fgl::LAYOUTVALUE_RATIO);
		
		double offsetY = 10;
		
		browseButton = new fgl::ButtonElement();
		browseButton->setBorderWidth(1);
		browseButton->setBackgroundColor(fgl::Color::LIGHTGRAY, fgl::ButtonElement::BUTTONSTATE_NORMAL);
		browseButton->setTitle("Browse", fgl::ButtonElement::BUTTONSTATE_NORMAL);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 10);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 100);
		browseButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		
		filePathElement = new fgl::TextElement();
		filePathElement->setBorderWidth(1);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 120);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_TOP, offsetY);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 10);
		filePathElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 32);
		offsetY += 50;
		
		containerElement->addChildElement(browseButton);
		containerElement->addChildElement(filePathElement);
	}
	
	AddFramesScreen::~AddFramesScreen()
	{
		delete browseButton;
		delete filePathElement;
	}
}
