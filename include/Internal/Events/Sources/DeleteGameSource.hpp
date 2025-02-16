#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct DeleteGameEvent final
	{
		const std::string_view saveName;
	};

	class DeleteGameSource final
		: public IEventSource<DeleteGameSource, DeleteGameEvent>
	{
	};
}
