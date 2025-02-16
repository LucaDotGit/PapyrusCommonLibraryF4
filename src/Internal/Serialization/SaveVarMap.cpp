#include "Internal/Serialization/SaveVarMap.hpp"

#include "Internal/Serialization/Serializer.hpp"
#include "Internal/Serialization/StringMap.hpp"

namespace Internal::Serialization
{
	static constexpr auto TYPE = static_cast<std::uint32_t>('SVVR');
	static constexpr auto VERSION = 1ui32;

	static const auto PATH = std::filesystem::path(L"Data\\PCL\\SaveVars"s);
	static const auto EXTENSION = std::filesystem::path(L".txt"s);

	void SaveVarMap::Setup()
	{
		constexpr auto DIR_OPTIONS = std::filesystem::directory_options::skip_permission_denied;

		auto entryError = std::error_code();
		for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(PATH, DIR_OPTIONS, entryError)) {
			if (dirEntry.path().extension() != EXTENSION) {
				continue;
			}

			auto isFileError = std::error_code();
			if (!dirEntry.is_regular_file(isFileError)) {
				continue;
			}

			_validNamespaces.emplace(dirEntry.path().stem().string());
		}
	}

	void SaveVarMap::Hash()
	{
		const auto lock = std::shared_lock{ _mutex };

		for (const auto& [name, map] : _variables) {
			StringMap::AddString(name);

			for (const auto& [key, var] : map) {
				StringMap::AddString(key);
				StringMap::AddVar(var);
			}
		}
	}

	bool SaveVarMap::Load([[maybe_unused]] const F4SE::SerializationInterface* a_interface,
		[[maybe_unused]] std::uint32_t a_recordType,
		[[maybe_unused]] std::uint32_t a_recordVersion,
		[[maybe_unused]] std::uint32_t a_recordLength)
	{
		if (a_recordType != TYPE || a_recordVersion != VERSION) {
			return false;
		}

		const auto lock = std::unique_lock{ _mutex };

		auto nameCount = Serializer::ReadRecordT<Serialization::size_t>(a_interface);
		_variables.reserve(nameCount);

		for (auto i = static_cast<Serialization::size_t>(0); i < nameCount; i++) {
			auto name = Serializer::ReadRecordString(a_interface);
			auto keyCount = Serializer::ReadRecordT<Serialization::size_t>(a_interface);

			if (keyCount <= 0) {
				continue;
			}

			auto& map = _variables[name];
			map.reserve(keyCount);

			for (auto j = static_cast<Serialization::size_t>(0); j < keyCount; j++) {
				auto key = Serializer::ReadRecordString(a_interface);
				auto var = Serializer::ReadRecordVar(a_interface);

				map[key] = std::move(var);
			}
		}

		for (const auto& [name, _] : _variables) {
			if (!_validNamespaces.contains(name)) {
				_variables.erase(name);
			}
		}

		return true;
	}

	void SaveVarMap::Save([[maybe_unused]] const F4SE::SerializationInterface* a_interface) const
	{
		const auto lock = std::shared_lock{ _mutex };

		if (_variables.empty() || !a_interface->OpenRecord(TYPE, VERSION)) {
			return;
		}

		if (!Serializer::WriteRecordT(a_interface, static_cast<Serialization::size_t>(_variables.size()))) {
			return;
		}

		for (const auto& [name, map] : _variables) {
			if (!Serializer::WriteRecordString(a_interface, name) ||
				!Serializer::WriteRecordT(a_interface, static_cast<Serialization::size_t>(map.size()))) {
				continue;
			}

			for (const auto& [key, var] : map) {
				if (!Serializer::WriteRecordString(a_interface, key) ||
					!Serializer::WriteRecordVar(a_interface, var)) {
					continue;
				}
			}
		}
	}

	void SaveVarMap::Revert([[maybe_unused]] const F4SE::SerializationInterface* a_interface)
	{
		const auto lock = std::unique_lock{ _mutex };
		_variables.clear();
	}

	bool SaveVarMap::IsNamespaceValid(const RE::BSFixedString& a_namespace) const
	{
		return _validNamespaces.contains(a_namespace);
	}

	bool SaveVarMap::SetPairs(const RE::BSFixedString& a_namespace, const std::vector<Pairs::Pair>& a_pairs)
	{
		if (!_validNamespaces.contains(a_namespace)) {
			return false;
		}

		return VarMap::SetPairs(a_namespace, a_pairs);
	}

	bool SaveVarMap::SetValue(const RE::BSFixedString& a_namespace, const RE::BSFixedString& a_key, const RE::BSScript::Variable* a_value)
	{
		if (!_validNamespaces.contains(a_namespace)) {
			return false;
		}

		return VarMap::SetValue(a_namespace, a_key, a_value);
	}
}