#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct PostSaveGameEvent final
	{
		const std::string_view saveName;
	};

	class PostSaveGameSource final
		: public IEventSource<PostSaveGameSource, PostSaveGameEvent>
	{
	};
}
