#include "Internal/Patches/EditorIDCache.hpp"

#include "Internal/Config/Config.hpp"

namespace Internal::Patches::EditorIDCache
{
	static constexpr auto RESERVED_SIZE = 0x20000ui32;

	void Install() noexcept
	{
		EditorIDs.reserve(RESERVED_SIZE);

		// Patch<RE::TESForm>::Install();
		// Patch<RE::TESObject>::Install();
		// Patch<RE::TESBoundObject>::Install();
		// Patch<RE::MagicItem>::Install();
		// Patch<RE::TESBoundAnimObject>::Install();
		// Patch<RE::TESActorBase>::Install();
		// Patch<RE::BGSStoryManagerTreeForm>::Install();
		// Patch<RE::BGSStoryManagerNodeBase>::Install();
		Patch<RE::BGSKeyword>::Install();
		Patch<RE::BGSLocationRefType>::Install();
		Patch<RE::BGSAction>::Install();
		Patch<RE::BGSTransform>::Install();
		Patch<RE::BGSComponent>::Install();
		Patch<RE::BGSTextureSet>::Install();
		// Patch<RE::BGSMenuIcon>::Install(); // Unused
		Patch<RE::TESGlobal>::Install();
		Patch<RE::BGSDamageType>::Install();
		Patch<RE::TESClass>::Install();
		Patch<RE::TESFaction>::Install();
		Patch<RE::BGSHeadPart>::Install();
		Patch<RE::TESEyes>::Install();
		Patch<RE::TESRace>::Install();
		Patch<RE::TESSound>::Install();
		Patch<RE::BGSAcousticSpace>::Install();
		Patch<RE::EffectSetting>::Install();
		// Patch<RE::Script>::Install(); // Not needed
		Patch<RE::TESLandTexture>::Install();
		Patch<RE::EnchantmentItem>::Install();
		Patch<RE::SpellItem>::Install();
		// Patch<RE::ScrollItem>::Install(); // Unused
		Patch<RE::TESObjectACTI>::Install();
		Patch<RE::BGSTalkingActivator>::Install();
		Patch<RE::TESObjectARMO>::Install();
		Patch<RE::TESObjectBOOK>::Install();
		Patch<RE::TESObjectCONT>::Install();
		Patch<RE::TESObjectDOOR>::Install();
		// Patch<RE::IngredientItem>::Install(); // Unused
		Patch<RE::TESObjectLIGH>::Install();
		Patch<RE::TESObjectMISC>::Install();
		Patch<RE::TESObjectSTAT>::Install();
		Patch<RE::BGSStaticCollection>::Install();
		Patch<RE::BGSMovableStatic>::Install();
		Patch<RE::TESGrass>::Install();
		// Patch<RE::TESObjectTREE>::Install(); // Unused
		Patch<RE::TESFlora>::Install();
		Patch<RE::TESFurniture>::Install();
		Patch<RE::TESObjectWEAP>::Install();
		Patch<RE::TESAmmo>::Install();
		Patch<RE::TESNPC>::Install();
		Patch<RE::TESLevCharacter>::Install();
		Patch<RE::TESKey>::Install();
		Patch<RE::AlchemyItem>::Install();
		Patch<RE::BGSIdleMarker>::Install();
		Patch<RE::BGSNote>::Install();
		Patch<RE::BGSProjectile>::Install();
		Patch<RE::BGSHazard>::Install();
		Patch<RE::BGSBendableSpline>::Install();
		// Patch<RE::TESSoulGem>::Install(); // Unused
		Patch<RE::BGSTerminal>::Install();
		Patch<RE::TESLevItem>::Install();
		Patch<RE::TESWeather>::Install();
		Patch<RE::TESClimate>::Install();
		Patch<RE::BGSShaderParticleGeometryData>::Install();
		Patch<RE::BGSReferenceEffect>::Install();
		Patch<RE::TESRegion>::Install();
		// Patch<RE::NavMeshInfoMap>::Install(); // Has no EditorIDs
		Patch<RE::TESObjectCELL>::Install();
		Patch<RE::TESObjectREFR>::Install();
		Patch<RE::Explosion>::Install();
		Patch<RE::Projectile>::Install();
		Patch<RE::Actor>::Install();
		Patch<RE::PlayerCharacter>::Install();
		Patch<RE::MissileProjectile>::Install();
		Patch<RE::ArrowProjectile>::Install();
		Patch<RE::GrenadeProjectile>::Install();
		Patch<RE::BeamProjectile>::Install();
		Patch<RE::FlameProjectile>::Install();
		Patch<RE::ConeProjectile>::Install();
		Patch<RE::BarrierProjectile>::Install();
		Patch<RE::Hazard>::Install();
		Patch<RE::TESWorldSpace>::Install();
		// Patch<RE::TESObjectLAND>::Install(); // Has no EditorIDs
		// Patch<RE::NavMesh>::Install(); // Has no EditorIDs
		Patch<RE::TESTopic>::Install();
		Patch<RE::TESTopicInfo>::Install();
		Patch<RE::TESQuest>::Install();
		Patch<RE::TESIdleForm>::Install();
		Patch<RE::TESPackage>::Install();
		Patch<RE::AlarmPackage>::Install();
		Patch<RE::DialoguePackage>::Install();
		Patch<RE::FleePackage>::Install();
		Patch<RE::SpectatorPackage>::Install();
		Patch<RE::TrespassPackage>::Install();
		Patch<RE::TESCombatStyle>::Install();
		Patch<RE::TESLoadScreen>::Install();
		Patch<RE::TESLevSpell>::Install();
		Patch<RE::TESObjectANIO>::Install();
		Patch<RE::TESWaterForm>::Install();
		Patch<RE::TESEffectShader>::Install();
		Patch<RE::BGSExplosion>::Install();
		Patch<RE::BGSDebris>::Install();
		Patch<RE::TESImageSpace>::Install();
		Patch<RE::TESImageSpaceModifier>::Install();
		Patch<RE::BGSListForm>::Install();
		Patch<RE::BGSPerk>::Install();
		Patch<RE::BGSBodyPartData>::Install();
		Patch<RE::BGSAddonNode>::Install();
		Patch<RE::ActorValueInfo>::Install();
		Patch<RE::BGSCameraShot>::Install();
		Patch<RE::BGSCameraPath>::Install();
		Patch<RE::BGSVoiceType>::Install();
		Patch<RE::BGSMaterialType>::Install();
		Patch<RE::BGSImpactData>::Install();
		Patch<RE::BGSImpactDataSet>::Install();
		Patch<RE::TESObjectARMA>::Install();
		Patch<RE::BGSEncounterZone>::Install();
		Patch<RE::BGSLocation>::Install();
		Patch<RE::BGSMessage>::Install();
		// Patch<RE::BGSDefaultObjectManager>::Install(); // Has no EditorIDs
		Patch<RE::BGSDefaultObject>::Install();
		Patch<RE::BGSLightingTemplate>::Install();
		Patch<RE::BGSMusicType>::Install();
		Patch<RE::BGSFootstep>::Install();
		Patch<RE::BGSFootstepSet>::Install();
		// Patch<RE::BGSStoryManagerBranchNode>::Install(); // Not needed
		// Patch<RE::BGSStoryManagerQuestNode>::Install(); // Not needed
		// Patch<RE::BGSStoryManagerEventNode>::Install(); // Not needed
		Patch<RE::BGSDialogueBranch>::Install();
		Patch<RE::BGSMusicTrackFormWrapper>::Install();
		// Patch<RE::TESWordOfPower>::Install(); // Unused
		// Patch<RE::TESShout>::Install(); // Unused
		Patch<RE::BGSEquipSlot>::Install();
		Patch<RE::BGSRelationship>::Install();
		Patch<RE::BGSScene>::Install();
		Patch<RE::BGSAssociationType>::Install();
		Patch<RE::BGSOutfit>::Install();
		Patch<RE::BGSArtObject>::Install();
		Patch<RE::BGSMaterialObject>::Install();
		Patch<RE::BGSMovementType>::Install();
		Patch<RE::BGSSoundDescriptorForm>::Install();
		Patch<RE::BGSDualCastData>::Install();
		Patch<RE::BGSSoundCategory>::Install();
		Patch<RE::BGSSoundOutput>::Install();
		Patch<RE::BGSCollisionLayer>::Install();
		Patch<RE::BGSColorForm>::Install();
		Patch<RE::BGSReverbParameters>::Install();
		Patch<RE::BGSPackIn>::Install();
		Patch<RE::BGSAimModel>::Install();
		Patch<RE::BGSConstructibleObject>::Install();
		Patch<RE::BGSMod::Attachment::Mod>::Install();
		Patch<RE::BGSMaterialSwap>::Install();
		Patch<RE::BGSZoomData>::Install();
		Patch<RE::BGSInstanceNamingRules>::Install();
		Patch<RE::BGSSoundKeywordMapping>::Install();
		Patch<RE::BGSAudioEffectChain>::Install();
		Patch<RE::BGSAttractionRule>::Install();
		Patch<RE::BGSSoundCategorySnapshot>::Install();
		Patch<RE::BGSSoundTagSet>::Install();
		Patch<RE::BGSLensFlare>::Install();
		Patch<RE::BGSGodRays>::Install();
	}

	const char* GetFormEditorIDImpl(RE::TESForm* a_this)
	{
		const auto&& [_, mutex] = RE::TESForm::GetAllFormsByEditorID();
		const auto lock = RE::BSAutoReadLock{ mutex.get() };

		const auto formIt = EditorIDs.find(a_this->formID);
		return formIt != EditorIDs.end() ? formIt->second.data() : "";
	}

	bool SetFormEditorIDImpl(RE::TESForm* a_this, const char* a_editorID)
	{
		if (!a_editorID || !a_editorID[0]) {
			return false;
		}

		const auto editorID = RE::BSFixedString(a_editorID);
		if (editorID.empty()) {
			return false;
		}

		const auto&& [map, mutex] = RE::TESForm::GetAllFormsByEditorID();
		const auto lock = RE::BSAutoWriteLock{ mutex.get() };

		const auto idIt = map->find(editorID);
		if (idIt != map->end()) {
			if (!Config::LogDuplicateEditorIDs.GetValue()) {
				return false;
			}

			const auto thisFormID = a_this->formID;
			const auto otherFormID = idIt->second->formID;

			if (thisFormID != otherFormID) {
				logger::warn("Duplicate EditorID - Sender: {:08X}, Owner: {:08X}, ID: \"{}\""sv, thisFormID, otherFormID, a_editorID);
			}

			return false;
		}

		const auto formID = a_this->formID;
		const auto formIt = EditorIDs.find(formID);

		if (formIt != EditorIDs.end()) {
			map->erase(formIt->second);
			EditorIDs.erase(formIt);
		}

		map->emplace(editorID, a_this);
		EditorIDs.emplace(formID, editorID);
		return true;
	}
}
