#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct UserEvent final
	{
		const RE::BSFixedString eventName;
		const std::vector<RE::BSScript::Variable> args;
	};

	class UserEventSource final
		: public IEventSource<UserEventSource, UserEvent>
	{
	};
}
