
#include "NumberAdjustElement.hpp"

namespace flui
{
	class TagAdjustElement : public NumberAdjustElement
	{
	public:
		using NumberAdjustElement::NumberAdjustElement;

	protected:
		virtual fgl::String getValueString() const override;
	};
}
