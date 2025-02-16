#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct PreSaveGameEvent final
	{
		const std::string_view saveName;
	};

	class PreSaveGameSource final
		: public IEventSource<PreSaveGameSource, PreSaveGameEvent>
	{
	};
}
