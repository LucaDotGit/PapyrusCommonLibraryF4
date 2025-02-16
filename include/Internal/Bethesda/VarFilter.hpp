#pragma once

namespace Internal
{
	class VarFilter final
	{
	public:
		struct Entry final
		{
			std::unordered_set<RE::ENUM_FORMTYPE> formTypes;
			Types::unordered_string_set<RE::BSFixedString> modNames;
			Types::unordered_form_set<const RE::TESForm*> forms;
		};

	public:
		VarFilter(
			const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
			const std::vector<const RE::BSScript::Variable*>& a_excludedObjects);

		~VarFilter() noexcept = default;

	public:
		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] const Entry& GetIncludedEntries() const noexcept;
		[[nodiscard]] const Entry& GetExcludedEntries() const noexcept;

		[[nodiscard]] bool Filter(const RE::TESForm* a_form) const;

	public:
		[[nodiscard]] static bool FilterByFormTypes(const RE::TESForm* a_form,
			const std::unordered_set<RE::ENUM_FORMTYPE>& a_includedFormTypes,
			const std::unordered_set<RE::ENUM_FORMTYPE>& a_excludedFormTypes);

		template <class T>
		[[nodiscard]] static bool FilterByT(T a_value,
			const std::unordered_set<T>& a_includedObjects,
			const std::unordered_set<T>& a_excludedObjects)
		{
			return a_includedObjects.empty() && a_excludedObjects.empty() ||
				   a_includedObjects.contains(a_value) && !a_excludedObjects.contains(a_value);
		}

		template <class T>
			requires std::is_enum_v<T>
		[[nodiscard]] static bool FilterByEnums(T a_value,
			const std::unordered_set<T>& a_includedEnums,
			const std::unordered_set<T>& a_excludedEnums)
		{
			return FilterByT(a_value, a_includedEnums, a_excludedEnums);
		}

		template <class T>
			requires std::is_enum_v<T>
		[[nodiscard]] static bool FilterByFlags(T a_value,
			T a_includedFlags,
			T a_excludedFlags,
			T a_default) noexcept
		{
			if (a_includedFlags == a_default && a_excludedFlags == a_default) {
				return true;
			}

			const auto value = std::to_underlying(a_value);
			return (value & std::to_underlying(a_includedFlags)) != 0 &&
				   (value & std::to_underlying(a_excludedFlags)) == 0;
		}

		template <RE::BSScript::detail::string T>
		[[nodiscard]] static bool FilterByStrings(const T& a_string,
			const Types::unordered_string_set<T>& a_includedStrings,
			const Types::unordered_string_set<T>& a_excludedStrings)
		{
			return a_includedStrings.empty() && a_excludedStrings.empty() ||
				   a_includedStrings.contains(a_string) && !a_excludedStrings.contains(a_string);
		}

		template <RE::BSScript::detail::string T>
		[[nodiscard]] static bool FilterByModNames(const RE::TESForm* a_form,
			const Types::unordered_string_set<T>& a_includedModNames,
			const Types::unordered_string_set<T>& a_excludedModNames)
		{
			if (a_includedModNames.empty() && a_excludedModNames.empty()) {
				return true;
			}

			if (!a_form) {
				return false;
			}

			const auto modFilter = [&](const RE::TESForm* a_filter) {
				if (!a_filter) {
					return false;
				}

				const auto* file = a_filter->GetFile(0);
				if (!file) {
					return false;
				}

				const auto modName = T{ file->filename };
				return FilterByStrings(modName, a_includedModNames, a_excludedModNames);
			};

			if (modFilter(a_form)) {
				return true;
			}

			const auto* ref = a_form->As<RE::TESObjectREFR>();
			if (!ref) {
				return false;
			}

			const auto* baseObject = ref->GetBaseObject();
			if (!baseObject) {
				return false;
			}

			return modFilter(baseObject);
		}

	private:
		const Entry _includedEntries;
		const Entry _excludedEntries;
	};
}
