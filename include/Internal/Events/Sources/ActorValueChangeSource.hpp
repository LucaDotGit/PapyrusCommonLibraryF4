#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct ActorValueChangeEvent final
	{
		const RE::TESObjectREFR* ref;
		const RE::ActorValueInfo* valueHolder;
		const float oldValue;
		const float newValue;
	};

	class ActorValueChangeSource final
		: public IEventSource<ActorValueChangeSource, ActorValueChangeEvent>
	{
	};
}
