#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct AnimationGraphEvent final
	{
		const RE::TESObjectREFR* ref;
		const RE::BSFixedString eventName;
		const RE::BSFixedString payload;
	};

	class AnimationGraphEventSource final
		: public IEventSource<AnimationGraphEventSource, AnimationGraphEvent>
	{
	};
}
