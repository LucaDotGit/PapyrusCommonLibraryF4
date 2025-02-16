#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct PerkPointIncreaseEvent final
	{
		const std::uint8_t amount;
	};

	class PerkPointIncreaseSource final
		: public IEventSource<PerkPointIncreaseSource, PerkPointIncreaseEvent>
	{
	};
}
