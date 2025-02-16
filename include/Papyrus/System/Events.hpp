#pragma once

#include "Internal/Events/Registration.hpp"

namespace System::Events
{
	static constexpr auto SCRIPT_NAME = "System:Events"sv;

	template <::Internal::Events::event_handler_v TEventHandler>
	static bool IsRegisteredImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		const ::Internal::ScriptReceivers::ScriptReceiver& a_receiver)
	{
		if (!a_receiver) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Events::Registration::IsRegistered<TEventHandler>(a_receiver);
	}

	template <::Internal::Events::event_handler_v TEventHandler, typename... Args>
	static bool RegisterImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		const ::Internal::ScriptReceivers::ScriptReceiver& a_receiver,
		Args&&... a_args)
	{
		if (!a_receiver) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Events::Registration::Register<TEventHandler>(a_receiver, std::forward<Args>(a_args)...);
	}

	template <::Internal::Events::event_handler_v TEventHandler>
	static bool UnregisterImpl(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID,
		const ::Internal::ScriptReceivers::ScriptReceiver& a_receiver)
	{
		if (!a_receiver) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Events::Registration::Unregister<TEventHandler>(a_receiver);
	}
}

#include "Events.Actor.hpp"
#include "Events.Misc.hpp"
#include "Events.Object.hpp"
#include "Events.Save.hpp"
#include "Events.UI.hpp"

#include "Internal/Events/Handlers/UserEventHandler.hpp"

namespace System::Events
{
	static bool IsRegisteredForAny(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		if (!a_receiver) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Events::Registration::IsRegisteredForAny(a_receiver);
	}

	static bool UnregisterForAny(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		if (!a_receiver) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return ::Internal::Events::Registration::UnregisterForAny(a_receiver);
	}

	static bool UnregisterForAll(std::monostate,
		RE::BSFixedString a_scriptName)
	{
		return ::Internal::Events::Registration::UnregisterForAll(a_scriptName);
	}

	static bool IsRegisteredForUserEvent(std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		RE::BSFixedString a_eventName)
	{
		const auto handler = ::Internal::Events::Registration::GetHandler<::Internal::Events::UserEventHandler>(a_receiver);
		if (!handler.has_value()) {
			return false;
		}

		if (a_eventName.empty()) {
			return true;
		}

		const auto& userHandler = handler.value();
		return userHandler.get().GetEventName() == a_eventName;
	}

	static bool RegisterForUserEvent(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver,
		RE::BSFixedString a_eventName)
	{
		if (a_eventName.empty()) {
			a_vm.PostError("The event name cannot be empty"sv, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return false;
		}

		return RegisterImpl<::Internal::Events::UserEventHandler>(a_vm, a_stackID, a_receiver, a_eventName);
	}

	static bool UnregisterForUserEvent(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		::Internal::ScriptReceivers::ScriptReceiver a_receiver)
	{
		return UnregisterImpl<::Internal::Events::UserEventHandler>(a_vm, a_stackID, a_receiver);
	}

	static void SendUserEvent(std::monostate,
		RE::BSFixedString a_eventName,
		std::vector<const RE::BSScript::Variable*> a_args)
	{
		auto args = std::vector<RE::BSScript::Variable>();
		args.reserve(a_args.size() + 1);

		auto eventName = RE::BSScript::Variable();
		eventName = a_eventName;
		args.push_back(std::move(eventName));

		for (const auto* arg : a_args) {
			auto value = ::Internal::Copier::Copy(arg);
			args.push_back(std::move(value));
		}

		auto event = ::Internal::Events::UserEvent{ std::move(a_eventName), std::move(args) };
		::Internal::Events::UserEventSource::GetEventSource()->Notify(event);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForAny);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForAny);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForAll);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsRegisteredForUserEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RegisterForUserEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, UnregisterForUserEvent);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SendUserEvent);

		return Save::RegisterFunctions(a_vm) &&
			   Actor::RegisterFunctions(a_vm) &&
			   Object::RegisterFunctions(a_vm) &&
			   UI::RegisterFunctions(a_vm) &&
			   Misc::RegisterFunctions(a_vm);
	}
}
