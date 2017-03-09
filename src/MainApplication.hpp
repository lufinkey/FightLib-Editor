
#pragma once

#include <fightlib/fightlib.hpp>
#include <GameLibrary/Screen/UI/TextElement.hpp>
#include "UI/AnimationEditorElement.hpp"

class MainApplication : public fgl::Application
{
public:
	MainApplication();
	virtual ~MainApplication();

	virtual void initialize() override;
	virtual void loadContent(fgl::AssetManager* assetManager) override;
	virtual void unloadContent(fgl::AssetManager* assetManager) override;
	virtual void update(fgl::ApplicationData appData) override;
	virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;

private:
	fl::AnimationData* animData;
	fgl::Screen* screen;
	fgl::TextInputElement* textInputElement;
	flui::AnimationEditorElement* animationElement;
};
