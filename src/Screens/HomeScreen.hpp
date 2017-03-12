
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include <fightlib/fightlib.hpp>

namespace flui
{
	class HomeScreen : public fgl::Screen
	{
	public:
		HomeScreen(fgl::AssetManager* assetManager);
		virtual ~HomeScreen();
		
	private:
		fgl::ButtonElement* openAnimationButton;
		fgl::ButtonElement* newAnimationButton;
	};
}
