#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct DestructionStageChangeEvent final
	{
		const RE::TESObjectREFR* ref;
		const std::uint32_t oldStage;
		const std::uint32_t newStage;
	};

	class DestructionStageChangeSource final
		: public IEventSource<DestructionStageChangeSource, DestructionStageChangeEvent>
	{
	};
}
