
#include <GameLibrary/GameLibrary.hpp>

namespace flui
{
	class AddFramesScreen : public fgl::PopupScreen
	{
	public:
		AddFramesScreen(fgl::Animation* animation);
		virtual ~AddFramesScreen();
		
	private:
		fgl::ButtonElement* browseButton;
		fgl::TextElement* filePathElement;
		
		fgl::TextElement* rowsLabel;
		fgl::TextInputElement* rowsInputElement;
		fgl::TextElement* columnsLabel;
		fgl::TextInputElement* columnsInputElement;
		//TODO have a re-arrangeable list of the frames in the animation so sequencing works
	};
}
