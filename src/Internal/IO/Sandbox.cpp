#include "Internal/IO/Sandbox.hpp"

namespace Internal::Sandbox
{
	static const std::filesystem::path ROOT = []() noexcept {
		auto error = std::error_code();
		auto root = std::filesystem::current_path(error);

		if (error) {
			F4SE::stl::report_and_fail(error.message());
		}

		return root;
	}();

	bool IsInSandbox(const std::filesystem::path& a_path) noexcept
	{
		try {
			const auto combination = ROOT / a_path;
			const auto normalized = combination.lexically_normal();
			const auto&& [_, rootEnd] = std::ranges::mismatch(normalized, ROOT);
			return rootEnd == ROOT.end();
		}
		catch (const std::exception&) {
			return false;
		}
	}
}
