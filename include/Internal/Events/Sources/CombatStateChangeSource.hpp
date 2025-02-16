#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct CombatStateChangeEvent final
	{
		const RE::Actor* sourceActor;
		const RE::Actor* targetActor;
		const RE::ACTOR_COMBAT_STATE setState;
	};

	class CombatStateChangeSource final
		: public IEventSource<CombatStateChangeSource, CombatStateChangeEvent>
	{
	};
}
