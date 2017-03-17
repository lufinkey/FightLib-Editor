
#pragma once

#include <fightlib/fightlib.hpp>
#include "CarouselSelectorElement.hpp"

namespace flui
{
	class MetaPointInfoElement : public fgl::ScreenElement
	{
	public:
		MetaPointInfoElement(fgl::AssetManager* assetManager);
		MetaPointInfoElement(fgl::AssetManager* assetManager, const fgl::RectangleD& frame);
		virtual ~MetaPointInfoElement();
		
		void setMetaPoint(const fl::AnimationMetaPoint& metaPoint);
		const fl::AnimationMetaPoint& getMetaPoint() const;

		static fgl::String getMetaPointTypeName(fl::AnimationMetaPoint::Type metaPointType);
		
	private:
		CarouselSelectorElement* typeSelectorElement;
		
		fl::AnimationMetaPoint metaPoint;
	};
}
