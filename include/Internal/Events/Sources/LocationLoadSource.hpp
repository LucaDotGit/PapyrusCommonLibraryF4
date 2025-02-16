#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct LocationLoadEvent final
	{
		const RE::BGSLocation* location;
	};

	class LocationLoadSource final
		: public IEventSource<LocationLoadSource, LocationLoadEvent>
	{
	};
}
