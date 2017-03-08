
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace flui
{
	class CheckerboardElement : public fgl::ScreenElement
	{
	public:
		CheckerboardElement();
		CheckerboardElement(const fgl::RectangleD&frame);
			
		void setBlockSize(double size);
		void setFirstBlockColor(const fgl::Color&color);
		void setSecondBlockColor(const fgl::Color&color);
			
		double getBlockSize() const;
		const fgl::Color& getFirstBlockColor() const;
		const fgl::Color& getSecondBlockColor() const;
			
	protected:
		/*! \copydoc fgl::ScreenElement::drawMain(fgl::ApplicationData,fgl::Graphics)const*/
		virtual void drawMain(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
			
	private:
		double blockSize;
		fgl::Color block1Color;
		fgl::Color block2Color;
	};
}
