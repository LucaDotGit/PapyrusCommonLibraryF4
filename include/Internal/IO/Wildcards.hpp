#pragma once

namespace Internal::Wildcards
{
	bool IsMatch(std::string_view a_text, std::string_view a_pattern) noexcept;
}
