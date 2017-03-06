
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

	screen = new fgl::Screen(getWindow());
	screen->getElement()->addChildElement(textInputElement);
}

void MainApplication::loadContent(fgl::AssetManager*assetManager)
{
	//
}

void MainApplication::unloadContent(fgl::AssetManager*assetManager)
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
