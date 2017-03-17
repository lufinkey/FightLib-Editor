
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

	private:
		fgl::ArrayList<fl::AnimationMetaPoint> metaPoints;
		fgl::ArrayList<MetaPointElement*> metaPointElements;
		std::function<void(size_t)> metaPointChangeHandler;
	};
}
