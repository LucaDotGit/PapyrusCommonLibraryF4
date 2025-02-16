#include "Papyrus/Registration.hpp"

#include "Papyrus/System/IO/Directory.hpp"
#include "Papyrus/System/IO/File.hpp"
#include "Papyrus/System/IO/INI.hpp"
#include "Papyrus/System/IO/JSON.hpp"
#include "Papyrus/System/IO/Path.hpp"

#include "Papyrus/System/Activator.hpp"
#include "Papyrus/System/AimModel.hpp"
#include "Papyrus/System/Ammo.hpp"
#include "Papyrus/System/Array.hpp"
#include "Papyrus/System/Assert.hpp"
#include "Papyrus/System/Book.hpp"
#include "Papyrus/System/Boolean.hpp"
#include "Papyrus/System/Cell.hpp"
#include "Papyrus/System/Char.hpp"
#include "Papyrus/System/Component.hpp"
#include "Papyrus/System/Console.hpp"
#include "Papyrus/System/Container.hpp"
#include "Papyrus/System/Door.hpp"
#include "Papyrus/System/Enchantment.hpp"
#include "Papyrus/System/EncounterZone.hpp"
#include "Papyrus/System/Events.hpp"
#include "Papyrus/System/Explosion.hpp"
#include "Papyrus/System/Faction.hpp"
#include "Papyrus/System/Flora.hpp"
#include "Papyrus/System/Form.hpp"
#include "Papyrus/System/FormList.hpp"
#include "Papyrus/System/Game.hpp"
#include "Papyrus/System/Holotape.hpp"
#include "Papyrus/System/Int32.hpp"
#include "Papyrus/System/Internal.hpp"
#include "Papyrus/System/MagicEffect.hpp"
#include "Papyrus/System/Math.hpp"
#include "Papyrus/System/MemVar.hpp"
#include "Papyrus/System/Message.hpp"
#include "Papyrus/System/MiscObject.hpp"
#include "Papyrus/System/MovementType.hpp"
#include "Papyrus/System/NetImmerse.hpp"
#include "Papyrus/System/ObjectReference.hpp"
#include "Papyrus/System/Operator.hpp"
#include "Papyrus/System/Outfit.hpp"
#include "Papyrus/System/Perk.hpp"
#include "Papyrus/System/Potion.hpp"
#include "Papyrus/System/Projectile.hpp"
#include "Papyrus/System/Regex.hpp"
#include "Papyrus/System/SaveVar.hpp"
#include "Papyrus/System/ScriptObject.hpp"
#include "Papyrus/System/Single.hpp"
#include "Papyrus/System/Spell.hpp"
#include "Papyrus/System/Strings.hpp"
#include "Papyrus/System/Structure.hpp"
#include "Papyrus/System/Translations.hpp"
#include "Papyrus/System/UInt32.hpp"
#include "Papyrus/System/WorldSpace.hpp"

namespace System
{
	static bool RegisterTypes(RE::BSScript::IVirtualMachine* a_vm)
	{
		logger::debug("Registering papyrus types"sv);

#define REGISTER_TYPE(a_type, a_name) a_vm->RegisterObjectType(std::to_underlying(a_type::FORMTYPE), a_name)

		return REGISTER_TYPE(RE::BGSAimModel, "AimModel") &&
			   REGISTER_TYPE(RE::BGSArtObject, "ArtObject") &&
			   REGISTER_TYPE(RE::TESClimate, "Climate") &&
			   REGISTER_TYPE(RE::BGSCollisionLayer, "CollisionLayer") &&
			   REGISTER_TYPE(RE::BGSLightingTemplate, "LightingTemplate") &&
			   REGISTER_TYPE(RE::BGSMovementType, "MovementType");
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		logger::debug("Registering papyrus functions"sv);

		return IO::Directory::RegisterFunctions(a_vm) &&
			   IO::File::RegisterFunctions(a_vm) &&
			   IO::INI::RegisterFunctions(a_vm) &&
			   IO::JSON::RegisterFunctions(a_vm) &&
			   IO::Path::RegisterFunctions(a_vm) &&

			   Activator::RegisterFunctions(a_vm) &&
			   AimModel::RegisterFunctions(a_vm) &&
			   Ammo::RegisterFunctions(a_vm) &&
			   Array::RegisterFunctions(a_vm) &&
			   Assert::RegisterFunctions(a_vm) &&
			   Book::RegisterFunctions(a_vm) &&
			   Boolean::RegisterFunctions(a_vm) &&
			   Cell::RegisterFunctions(a_vm) &&
			   Char::RegisterFunctions(a_vm) &&
			   Component::RegisterFunctions(a_vm) &&
			   Console::RegisterFunctions(a_vm) &&
			   Container::RegisterFunctions(a_vm) &&
			   Door::RegisterFunctions(a_vm) &&
			   Enchantment::RegisterFunctions(a_vm) &&
			   EncounterZone::RegisterFunctions(a_vm) &&
			   Explosion::RegisterFunctions(a_vm) &&
			   Faction::RegisterFunctions(a_vm) &&
			   Flora::RegisterFunctions(a_vm) &&
			   Form::RegisterFunctions(a_vm) &&
			   FormList::RegisterFunctions(a_vm) &&
			   Events::RegisterFunctions(a_vm) &&
			   Game::RegisterFunctions(a_vm) &&
			   Holotape::RegisterFunctions(a_vm) &&
			   Int32::RegisterFunctions(a_vm) &&
			   Internal::RegisterFunctions(a_vm) &&
			   MagicEffect::RegisterFunctions(a_vm) &&
			   Math::RegisterFunctions(a_vm) &&
			   MemVar::RegisterFunctions(a_vm) &&
			   Message::RegisterFunctions(a_vm) &&
			   MiscObject::RegisterFunctions(a_vm) &&
			   MovementType::RegisterFunctions(a_vm) &&
			   NetImmerse::RegisterFunctions(a_vm) &&
			   ObjectReference::RegisterFunctions(a_vm) &&
			   Operator::RegisterFunctions(a_vm) &&
			   Outfit::RegisterFunctions(a_vm) &&
			   Perk::RegisterFunctions(a_vm) &&
			   Potion::RegisterFunctions(a_vm) &&
			   Projectile::RegisterFunctions(a_vm) &&
			   Regex::RegisterFunctions(a_vm) &&
			   SaveVar::RegisterFunctions(a_vm) &&
			   ScriptObject::RegisterFunctions(a_vm) &&
			   Single::RegisterFunctions(a_vm) &&
			   Spell::RegisterFunctions(a_vm) &&
			   Strings::RegisterFunctions(a_vm) &&
			   Structure::RegisterFunctions(a_vm) &&
			   Translations::RegisterFunctions(a_vm) &&
			   UInt32::RegisterFunctions(a_vm) &&
			   WorldSpace::RegisterFunctions(a_vm);
	}

	bool Callback(RE::BSScript::IVirtualMachine* a_vm)
	{
		if (!RegisterTypes(a_vm)) {
			logger::error("Failed to register papyrus types"sv);
			assert(false);
			return false;
		}

		if (!RegisterFunctions(a_vm)) {
			logger::error("Failed to register papyrus functions"sv);
			assert(false);
			return false;
		}

		return true;
	}
}
