#pragma once

namespace Internal::IOMutex
{
	[[nodiscard]] std::shared_mutex& Get() noexcept;
}
