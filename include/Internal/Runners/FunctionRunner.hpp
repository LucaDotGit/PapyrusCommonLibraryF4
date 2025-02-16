#pragma once

namespace Internal::FunctionRunner
{
	enum Event : std::uint8_t
	{
		OnGameStart,
		OnPostGameStart,
		OnGameLoad,

		Count
	};

	void Setup();
	void Run(Event a_event);
}
