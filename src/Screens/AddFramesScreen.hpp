
#include <GameLibrary/GameLibrary.hpp>
#include "UI/NumberAdjustElement.hpp"

namespace flui
{
	class AddFramesScreen : public fgl::PopupScreen
	{
	public:
		AddFramesScreen(fgl::AssetManager* assetManager, fgl::Animation* animation);
		virtual ~AddFramesScreen();
		
	private:
		void updateAnimation();

		fgl::AssetManager assetManager;
		fgl::Animation editingAnimation;
		fgl::Animation* animation;

		fgl::ButtonElement* browseButton;
		fgl::TextElement* filePathElement;
		
		fgl::TextElement* rowsLabel;
		NumberAdjustElement* rowsAdjuster;
		fgl::TextElement* columnsLabel;
		NumberAdjustElement* columnsAdjuster;

		fgl::AnimationElement* animationElement;

		NumberAdjustElement* frameAdjuster;

		//TODO have a re-arrangeable list of the frames in the animation so sequencing works
	};
}
