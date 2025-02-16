#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	class ObjectHitSource final
		: public IEventSource<ObjectHitSource, RE::TESHitEvent>
	{
	};
}
