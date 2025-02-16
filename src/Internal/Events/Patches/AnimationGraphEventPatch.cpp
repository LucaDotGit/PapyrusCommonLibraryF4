#include "Internal/Events/Patches/AnimationGraphEventPatch.hpp"

namespace Internal::Events::AnimationGraphEventPatch
{
	void Install() noexcept
	{
		Patch<RE::TESObjectREFR>::Install();
		Patch<RE::Actor>::Install();
		Patch<RE::PlayerCharacter>::Install();
	}
}
