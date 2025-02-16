#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct LocationEnterExitEvent final
	{
		const RE::Actor* actor;
		const RE::BGSLocation* oldLocation;
		const RE::BGSLocation* newLocation;
	};

	class LocationEnterExitSource final
		: public IEventSource<LocationEnterExitSource, LocationEnterExitEvent>
	{
	};
}
