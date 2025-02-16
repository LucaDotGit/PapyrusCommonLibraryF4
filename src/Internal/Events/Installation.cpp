#include "Internal/Events/Installation.hpp"

#include "Internal/Events/Registration.hpp"

#include "Internal/Events/Patches/ActorValueChangePatch.hpp"
#include "Internal/Events/Patches/AnimationGraphEventPatch.hpp"
#include "Internal/Events/Patches/CellLoadPatch.hpp"
#include "Internal/Events/Patches/CombatStateChangePatch.hpp"
#include "Internal/Events/Patches/DestructionStageChangePatch.hpp"
#include "Internal/Events/Patches/HUDColorUpdatePatch.hpp"
#include "Internal/Events/Patches/LifeStateChangePatch.hpp"
#include "Internal/Events/Patches/LimbCripplePatch.hpp"
#include "Internal/Events/Patches/LocationEnterExitPatch.hpp"
#include "Internal/Events/Patches/LocationLoadPatch.hpp"
#include "Internal/Events/Patches/ObjectGrabReleasePatch.hpp"
#include "Internal/Events/Patches/ObjectHitPatch.hpp"
#include "Internal/Events/Patches/ObjectOpenClosePatch.hpp"
#include "Internal/Events/Patches/PerkPointIncreasePatch.hpp"
#include "Internal/Events/Patches/TriggerEnterPatch.hpp"
#include "Internal/Events/Patches/TriggerLeavePatch.hpp"
#include "Internal/Events/Patches/UserInputPatch.hpp"

namespace Internal::Events
{
	void Install() noexcept
	{
		logger::debug("Game Events: Installation"sv);

		ActorValueChangePatch::Install();
		AnimationGraphEventPatch::Install();
		CellLoadPatch::Install();
		CombatStateChangePatch::Install();
		DestructionStageChangePatch::Install();
		HUDColorUpdatePatch::Install();
		LifeStateChangePatch::Install();
		LimbCripplePatch::Install();
		LocationEnterExitPatch::Install();
		LocationLoadPatch::Install();
		ObjectGrabReleasePatch::Install();
		ObjectHitPatch::Install();
		ObjectOpenClosePatch::Install();
		PerkPointIncreasePatch::Install();
		TriggerEnterPatch::Install();
		TriggerLeavePatch::Install();
		UserInputPatch::Install();
	}
}
