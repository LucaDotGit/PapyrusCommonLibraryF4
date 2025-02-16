#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct PostLoadGameEvent final
	{
		const bool isSucceeded;
	};

	class PostLoadGameSource final
		: public IEventSource<PostLoadGameSource, PostLoadGameEvent>
	{
	};
}
