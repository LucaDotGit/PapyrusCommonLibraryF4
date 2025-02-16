#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct ObjectGrabReleaseEvent final
	{
		const RE::TESObjectREFR* ref;
		const bool isGrabbed;
	};

	class ObjectGrabReleaseSource final
		: public IEventSource<ObjectGrabReleaseSource, ObjectGrabReleaseEvent>
	{
	};
}
