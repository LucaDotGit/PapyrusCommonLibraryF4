#include "Internal/Events/Patches/LifeStateChangePatch.hpp"

#include "Internal/Events/Sources/LifeStateChangeSource.hpp"

namespace Internal::Events::LifeStateChangePatch
{
	static auto _SetLifeState = REL::Relocation<decltype(&RE::Actor::SetLifeState)>();

	static void SetLifeState(RE::Actor* a_this, RE::ACTOR_LIFE_STATE a_lifeState)
	{
		const auto oldState = static_cast<RE::ACTOR_LIFE_STATE>(a_this->lifeState);
		if (oldState != a_lifeState) {
			LifeStateChangeSource::GetEventSource()->Notify(
				{ a_this, oldState, a_lifeState });
		}

		_SetLifeState(a_this, a_lifeState);
	}

	void Install() noexcept
	{
		auto vtable = REL::Relocation<std::uintptr_t>{ RE::Actor::VTABLE[0] };
		_SetLifeState = vtable.write_vfunc(0x105, SetLifeState);
	}
}
