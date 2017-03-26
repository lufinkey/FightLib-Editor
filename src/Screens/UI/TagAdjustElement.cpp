
#include "TagAdjustElement.hpp"

namespace flui
{
	fgl::String TagAdjustElement::getValueString() const
	{
		if(getValue().toArithmeticValue<long long>()==-1)
		{
			return "none";
		}
		return NumberAdjustElement::getValueString();
	}
}
