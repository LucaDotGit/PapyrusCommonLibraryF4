#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct ObjectOpenCloseEvent final
	{
		const RE::TESObjectREFR* sourceRef;
		const RE::TESObjectREFR* targetRef;
		const bool isOpened;
	};

	class ObjectOpenCloseSource final
		: public IEventSource<ObjectOpenCloseSource, ObjectOpenCloseEvent>
	{
	};
}
