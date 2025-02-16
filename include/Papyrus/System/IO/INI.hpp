#pragma once

namespace System::IO::INI
{
	static constexpr auto SCRIPT_NAME = "System:IO:INI"sv;

	static constexpr auto SECTION_KEY = "Section"sv;
	static constexpr auto PAIRS_KEY = "Pairs"sv;

	static constexpr auto PREPEND_BOM = false;
	static constexpr auto IS_UNICODE = true;
	static constexpr auto ALLOW_MULTILINE = true;
	static constexpr auto PARSE_QUOTES = true;

	using Ini = CSimpleIniCaseA;
	using Entry = RE::BSScript::structure_wrapper<"System:IO:INI", "Entry">;

	static std::vector<std::string> GetSections(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		if (ini.LoadFile(a_path.data()) != SI_OK) {
			return {};
		}

		auto sections = Ini::TNamesDepend();
		ini.GetAllSections(sections);

		auto result = std::vector<std::string>();
		result.reserve(sections.size());

		for (const auto& section : sections) {
			result.emplace_back(section.pItem);
		}

		return result;
	}

	static std::vector<std::string> GetKeys(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		if (ini.LoadFile(a_path.data()) != SI_OK) {
			return {};
		}

		auto keys = Ini::TNamesDepend();
		ini.GetAllKeys(a_section.data(), keys);

		auto result = std::vector<std::string>();
		result.reserve(keys.size());

		for (const auto& key : keys) {
			result.emplace_back(key.pItem);
		}

		return result;
	}

	static std::vector<std::string> GetValues(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		if (ini.LoadFile(a_path.data()) != SI_OK) {
			return {};
		}

		auto keys = Ini::TNamesDepend();
		ini.GetAllKeys(a_section.data(), keys);

		auto result = std::vector<std::string>();
		result.reserve(keys.size());

		for (const auto& key : keys) {
			const char* value = ini.GetValue(a_section.data(), key.pItem, "");
			result.emplace_back(value);
		}

		return result;
	}

	static std::vector<::Internal::Pairs::StringPair> GetPairs(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		if (ini.LoadFile(a_path.data()) != SI_OK) {
			return {};
		}

		auto keys = Ini::TNamesDepend();
		ini.GetAllKeys(a_section.data(), keys);

		auto pairs = std::vector<::Internal::Pairs::StringPair>();
		pairs.reserve(keys.size());

		for (const auto& key : keys) {
			const char* value = ini.GetValue(a_section.data(), key.pItem, "");
			auto pair = ::Internal::Pairs::MakeStringPair(key.pItem, value);
			pairs.push_back(std::move(pair));
		}

		return pairs;
	}

	static bool SetPairs(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::vector<::Internal::Pairs::StringPair> a_pairs)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		ini.LoadFile(a_path.data());

		for (const auto& pair : a_pairs) {
			if (!pair) {
				continue;
			}

			const auto&& [key, value] = ::Internal::Pairs::GetStringPair(pair);
			ini.SetValue(a_section.data(), key.data(), value.data());
		}

		return ini.SaveFile(a_path.data(), PREPEND_BOM) >= SI_OK;
	}

	static std::vector<Entry> GetEntries(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		if (ini.LoadFile(a_path.data()) != SI_OK) {
			return {};
		}

		auto sections = Ini::TNamesDepend();
		ini.GetAllSections(sections);

		auto entries = std::vector<Entry>();
		entries.reserve(sections.size());

		for (const auto& sectionName : sections) {
			auto entry = Entry();
			entry.insert(SECTION_KEY, std::string_view{ sectionName.pItem });

			auto keys = Ini::TNamesDepend();
			ini.GetAllKeys(sectionName.pItem, keys);

			auto pairs = std::vector<::Internal::Pairs::StringPair>();
			pairs.reserve(keys.size());

			for (const auto& key : keys) {
				const char* value = ini.GetValue(sectionName.pItem, key.pItem, "");
				auto pair = ::Internal::Pairs::MakeStringPair(key.pItem, value);
				pairs.push_back(std::move(pair));
			}

			entry.insert(PAIRS_KEY, std::move(pairs));
			entries.push_back(std::move(entry));
		}

		return entries;
	}

	static bool SetEntries(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::vector<Entry> a_entries)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		ini.LoadFile(a_path.data());

		for (const auto& entry : a_entries) {
			if (!entry) {
				continue;
			}

			const auto sectionName = entry.find<std::string_view>(SECTION_KEY).value();
			const auto pairs = entry.find<std::vector<::Internal::Pairs::StringPair>>(PAIRS_KEY).value_or(std::vector<::Internal::Pairs::StringPair>());

			for (const auto& pair : pairs) {
				const auto&& [key, value] = ::Internal::Pairs::GetStringPair(pair);
				ini.SetValue(sectionName.data(), key.data(), value.data());
			}
		}

		return ini.SaveFile(a_path.data(), PREPEND_BOM) >= SI_OK;
	}

	static bool ContainsSection(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		return ini.LoadFile(a_path.data()) >= SI_OK &&
			   ini.SectionExists(a_section.data());
	}

	static bool ContainsKey(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		return ini.LoadFile(a_path.data()) >= SI_OK &&
			   ini.KeyExists(a_section.data(), a_key.data());
	}

	template <typename T>
	static T GetImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		T a_default)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::shared_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		if (ini.LoadFile(a_path.data()) < SI_OK) {
			return a_default;
		}

		if constexpr (std::is_same_v<T, bool>) {
			return ini.GetBoolValue(a_section.data(), a_key.data(), a_default);
		}
		else if constexpr (std::is_same_v<T, std::int32_t> || std::is_same_v<T, std::uint32_t>) {
			return static_cast<T>(ini.GetLongValue(a_section.data(), a_key.data(), a_default));
		}
		else if constexpr (std::is_floating_point_v<T>) {
			return static_cast<T>(ini.GetDoubleValue(a_section.data(), a_key.data(), a_default));
		}
		else if constexpr (std::is_same_v<T, std::string_view>) {
			return ini.GetValue(a_section.data(), a_key.data(), a_default.data());
		}
		else if constexpr (std::is_convertible_v<T, std::string_view>) {
			const auto view = std::string_view{ a_default };
			return ini.GetValue(a_section.data(), a_key.data(), view.data());
		}
		else {
			static_assert(false, "Unsupported type");
		}
	}

	template <typename T>
	static bool SetImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		T&& a_value)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		ini.LoadFile(a_path.data());

		if constexpr (std::is_same_v<std::remove_reference_t<T>, bool>) {
			ini.SetBoolValue(a_section.data(), a_key.data(), std::forward<T>(a_value));
		}
		else if constexpr (std::is_same_v<std::remove_reference_t<T>, std::int32_t> || std::is_same_v<std::remove_reference_t<T>, std::uint32_t>) {
			ini.SetLongValue(a_section.data(), a_key.data(), std::forward<T>(a_value));
		}
		else if constexpr (std::is_floating_point_v<std::remove_reference_t<T>>) {
			ini.SetDoubleValue(a_section.data(), a_key.data(), std::forward<T>(a_value));
		}
		else if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string_view>) {
			ini.SetValue(a_section.data(), a_key.data(), std::forward<T>(a_value).data());
		}
		else if constexpr (std::is_convertible_v<std::remove_reference_t<T>, std::string_view>) {
			const auto view = std::string_view{ std::forward<T>(a_value) };
			ini.SetValue(a_section.data(), a_key.data(), view.data());
		}
		else {
			static_assert(false, "Unsupported type");
		}

		return ini.SaveFile(a_path.data(), PREPEND_BOM) >= SI_OK;
	}

	static bool GetBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		bool a_default)
	{
		return GetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_default);
	}

	static bool SetBool(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		bool a_value)
	{
		return SetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_value);
	}

	static std::int32_t GetInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		std::int32_t a_default)
	{
		return GetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_default);
	}

	static bool SetInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		std::int32_t a_value)
	{
		return SetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_value);
	}

	static std::uint32_t GetUInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		std::uint32_t a_default)
	{
		return GetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_default);
	}

	static bool SetUInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		std::uint32_t a_value)
	{
		return SetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_value);
	}

	static float GetFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		float a_default)
	{
		return GetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_default);
	}

	static bool SetFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		float a_value)
	{
		return SetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_value);
	}

	static std::string GetString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		std::string a_default)
	{
		return GetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_default);
	}

	static bool SetString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key,
		std::string_view a_value)
	{
		return SetImpl(a_vm, a_stackID, a_path, a_section, a_key, a_value);
	}

	static bool RemoveSection(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		return ini.LoadFile(a_path.data()) >= SI_OK &&
			   ini.Delete(a_section.data(), nullptr) &&
			   ini.SaveFile(a_path.data(), PREPEND_BOM) >= SI_OK;
	}

	static bool RemoveKey(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::string_view a_path,
		std::string_view a_section,
		std::string_view a_key)
	{
		if (!::Internal::Sandbox::IsInSandbox(a_path)) {
			a_vm.PostError(::Internal::Errors::OUT_OF_SANDBOX, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}

		const auto lock = std::unique_lock{ ::Internal::IOMutex::Get() };

		auto ini = Ini();
		ini.SetUnicode(IS_UNICODE);
		ini.SetMultiLine(ALLOW_MULTILINE);
		ini.SetQuotes(PARSE_QUOTES);

		constexpr auto REMOVE_EMPTY = false;

		return ini.LoadFile(a_path.data()) >= SI_OK &&
			   ini.Delete(a_section.data(), a_key.data(), REMOVE_EMPTY) &&
			   ini.SaveFile(a_path.data(), PREPEND_BOM) >= SI_OK;
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetSections);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetKeys);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetValues);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetPairs);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetPairs);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetEntries);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetEntries);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsSection);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ContainsKey);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetUInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetUInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetString);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RemoveSection);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RemoveKey);

		return true;
	}
}
