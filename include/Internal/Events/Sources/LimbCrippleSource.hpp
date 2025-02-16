#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct LimbCrippleEvent final
	{
		const RE::Actor* actor;
		const RE::ActorValueInfo* limb;
		const bool isCrippled;
	};

	class LimbCrippleSource final
		: public IEventSource<LimbCrippleSource, LimbCrippleEvent>
	{
	};
}
