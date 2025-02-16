#pragma once

#include "Internal/Events/Sources/AnimationGraphEventSource.hpp"

namespace Internal::Events::AnimationGraphEventPatch
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
				auto vtable = REL::Relocation<std::uintptr_t>{ T::VTABLE[3] };
				_ProcessEvent = vtable.write_vfunc(0x1, ProcessEvent);
			}

		private:
			static RE::BSEventNotifyControl ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_this,
				const RE::BSAnimationGraphEvent& a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_source)
			{
				const auto* ref = event_cast<RE::TESObjectREFR>(a_this, RE::RTTI::BSTEventSink_BSAnimationGraphEvent_);
				if (ref) {
					AnimationGraphEventSource::GetEventSource()->Notify({ ref, a_event.tag, a_event.payload });
				}

				return _ProcessEvent(a_this, a_event, a_source);
			}

			template <class TTarget, class TSource>
				requires std::is_pointer_v<TSource>
			[[nodiscard]] static TTarget* event_cast(const TSource a_source, const REL::RelocationID& a_rtti)
			{
				return reinterpret_cast<TTarget*>(RE::RTDynamicCast(reinterpret_cast<void*>(a_source), 0,
					reinterpret_cast<void*>(a_rtti.address()), reinterpret_cast<void*>(TTarget::RTTI.address()), 0));
			}

		private:
			inline static auto _ProcessEvent = REL::Relocation<decltype(&RE::BSTEventSink<RE::BSAnimationGraphEvent>::ProcessEvent)>();
		};
	}
}
