#pragma once

namespace Internal::Versions
{
	using Version = RE::BSScript::structure_wrapper<"System:Versions", "Version">;

	[[nodiscard]] Version MakeVersion(
		std::uint32_t a_major = 0, std::uint32_t a_minor = 0, std::uint32_t a_patch = 0, std::uint32_t a_build = 0) noexcept;
	[[nodiscard]] Version MakeVersion(const REL::Version& a_version) noexcept;

	[[nodiscard]] std::tuple<std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t> GetVersion(
		const Version& a_version) noexcept;
	bool SetVersion(
		Version& a_version, std::uint32_t a_major, std::uint32_t a_minor, std::uint32_t a_patch, std::uint32_t a_build) noexcept;

	[[nodiscard]] std::uint32_t GetMajor(const Version& a_version) noexcept;
	bool SetMajor(Version& a_version, std::uint32_t a_major) noexcept;

	[[nodiscard]] std::uint32_t GetMinor(const Version& a_version) noexcept;
	bool SetMinor(Version& a_version, std::uint32_t a_minor) noexcept;

	[[nodiscard]] std::uint32_t GetPatch(const Version& a_version) noexcept;
	bool SetPatch(Version& a_version, std::uint32_t a_patch) noexcept;

	[[nodiscard]] std::uint32_t GetBuild(const Version& a_version) noexcept;
	bool SetBuild(Version& a_version, std::uint32_t a_build) noexcept;
}
