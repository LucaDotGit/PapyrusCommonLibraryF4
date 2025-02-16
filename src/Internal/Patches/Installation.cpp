#include "Internal/Patches/Installation.hpp"

#include "Internal/Patches/EditorIDCache.hpp"

namespace Internal::Patches
{
	void Install() noexcept
	{
		logger::debug("Installing patches"sv);

		EditorIDCache::Install();
	}
}
