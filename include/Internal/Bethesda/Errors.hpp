#pragma once

namespace Internal::Errors
{
	inline constexpr auto IO_FLAGS = std::ios_base::badbit | std::ios_base::failbit;

	inline constexpr auto OUT_OF_SANDBOX = "The specified path is outside the sandbox"sv;
	inline constexpr auto OUT_OF_SANDBOX_OLD_PATH = "The specified old path is outside the sandbox"sv;
	inline constexpr auto OUT_OF_SANDBOX_NEW_PATH = "The specified new path is outside the sandbox"sv;

	inline constexpr auto SCRIPT_NAME_NOT_FOUND = "The script name \"{}\" does not exist"sv;
	inline constexpr auto STRUCT_NAME_NOT_FOUND = "The struct name \"{}\" does not exist"sv;

	inline constexpr auto SCRIPT_OBJECT_NULL = "The script object cannot be none"sv;
	inline constexpr auto STRUCT_NULL = "The struct cannot be none"sv;

	inline constexpr auto ACTIVATOR_NULL = "The activator cannot be none"sv;
	inline constexpr auto ACTOR_NONE = "The actor cannot be none"sv;
	inline constexpr auto AIM_MODEL_NULL = "The aim model cannot be none"sv;
	inline constexpr auto AMMO_NULL = "The ammo cannot be none"sv;
	inline constexpr auto BOOK_NULL = "The book cannot be none"sv;
	inline constexpr auto CELL_NULL = "The cell cannot be none"sv;
	inline constexpr auto COMPONENT_NULL = "The component cannot be none"sv;
	inline constexpr auto CONTAINER_NULL = "The container cannot be none"sv;
	inline constexpr auto DOOR_NULL = "The door cannot be none"sv;
	inline constexpr auto ENCHANTMENT_NULL = "The enchantment cannot be none"sv;
	inline constexpr auto ENCOUNTER_ZONE_NULL = "The encounter zone cannot be none"sv;
	inline constexpr auto EXPLOSION_NULL = "The explosion cannot be none"sv;
	inline constexpr auto FACTION_NULL = "The faction cannot be none"sv;
	inline constexpr auto FLORA_NULL = "The flora cannot be none"sv;
	inline constexpr auto FORM_LIST_NULL = "The form list cannot be none"sv;
	inline constexpr auto FORM_NULL = "The form cannot be none"sv;
	inline constexpr auto HOLOTAPE_NULL = "The holotape cannot be none"sv;
	inline constexpr auto KEYWORD_NULL = "The keyword cannot be none"sv;
	inline constexpr auto MAGIC_EFFECT_NULL = "The magic effect cannot be none"sv;
	inline constexpr auto MESSAGE_NULL = "The message cannot be none"sv;
	inline constexpr auto MISC_OBJECT_NULL = "The misc object cannot be none"sv;
	inline constexpr auto MOVEMENT_TYPE_NULL = "The movement type cannot be none"sv;
	inline constexpr auto OBJECT_REFERENCE_NULL = "The object reference cannot be none"sv;
	inline constexpr auto OUTFIT_NULL = "The outfit cannot be none"sv;
	inline constexpr auto PERK_NULL = "The perk cannot be none"sv;
	inline constexpr auto POTION_NULL = "The potion cannot be none"sv;
	inline constexpr auto PROJECTILE_NULL = "The projectile cannot be none"sv;
	inline constexpr auto SOUND_NULL = "The sound cannot be none"sv;
	inline constexpr auto SPELL_NULL = "The spell cannot be none"sv;
	inline constexpr auto WORLD_SPACE_NULL = "The world space cannot be none"sv;

	inline constexpr auto START_INDEX_NEGATIVE = "The start index cannot be negative"sv;
	inline constexpr auto COUNT_NEGATIVE = "The count cannot be negative"sv;
	inline constexpr auto TOTAL_SIZE_NEGATIVE = "The total size cannot be negative"sv;
	inline constexpr auto MINIMUM_GREATER_THAN_MAXIMUM = "The minimum value cannot be greater than the maximum one"sv;

	inline constexpr auto* TYPE_ID_OUT_OF_RANGE = "The type ID {} is out of range ({} - {})";
	inline constexpr auto* COUNT_OUT_OF_RANGE = "The count {} is out of range ({} - {})";

	inline constexpr auto* INDEX_OUT_OF_RANGE = "The index {} is out of range ({} - {})";
	inline constexpr auto* START_INDEX_OUT_OF_RANGE = "The start index {} is out of range ({} - {})";
	inline constexpr auto* ENTRY_INDEX_OUT_OF_RANGE = "The entry index {} is out of range ({} - {})";
	inline constexpr auto* VALUE_INDEX_OUT_OF_RANGE = "The value index {} is out of range ({} - {})";
};
