
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

		void nextTracingFrame();
		void previousTracingFrame();

		void beginUserAddMetaPoint();
		
	private:
		fgl::String getFrameIndexLabelString() const;
		fgl::String getTracingFrameIndexLabelString() const;
		
		fl::AnimationData* animationData;
		fgl::String savePath;
		
		fl::AnimationData* lastSavedAnimationData;

		fgl::TouchElement* overlayElement;

		//header area
		fgl::ButtonElement* closeButtonElement;
		fgl::ButtonElement* saveButtonElement;
		fgl::TextInputElement* nameInputElement;
		fgl::SegmentedSelectorElement* orientationSelectorElement;

		flui::AnimationEditorElement* animationEditorElement;
		
		ToolboxContainerElement* leftSidebarContainer;
		fgl::ScreenElement* rightSidebarContainer;

		//right sidebar - frame changer
		fgl::TextElement* frameIndexLabel;
		fgl::ButtonElement* nextFrameButton;
		fgl::ButtonElement* prevFrameButton;
		fgl::ButtonElement* playToggleButton;
		fgl::ButtonElement* addFramesButton;
		//right sidebar - tracing frame
		fgl::TextElement* tracingFrameLabel;
		LabeledCheckboxElement* tracingFrameCheckbox;
		fgl::TextElement* tracingFrameIndexLabel;
		fgl::ButtonElement* nextTracingFrameButton;
		fgl::ButtonElement* prevTracingFrameButton;
		fgl::ButtonElement* cloneMetaPointsButton;
		//right sidebar - metapoint checkboxes
		fgl::TextElement* metapointCheckboxHeaderLabel;
		fgl::ButtonElement* addMetapointButton;
		fgl::BasicDictionary<fl::AnimationMetaPoint::Type, LabeledCheckboxElement*> metapointCheckboxElements;
		LabeledCheckboxElement* showBoundsCheckbox;
		
		//left sidebar
		MetaPointInfoElement* metaPointInfoElement;

		size_t selectedMetaPointFrameIndex;
		size_t selectedMetaPointIndex;
		bool addingMetaPoint;
	};
}
