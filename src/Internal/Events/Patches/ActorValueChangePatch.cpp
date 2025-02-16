#include "Internal/Events/Patches/ActorValueChangePatch.hpp"

namespace Internal::Events::ActorValueChangePatch
{
	void Install() noexcept
	{
		Patch<RE::TESObjectREFR>::Install();
		Patch<RE::Actor>::Install();
		Patch<RE::PlayerCharacter>::Install();
	}
}
