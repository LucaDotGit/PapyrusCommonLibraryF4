#pragma once

namespace Internal
{
	class LockpickRefHandler final
		: public REX::Singleton<LockpickRefHandler>,
		  public RE::BSTEventSink<RE::TESActivateEvent>
	{
	public:
		~LockpickRefHandler() override;

	public:
		void Register();
		void Unregister();

		[[nodiscard]] RE::NiPointer<RE::TESObjectREFR> GetLastRef() const;

		void Clear();

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent& a_event, RE::BSTEventSource<RE::TESActivateEvent>*) override;

	private:
		mutable std::shared_mutex _mutex;
		RE::NiPointer<RE::TESObjectREFR> _lastRef;
	};
}
