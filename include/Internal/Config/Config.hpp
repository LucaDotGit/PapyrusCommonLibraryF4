#pragma once

namespace Internal::Config
{
	inline const auto LogDuplicateEditorIDs = REX::INI::Bool{ "General"sv, "bLogDuplicateEditorIDs"sv, false };

	void Load() noexcept;
}
