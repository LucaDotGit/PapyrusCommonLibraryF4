#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct TriggerEnterLeaveEvent final
	{
		const RE::TESObjectREFR* sourceRef;
		const RE::TESObjectREFR* targetRef;
		const bool isEntered;
	};

	class TriggerEnterLeaveSource final
		: public IEventSource<TriggerEnterLeaveSource, TriggerEnterLeaveEvent>
	{
	};
}
