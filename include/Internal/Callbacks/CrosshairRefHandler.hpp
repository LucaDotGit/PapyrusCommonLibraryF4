#pragma once

namespace Internal
{
	class CrosshairRefHandler final
		: public REX::Singleton<CrosshairRefHandler>,
		  public RE::BSTEventSink<RE::ViewCasterUpdateEvent>
	{
	public:
		~CrosshairRefHandler() override;

	public:
		void Register();
		void Unregister();

		[[nodiscard]] RE::ObjectRefHandle GetPreviousRef() const;
		[[nodiscard]] RE::ObjectRefHandle GetCurrentRef() const;

		void Clear();

	private:
		RE::BSEventNotifyControl ProcessEvent(const RE::ViewCasterUpdateEvent& a_event, RE::BSTEventSource<RE::ViewCasterUpdateEvent>*) override;

	private:
		mutable std::shared_mutex _mutex;
		RE::ObjectRefHandle _previousRef;
		RE::ObjectRefHandle _currentRef;
	};
}
