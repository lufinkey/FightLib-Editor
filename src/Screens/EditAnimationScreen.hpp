
#pragma once

#include <fightlib/fightlib.hpp>
#include "UI/AnimationEditorElement.hpp"
#include "UI/MetaPointInfoElement.hpp"
#include "UI/LabeledCheckboxElement.hpp"
#include "UI/ToolboxContainerElement.hpp"

namespace flui
{
	class EditAnimationScreen : public fgl::Screen
	{
	public:
		EditAnimationScreen(fgl::AssetManager* assetManager, fl::AnimationData* animationData, const fgl::String& savePath);
		virtual ~EditAnimationScreen();
		
		virtual void update(fgl::ApplicationData appData) override;
		
		bool saveAnimationData();
		bool closeScreen();
		
		void nextFrame();
		void previousFrame();

		void beginUserAddMetaPoint();
		
	private:
		fgl::String getFrameIndexLabelString() const;
		
		fl::AnimationData* animationData;
		fgl::String savePath;
		
		fl::AnimationData* lastSavedAnimationData;

		fgl::TouchElement* overlayElement;

		//header area
		fgl::ButtonElement* closeButtonElement;
		fgl::ButtonElement* saveButtonElement;
		fgl::TextInputElement* nameInputElement;

		flui::AnimationEditorElement* animationEditorElement;
		
		ToolboxContainerElement* leftSidebarContainer;
		fgl::ScreenElement* rightSidebarContainer;

		//right sidebar
		fgl::TextElement* frameIndexLabel;
		fgl::ButtonElement* nextFrameButton;
		fgl::ButtonElement* prevFrameButton;
		fgl::ButtonElement* addMetapointButton;
		fgl::TextElement* metapointCheckboxHeaderLabel;
		fgl::BasicDictionary<fl::AnimationMetaPoint::Type, LabeledCheckboxElement*> metapointCheckboxElements;
		
		//left sidebar
		MetaPointInfoElement* metaPointInfoElement;

		size_t selectedMetaPointFrameIndex;
		size_t selectedMetaPointIndex;
		bool addingMetaPoint;
	};
}
