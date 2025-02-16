#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct LifeStateChangeEvent final
	{
		const RE::Actor* actor;
		const RE::ACTOR_LIFE_STATE oldState;
		const RE::ACTOR_LIFE_STATE newState;
	};

	class LifeStateChangeSource final
		: public IEventSource<LifeStateChangeSource, LifeStateChangeEvent>
	{
	};
}
