#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct CellLoadEvent final
	{
		const RE::TESObjectCELL* cell;
	};

	class CellLoadSource final
		: public IEventSource<CellLoadSource, CellLoadEvent>
	{
	};
}
