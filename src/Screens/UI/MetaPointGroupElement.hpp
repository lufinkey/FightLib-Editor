
#pragma once

#include "MetaPointElement.hpp"

namespace flui
{
	class MetaPointGroupElement : public fgl::ScreenElement
	{
	public:
		using ScreenElement::ScreenElement;
		virtual ~MetaPointGroupElement();

		void setMetaPoints(const fgl::ArrayList<fl::AnimationMetaPoint>& metaPoints);
		const fgl::ArrayList<fl::AnimationMetaPoint>& getMetaPoints() const;

		void setMetaPointChangeHandler(const std::function<void(size_t index)>& handler);
		const std::function<void(size_t)>& getMetaPointChangeHandler() const;

		void setMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType, bool visible);
		bool isMetaPointTypeVisible(fl::AnimationMetaPoint::Type metaPointType) const;

	private:
		fgl::ArrayList<fl::AnimationMetaPoint> metaPoints;
		fgl::ArrayList<MetaPointElement*> metaPointElements;
		std::function<void(size_t)> metaPointChangeHandler;
		fgl::BasicDictionary<fl::AnimationMetaPoint::Type, bool> enabledMetaPointTypes;
	};
}
