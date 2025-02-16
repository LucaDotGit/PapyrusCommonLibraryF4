#include "Internal/Config/Config.hpp"

namespace Internal::Config
{
	static constexpr auto PLUGINS_PATH = "Data/F4SE/Plugins"sv;

	static const auto FILE_PATH = fmt::format("{}/{}.ini", PLUGINS_PATH, Plugin::NAME);
	static const auto CUSTOM_FILE_PATH = fmt::format("{}/{}_Custom.ini", PLUGINS_PATH, Plugin::NAME);

	void Load() noexcept
	{
		auto* ini = REX::INI::SettingStore::GetSingleton();
		ini->Init(FILE_PATH, CUSTOM_FILE_PATH);
		ini->Load();
	}
}
