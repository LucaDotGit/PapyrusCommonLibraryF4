#include "Internal/Events/Handlers/ObjectHitHandler.hpp"

#include "Internal/Events/Sources/ObjectHitSource.hpp"

namespace Internal::Events
{
	ObjectHitHandler::ObjectHitHandler(const ScriptReceivers::ScriptReceiver& a_receiver,
		const std::vector<const RE::BSScript::Variable*>& a_includedSources,
		const std::vector<const RE::BSScript::Variable*>& a_excludedSources,
		const std::vector<const RE::BSScript::Variable*>& a_includedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_excludedTargets,
		const std::vector<const RE::BSScript::Variable*>& a_includedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_excludedObjects,
		const std::vector<const RE::BSScript::Variable*>& a_includedProjectiles,
		const std::vector<const RE::BSScript::Variable*>& a_excludedProjectiles,
		const std::vector<RE::BSFixedString>& a_includedMaterialNames,
		const std::vector<RE::BSFixedString>& a_excludedMaterialNames,
		RE::HitData::Flags a_includedFlags,
		RE::HitData::Flags a_excludedFlags) :
		IEventHandler(a_receiver),
		_sourceFilter{ a_includedSources, a_excludedSources },
		_targetFilter{ a_includedTargets, a_excludedTargets },
		_objectFilter{ a_includedObjects, a_excludedObjects },
		_projectileFilter{ a_includedProjectiles, a_excludedProjectiles },
		_includedMaterialNames{ a_includedMaterialNames.begin(), a_includedMaterialNames.end() },
		_excludedMaterialNames{ a_excludedMaterialNames.begin(), a_excludedMaterialNames.end() },
		_includedFlags(a_includedFlags),
		_excludedFlags(a_excludedFlags)
	{
		Register();
	}

	ObjectHitHandler::~ObjectHitHandler()
	{
		Unregister();
	}

	RE::BSEventNotifyControl ObjectHitHandler::ProcessEvent(const RE::TESHitEvent& a_event, RE::BSTEventSource<RE::TESHitEvent>*)
	{
		if (!IsDispatchable()) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* sourceRef = a_event.cause.get();
		const auto* targetRef = a_event.target.get();
		const auto* object = RE::TESForm::GetFormByID(a_event.sourceFormID);

		const auto* projectileRef = a_event.hitData.sourceRef.get().get();
		const auto* projectile = RE::TESForm::GetFormByID<RE::BGSProjectile>(a_event.projectileFormID);
		const auto& materialName = a_event.material;

		if (!_sourceFilter.Filter(sourceRef) ||
			!_targetFilter.Filter(targetRef) ||
			!_objectFilter.Filter(object) ||
			!(projectileRef ? _projectileFilter.Filter(projectileRef) : _projectileFilter.Filter(projectile)) ||
			!VarFilter::FilterByStrings(materialName, _includedMaterialNames, _excludedMaterialNames) ||
			!VarFilter::FilterByFlags(a_event.hitData.flags.get(), _includedFlags, _excludedFlags, RE::HitData::Flags::kNone)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto* source = sourceRef ? sourceRef->GetBaseObject() : nullptr;
		const auto* target = targetRef ? targetRef->GetBaseObject() : nullptr;

		auto args = EventArgs();
		args.insert("SourceRef"sv, sourceRef);
		args.insert("TargetRef"sv, targetRef);
		args.insert("Source"sv, source);
		args.insert("Target"sv, target);
		args.insert("SourceObject"sv, object);
		args.insert("SourceProjectileRef"sv, projectileRef);
		args.insert("SourceProjectile"sv, projectile);
		args.insert("MaterialName"sv, materialName);

		auto data = ObjectHitData(nullptr);
		if (a_event.usesHitData) {
			const auto& hitData = a_event.hitData;

			data = ObjectHitData();
			data.insert("Flags"sv, hitData.flags.underlying());
			data.insert("BaseDamage"sv, hitData.healthDamage);
			data.insert("TotalDamage"sv, hitData.totalDamage);
			data.insert("PhysicalDamage"sv, hitData.physicalDamage);
			data.insert("LimbDamage"sv, hitData.targetedLimbDamage);
			data.insert("BlockedDamageMult"sv, hitData.percentBlocked);
			data.insert("ResistedPhysicalDamage"sv, hitData.resistedPhysicalDamage);
			data.insert("ResistedTypedDamage"sv, hitData.resistedTypedDamage);
			data.insert("ReflectedDamage"sv, hitData.reflectedDamage);
			data.insert("SneakAttackMult"sv, hitData.sneakAttackBonus);
			data.insert("CriticalDamageMult"sv, hitData.criticalDamageMult);
			data.insert("BonusHealthDamageMult"sv, hitData.bonusHealthDamageMult);
			data.insert("PushBackMult"sv, hitData.pushBack);
			data.insert("StaggerMagnitude"sv, hitData.staggerMagnitude.underlying());
		}

		args.insert("HitData"sv, std::move(data));

		DispatchCall(std::move(args));
		return RE::BSEventNotifyControl::kContinue;
	}

	void ObjectHitHandler::Register()
	{
		ObjectHitSource::GetEventSource()->RegisterSink(this);
	}

	void ObjectHitHandler::Unregister()
	{
		ObjectHitSource::GetEventSource()->UnregisterSink(this);
	}
}
