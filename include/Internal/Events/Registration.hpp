#pragma once

#include "Internal/Events/IEventHandler.hpp"

namespace Internal::Events
{
	template <class T>
	concept event_handler_v = std::derived_from<T, IEventHandler>;

	namespace Registration
	{
		static auto Mutex = std::shared_mutex();
		static auto Handlers = Types::unordered_string_map<RE::BSFixedString,
			Types::unordered_string_map<RE::BSFixedString, std::unique_ptr<const IEventHandler>>>();

		[[nodiscard]] bool IsRegisteredForAny(const ScriptReceivers::ScriptReceiver& a_receiver);
		bool UnregisterForAny(const ScriptReceivers::ScriptReceiver& a_receiver);
		bool UnregisterForAll(const RE::BSFixedString& a_scriptName);

		template <event_handler_v TEventHandler>
		[[nodiscard]] static bool TypeEquals(const IEventHandler& a_eventHandler)
		{
			return typeid(a_eventHandler) == typeid(TEventHandler);
		}

		template <event_handler_v TEventHandler>
		[[nodiscard]] std::optional<std::reference_wrapper<const TEventHandler>> GetHandler(const ScriptReceivers::ScriptReceiver& a_receiver)
		{
			if (!a_receiver) {
				return std::nullopt;
			}

			const auto lock = std::shared_lock{ Mutex };

			const auto scriptIt = Handlers.find(ScriptReceivers::GetScriptName(a_receiver));
			if (scriptIt == Handlers.end()) {
				return std::nullopt;
			}

			const auto functionIt = scriptIt->second.find(ScriptReceivers::GetFunctionName(a_receiver));
			if (functionIt == scriptIt->second.end()) {
				return std::nullopt;
			}

			const auto& eventHandler = *functionIt->second;
			if (!TypeEquals<TEventHandler>(eventHandler)) {
				return std::nullopt;
			}

			return std::ref(reinterpret_cast<const TEventHandler&>(eventHandler));
		}

		template <event_handler_v TEventHandler>
		[[nodiscard]] bool IsRegistered(const ScriptReceivers::ScriptReceiver& a_receiver)
		{
			if (!a_receiver) {
				return false;
			}

			const auto lock = std::shared_lock{ Mutex };

			const auto scriptIt = Handlers.find(ScriptReceivers::GetScriptName(a_receiver));
			if (scriptIt == Handlers.end()) {
				return false;
			}

			const auto& scriptMap = scriptIt->second;
			const auto functionIt = scriptMap.find(ScriptReceivers::GetFunctionName(a_receiver));

			if (functionIt == scriptMap.end()) {
				return false;
			}

			return TypeEquals<TEventHandler>(*functionIt->second);
		}

		template <event_handler_v TEventHandler, typename... Args>
		bool Register(const ScriptReceivers::ScriptReceiver& a_receiver, Args&&... a_args)
		{
			if (!a_receiver) {
				return false;
			}

			const auto lock = std::unique_lock{ Mutex };

			const auto&& [scriptName, functionName] = ScriptReceivers::GetNames(a_receiver);
			const auto&& [scriptIt, hasInserted] = Handlers.try_emplace(scriptName);

			if (!hasInserted && scriptIt->second.contains(functionName)) {
				return false;
			}

			scriptIt->second[functionName] = std::make_unique<TEventHandler>(a_receiver, std::forward<Args>(a_args)...);
			return true;
		}

		template <event_handler_v TEventHandler>
		bool Unregister(const ScriptReceivers::ScriptReceiver& a_receiver)
		{
			if (!a_receiver) {
				return false;
			}

			const auto lock = std::unique_lock{ Mutex };

			const auto scriptIt = Handlers.find(ScriptReceivers::GetScriptName(a_receiver));
			if (scriptIt == Handlers.end()) {
				return false;
			}

			auto& scriptMap = scriptIt->second;
			const auto functionIt = scriptMap.find(ScriptReceivers::GetFunctionName(a_receiver));

			if (functionIt == scriptMap.end() || !TypeEquals<TEventHandler>(*functionIt->second)) {
				return false;
			}

			scriptMap.erase(functionIt);
			if (scriptMap.empty()) {
				Handlers.erase(scriptIt);
			}

			return true;
		}
	}
}
