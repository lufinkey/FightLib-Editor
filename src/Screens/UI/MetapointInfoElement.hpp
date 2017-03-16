
#pragma once

#include <fightlib/fightlib.hpp>
#include "CarouselSelectorElement.hpp"

namespace flui
{
	class MetapointInfoElement : public fgl::ScreenElement
	{
	public:
		MetapointInfoElement(fgl::AssetManager* assetManager);
		MetapointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame);
		virtual ~MetapointInfoElement();
		
		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;
		
	private:
		CarouselSelectorElement* typeSelectorElement;
		
		fl::AnimationMetaPoint metaPoint;
	};
}
