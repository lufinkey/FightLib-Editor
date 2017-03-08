
#include "MainApplication.hpp"

MainApplication::MainApplication()
{
	//
}

MainApplication::~MainApplication()
{
	//
}

void MainApplication::initialize()
{
	getWindow()->setTitle("MobileBrawler Character Editor");
	getWindow()->setSize(fgl::Vector2u(800,600));

	textInputElement = new fgl::TextInputElement(fgl::RectangleD(100, 100, 200, 40));
	animationElement = new flui::AnimationEditorElement(fgl::RectangleD(100, 240, 100, 100));
	animationElement->setBorderWidth(-1);

	screen = new fgl::Screen(getWindow());
	screen->getElement()->addChildElement(textInputElement);
	screen->getElement()->addChildElement(animationElement);
}

void MainApplication::loadContent(fgl::AssetManager* assetManager)
{
	animData = new fl::AnimationData();
	animData->loadFromFile("external/FightLib/test/assets/animations/idle.plist", assetManager);
	animationElement->setAnimationData(animData);
}

void MainApplication::unloadContent(fgl::AssetManager* assetManager)
{
	//
}

void MainApplication::update(fgl::ApplicationData appData)
{
	screen->update(appData);
}

void MainApplication::draw(fgl::ApplicationData appData, fgl::Graphics graphics) const
{
	screen->draw(appData, graphics);
}
