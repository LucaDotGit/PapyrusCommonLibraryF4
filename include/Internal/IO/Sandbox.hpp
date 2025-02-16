#pragma once

namespace Internal::Sandbox
{
	[[nodiscard]] bool IsInSandbox(const std::filesystem::path& a_path) noexcept;
}
