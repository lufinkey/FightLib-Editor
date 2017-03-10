
#include "EditAnimationScreen.hpp"

namespace flui
{
	EditAnimationScreen::EditAnimationScreen(fl::AnimationData* animationData_arg)
		: animationData(animationData_arg)
	{
		animationEditorElement = new AnimationEditorElement(fgl::RectangleD(100,100,100,100));
		animationEditorElement->setAnimationData(animationData);
		animationEditorElement->setAnimationFrame(4);
		
		getElement()->addChildElement(animationEditorElement);
	}
}
