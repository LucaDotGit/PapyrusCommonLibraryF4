#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct HUDColorUpdateEvent final
	{
		const std::uint8_t red;
		const std::uint8_t green;
		const std::uint8_t blue;
	};

	class HUDColorUpdateSource final
		: public IEventSource<HUDColorUpdateSource, HUDColorUpdateEvent>
	{
	};
}
