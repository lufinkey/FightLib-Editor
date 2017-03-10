
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
	getWindow()->getViewport()->setSize(800, 600);
}

void MainApplication::loadContent(fgl::AssetManager* assetManager)
{
	homeScreen = new flui::HomeScreen(assetManager);
	screenManager = new fgl::ScreenManager(getWindow(), homeScreen);
}

void MainApplication::unloadContent(fgl::AssetManager* assetManager)
{
	//
}

void MainApplication::update(fgl::ApplicationData appData)
{
	screenManager->update(appData);
}

void MainApplication::draw(fgl::ApplicationData appData, fgl::Graphics graphics) const
{
	screenManager->draw(appData, graphics);
}
