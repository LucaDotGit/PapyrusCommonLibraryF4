#include "Internal/IO/Wildcards.hpp"

namespace Internal::Wildcards
{
	static constexpr auto ZERO_OR_MORE = '*';
	static constexpr auto EXACTLY_ONE = '?';

	bool IsMatch(std::string_view a_text, std::string_view a_pattern) noexcept
	{
		if (a_pattern.empty()) {
			return a_text.empty();
		}

		auto textIt = a_text.begin();
		auto patternIt = a_pattern.begin();
		auto starIt = a_pattern.end();
		auto matchIt = a_text.begin();

		while (textIt != a_text.end()) {
			if (patternIt != a_pattern.end() &&
				(std::tolower(*patternIt) == std::tolower(*textIt) ||
					*patternIt == EXACTLY_ONE)) {
				textIt++;
				patternIt++;
				continue;
			}

			if (patternIt != a_pattern.end() && *patternIt == ZERO_OR_MORE) {
				starIt = patternIt++;
				matchIt = textIt;
				continue;
			}

			if (starIt != a_pattern.end()) {
				patternIt = starIt + 1;
				textIt = ++matchIt;
				continue;
			}

			return false;
		}

		while (patternIt != a_pattern.end() && *patternIt == ZERO_OR_MORE) {
			patternIt++;
		}

		return patternIt == a_pattern.end();
	}
}
