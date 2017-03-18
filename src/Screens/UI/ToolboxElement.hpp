
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace flui
{
	class ToolboxElement : public fgl::ScreenElement
	{
	public:
		using ScreenElement::ScreenElement;

		virtual fgl::String getTitle() const;

		virtual void onClose();
	};
}
