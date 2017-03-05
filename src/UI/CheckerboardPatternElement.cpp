
#include "CheckerboardPatternElement.hpp"

using namespace fgl;

namespace flui
{
	CheckerboardPatternElement::CheckerboardPatternElement() : CheckerboardPatternElement(RectangleD(0,0,0,0))
	{
		//
	}
		
	CheckerboardPatternElement::CheckerboardPatternElement(const RectangleD&frame)
		: blockSize(8), block1Color(0,0,0), block2Color(255,0,0)
	{
		//
	}
		
	void CheckerboardPatternElement::setBlockSize(double size)
	{
		blockSize = size;
	}
		
	void CheckerboardPatternElement::setFirstBlockColor(const Color&color)
	{
		block1Color = color;
	}
		
	void CheckerboardPatternElement::setSecondBlockColor(const Color&color)
	{
		block2Color = color;
	}
			
	double CheckerboardPatternElement::getBlockSize() const
	{
		return blockSize;
	}
		
	const Color& CheckerboardPatternElement::getFirstBlockColor() const
	{
		return block1Color;
	}
		
	const Color& CheckerboardPatternElement::getSecondBlockColor() const
	{
		return block2Color;
	}
		
	void CheckerboardPatternElement::drawMain(ApplicationData appData, Graphics graphics) const
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
				double blockX = frame.x + (blockSize*((double)blockTimesX));
				double blockY = frame.y + (blockSize*((double)blockTimesY));
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
