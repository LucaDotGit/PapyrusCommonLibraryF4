#include "Internal/Structs/Versions.hpp"

namespace Internal::Versions
{
	static constexpr auto MAJOR_KEY = "Major"sv;
	static constexpr auto MINOR_KEY = "Minor"sv;
	static constexpr auto PATCH_KEY = "Patch"sv;
	static constexpr auto BUILD_KEY = "Build"sv;

	Version MakeVersion(
		std::uint32_t a_major, std::uint32_t a_minor, std::uint32_t a_patch, std::uint32_t a_build) noexcept
	{
		auto version = Version();
		SetVersion(version, a_major, a_minor, a_patch, a_build);
		return version;
	}

	Version MakeVersion(const REL::Version& a_version) noexcept
	{
		auto version = Version();
		SetVersion(version, a_version.major(), a_version.minor(), a_version.patch(), a_version.build());
		return version;
	}

	std::tuple<std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t> GetVersion(
		const Version& a_version) noexcept
	{
		return std::make_tuple(
			GetMajor(a_version),
			GetMinor(a_version),
			GetPatch(a_version),
			GetBuild(a_version));
	}

	bool SetVersion(
		Version& a_version, std::uint32_t a_major, std::uint32_t a_minor, std::uint32_t a_patch, std::uint32_t a_build) noexcept
	{
		return SetMajor(a_version, a_major) &&
			   SetMinor(a_version, a_minor) &&
			   SetPatch(a_version, a_patch) &&
			   SetBuild(a_version, a_build);
	}

	std::uint32_t GetMajor(const Version& a_version) noexcept
	{
		return a_version.find<std::uint32_t>(MAJOR_KEY).value_or(0);
	}

	bool SetMajor(Version& a_version, std::uint32_t a_major) noexcept
	{
		return a_version.insert(MAJOR_KEY, a_major);
	}

	std::uint32_t GetMinor(const Version& a_version) noexcept
	{
		return a_version.find<std::uint32_t>(MINOR_KEY).value_or(0);
	}

	bool SetMinor(Version& a_version, std::uint32_t a_minor) noexcept
	{
		return a_version.insert(MINOR_KEY, a_minor);
	}

	std::uint32_t GetPatch(const Version& a_version) noexcept
	{
		return a_version.find<std::uint32_t>(PATCH_KEY).value_or(0);
	}

	bool SetPatch(Version& a_version, std::uint32_t a_patch) noexcept
	{
		return a_version.insert(PATCH_KEY, a_patch);
	}

	std::uint32_t GetBuild(const Version& a_version) noexcept
	{
		return a_version.find<std::uint32_t>(BUILD_KEY).value_or(0);
	}

	bool SetBuild(Version& a_version, std::uint32_t a_build) noexcept
	{
		return a_version.insert(BUILD_KEY, a_build);
	}
}
