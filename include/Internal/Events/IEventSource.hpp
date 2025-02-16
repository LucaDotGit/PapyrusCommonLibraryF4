#pragma once

namespace Internal::Events
{
	template <class TEventSource, class TEvent>
	class IEventSource
		: public RE::BSTEventSource<TEvent>
	{
	public:
		using event_type = TEvent;

	public:
		[[nodiscard]] static TEventSource* GetEventSource() noexcept
		{
			static auto eventSource = TEventSource();
			return &eventSource;
		}

	protected:
		IEventSource() noexcept = default;
		virtual ~IEventSource() noexcept = default;

		IEventSource(const IEventSource&) = delete;
		IEventSource(IEventSource&&) = delete;
		IEventSource& operator=(const IEventSource&) = delete;
		IEventSource& operator=(IEventSource&&) = delete;
	};
}
