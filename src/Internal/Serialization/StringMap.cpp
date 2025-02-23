#include "Internal/Serialization/StringMap.hpp"

namespace Internal::Serialization::StringMap
{
	static constexpr auto TYPE = static_cast<std::uint32_t>('STRM');
	static constexpr auto VERSION = 1ui32;

	static auto Strings = Types::unordered_string_map<RE::BSFixedString, Serialization::size_t>();
	static auto Indexes = std::map<Serialization::size_t, RE::BSFixedString>();
	static auto LastIndex = static_cast<Serialization::size_t>(0);

	template <typename T>
		requires std::is_trivially_copyable_v<T>
	[[nodiscard]] static T ReadRecordT(const F4SE::SerializationInterface* a_interface)
	{
		auto value = T();
		a_interface->ReadRecordData(std::addressof(value), sizeof(value));
		return value;
	}

	template <typename T>
		requires std::is_trivially_copyable_v<std::remove_cvref_t<T>>
	static bool WriteRecordT(const F4SE::SerializationInterface* a_interface, T&& a_value)
	{
		return a_interface->WriteRecordData(std::addressof(a_value), sizeof(a_value));
	}

	[[nodiscard]] static RE::BSFixedString ReadRecordString(const F4SE::SerializationInterface* a_interface)
	{
		auto size = static_cast<Serialization::size_t>(0);
		if (!a_interface->ReadRecordData(std::addressof(size), sizeof(size)) || size == 0) {
			return {};
		}

		auto string = std::string(size, '\0');
		a_interface->ReadRecordData(string.data(), size);

		return RE::BSFixedString(string);
	}

	[[nodiscard]] static bool WriteRecordString(const F4SE::SerializationInterface* a_interface, const RE::BSFixedString& a_string)
	{
		const auto size = static_cast<Serialization::size_t>(a_string.size());
		return a_interface->WriteRecordData(std::addressof(size), sizeof(size)) &&
			   (size == 0 || a_interface->WriteRecordData(a_string.data(), size));
	}

	bool Load([[maybe_unused]] const F4SE::SerializationInterface* a_interface,
		[[maybe_unused]] std::uint32_t a_recordType,
		[[maybe_unused]] std::uint32_t a_recordVersion,
		[[maybe_unused]] std::uint32_t a_recordLength)
	{
		if (a_recordType != TYPE || a_recordVersion != VERSION) {
			return false;
		}

		const auto size = ReadRecordT<Serialization::size_t>(a_interface);
		Strings.reserve(size);

		for (auto i = static_cast<Serialization::size_t>(0); i < size; i++) {
			auto key = ReadRecordString(a_interface);

			Strings[key] = i;
			Indexes[i] = key;
		}

		LastIndex = size;
		return true;
	}

	void Save([[maybe_unused]] const F4SE::SerializationInterface* a_interface)
	{
		if (Strings.empty() || !a_interface->OpenRecord(TYPE, VERSION)) {
			return;
		}

		if (!WriteRecordT(a_interface, static_cast<Serialization::size_t>(Strings.size()))) {
			return;
		}

		for (const auto& [i, key] : Indexes) {
			if (!WriteRecordString(a_interface, key)) {
				continue;
			}
		}
	}

	void Revert([[maybe_unused]] const F4SE::SerializationInterface* a_interface)
	{
		Clear();
	}

	bool Contains(Serialization::size_t a_index)
	{
		return Indexes.contains(a_index);
	}

	bool Contains(const RE::BSFixedString& a_key)
	{
		return Strings.contains(a_key);
	}

	std::optional<RE::BSFixedString> GetString(Serialization::size_t a_index)
	{
		const auto indexIt = Indexes.find(a_index);
		if (indexIt == Indexes.end()) {
			return std::nullopt;
		}

		return indexIt->second;
	}

	std::optional<Serialization::size_t> GetIndex(const RE::BSFixedString& a_key)
	{
		const auto keyIt = Strings.find(a_key);
		if (keyIt == Strings.end()) {
			return std::nullopt;
		}

		return keyIt->second;
	}

	Serialization::size_t AddString(const RE::BSFixedString& a_key)
	{
		const auto keyIt = Strings.find(a_key);
		if (keyIt != Strings.end()) {
			return keyIt->second;
		}

		auto index = LastIndex;
		LastIndex++;

		Strings[a_key] = index;
		Indexes[index] = a_key;

		return index;
	}

	bool AddVar(const RE::BSScript::Variable& a_var)
	{
		using raw_type_t = RE::BSScript::TypeInfo::RawType;

		switch (a_var.GetType().GetRawType()) {
			case raw_type_t::kString: {
				const auto value = RE::BSScript::get<RE::BSFixedString>(a_var);
				AddString(value);
				break;
			}
			case raw_type_t::kStruct: {
				const auto value = RE::BSScript::get<RE::BSScript::Struct>(a_var);
				if (!value) {
					AddString(RE::BSFixedString());
					break;
				}

				const auto lock = RE::BSAutoLock{ value->structLock };

				const auto& typeInfo = value->type;
				if (!typeInfo) {
					AddString(RE::BSFixedString());
					break;
				}

				const auto& typeName = typeInfo->name;
				AddString(typeName);

				for (const auto& [name, index] : typeInfo->varNameIndexMap) {
					AddString(name);

					const auto& var = value->variables[index];
					AddVar(var);
				}
				break;
			}
			case raw_type_t::kVar: {
				const auto* value = RE::BSScript::get<RE::BSScript::Variable>(a_var);
				if (!value) {
					return false;
				}

				AddVar(*value);
				break;
			}
			case raw_type_t::kArrayString:
			case raw_type_t::kArrayStruct:
			case raw_type_t::kArrayVar: {
				const auto value = RE::BSScript::get<RE::BSScript::Array>(a_var);
				if (!value) {
					return false;
				}

				const auto lock = RE::BSAutoLock{ value->elementsLock };

				for (const auto& element : value->elements) {
					AddVar(element);
				}
				break;
			}
			default: {
				return false;
			}
		}

		return true;
	}

	void Clear()
	{
		Strings.clear();
		Indexes.clear();
		LastIndex = 0;
	}
}
