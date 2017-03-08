
#include "CheckerboardElement.hpp"

using namespace fgl;

namespace flui
{
	CheckerboardElement::CheckerboardElement() : CheckerboardElement(RectangleD(0,0,0,0))
	{
		//
	}
		
	CheckerboardElement::CheckerboardElement(const RectangleD& frame)
		: ScreenElement(frame), blockSize(8), block1Color(0,0,0), block2Color(255,0,0)
	{
		//
	}
		
	void CheckerboardElement::setBlockSize(double size)
	{
		blockSize = size;
	}
		
	void CheckerboardElement::setFirstBlockColor(const Color&color)
	{
		block1Color = color;
	}
		
	void CheckerboardElement::setSecondBlockColor(const Color&color)
	{
		block2Color = color;
	}
			
	double CheckerboardElement::getBlockSize() const
	{
		return blockSize;
	}
		
	const Color& CheckerboardElement::getFirstBlockColor() const
	{
		return block1Color;
	}
		
	const Color& CheckerboardElement::getSecondBlockColor() const
	{
		return block2Color;
	}
		
	void CheckerboardElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		RectangleD frame = getFrame();
		unsigned int blockTimesX = (unsigned int)Math::ceil(frame.width/blockSize);
		unsigned int blockTimesY = (unsigned int)Math::ceil(frame.height/blockSize);
		bool blockOn = true;
		bool blockStartOn = true;
		graphics.clip(frame);
		for(unsigned int y=0; y<blockTimesY; y++)
		{
			blockOn = blockStartOn;
			for(unsigned int x=0; x<blockTimesX; x++)
			{
				double blockX = frame.x + (blockSize*((double)x));
				double blockY = frame.y + (blockSize*((double)y));
				if(blockOn)
				{
					graphics.setColor(block1Color);
					blockOn = false;
				}
				else
				{
					graphics.setColor(block2Color);
					blockOn = true;
				}
				graphics.fillRect(blockX, blockY, blockSize, blockSize);
			}
			if(blockStartOn)
			{
				blockStartOn = false;
			}
			else
			{
				blockStartOn = true;
			}
		}
	}
}
