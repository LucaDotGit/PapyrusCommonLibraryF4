#pragma once

#include "Internal/Events/Sources/ActorValueChangeSource.hpp"

namespace Internal::Events::ActorValueChangePatch
{
	void Install() noexcept;

	namespace
	{
		template <class T>
			requires std::derived_from<T, RE::TESObjectREFR>
		class Patch final
		{
		private:
			Patch() = delete;
			Patch(const Patch&) = delete;
			Patch(Patch&&) = delete;
			Patch& operator=(const Patch&) = delete;
			Patch& operator=(Patch&&) = delete;

		public:
			static void Install() noexcept
			{
				auto vtable = REL::Relocation<std::uintptr_t>{ T::VTABLE[7] };

				_ModActorValue = vtable.write_vfunc(0x6, ModActorValue);
				_SetActorValue = vtable.write_vfunc(0x9, SetActorValue);
			}

		private:
			static void ModActorValue(RE::ActorValueOwner* a_this, RE::ACTOR_VALUE_MODIFIER a_modifier, const RE::ActorValueInfo& a_info, float a_value)
			{
				const auto* ref = RE::fallout_cast<const RE::TESObjectREFR*>(a_this);
				if (!ref) {
					_ModActorValue(a_this, a_modifier, a_info, a_value);
					return;
				}

				float oldValue = a_this->GetActorValue(a_info);
				_ModActorValue(a_this, a_modifier, a_info, a_value);
				float newValue = a_this->GetActorValue(a_info);

				if (oldValue != newValue) {
					ActorValueChangeSource::GetEventSource()->Notify({ ref, &a_info, oldValue, newValue });
				}
			}

			static void SetActorValue(RE::ActorValueOwner* a_this, const RE::ActorValueInfo& a_info, float a_value)
			{
				const auto* ref = RE::fallout_cast<const RE::TESObjectREFR*>(a_this);
				if (!ref) {
					_SetActorValue(a_this, a_info, a_value);
					return;
				}

				float oldValue = a_this->GetActorValue(a_info);
				_SetActorValue(a_this, a_info, a_value);
				float newValue = a_this->GetActorValue(a_info);

				if (oldValue != newValue) {
					ActorValueChangeSource::GetEventSource()->Notify({ ref, &a_info, oldValue, newValue });
				}
			}

		private:
			inline static auto _ModActorValue = REL::Relocation<decltype(&RE::ActorValueOwner::ModActorValue)>();
			inline static auto _SetActorValue = REL::Relocation<decltype(&RE::ActorValueOwner::SetActorValue)>();
		};
	}
}
