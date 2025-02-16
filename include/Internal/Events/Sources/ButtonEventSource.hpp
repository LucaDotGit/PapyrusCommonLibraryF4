#pragma once

#include "Internal/Events/IEventSource.hpp"

namespace Internal::Events
{
	struct ButtonEvent final
	{
		[[nodiscard]] bool IsUp() const noexcept { return !IsPressed() && IsRepeating(); }
		[[nodiscard]] bool IsDown() const noexcept { return IsPressed() && !IsRepeating(); }
		[[nodiscard]] bool IsPressed() const noexcept { return analogValue > 0.0f; }
		[[nodiscard]] bool IsRepeating() const noexcept { return heldSeconds > 0.0f; }
		[[nodiscard]] bool IsJustPressed() const noexcept { return IsPressed() && !IsRepeating(); }
		[[nodiscard]] bool IsReleased(float a_heldDownSecs) const noexcept { return !IsPressed() && a_heldDownSecs <= heldSeconds; }
		[[nodiscard]] bool IsHeldDown(float a_heldDownSecs) const noexcept { return IsPressed() && a_heldDownSecs <= heldSeconds; }

		const RE::INPUT_DEVICE deviceType;
		const RE::BS_BUTTON_CODE buttonCode;
		const RE::BSFixedString controlName;
		const float analogValue;
		const float heldSeconds;
	};

	class ButtonEventSource final
		: public IEventSource<ButtonEventSource, ButtonEvent>
	{
	};
}
