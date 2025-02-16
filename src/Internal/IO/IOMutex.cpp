#include "Internal/IO/IOMutex.hpp"

namespace Internal::IOMutex
{
	static auto Mutex = std::shared_mutex();

	std::shared_mutex& Get() noexcept
	{
		return Mutex;
	}
}
