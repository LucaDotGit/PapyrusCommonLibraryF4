#pragma once

#include <SimpleIni.h>
#include <boost/regex.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "Internal/Bethesda/Errors.hpp"

#include "Internal/Bethesda/Comparer.hpp"
#include "Internal/Bethesda/Copier.hpp"
#include "Internal/Bethesda/Types.hpp"
#include "Internal/Bethesda/VarFilter.hpp"

#include "Internal/IO/IOMutex.hpp"
#include "Internal/IO/Sandbox.hpp"

#include "Internal/Structs/Colors.hpp"
#include "Internal/Structs/MagicItem.hpp"
#include "Internal/Structs/Pairs.hpp"
#include "Internal/Structs/ScriptReceivers.hpp"
#include "Internal/Structs/Vectors.hpp"
#include "Internal/Structs/Versions.hpp"

#define TO_STRING(a_value) #a_value##s
#define TO_STRING_VIEW(a_value) #a_value##sv

#define BIND_METHOD(a_vm, a_scriptName, a_method, ...) \
	a_vm->BindNativeMethod(a_scriptName, TO_STRING_VIEW(a_method), a_method __VA_OPT__(, ) __VA_ARGS__)
#define BIND_METHOD_SAFE(a_vm, a_scriptName, a_method) \
	BIND_METHOD(a_vm, a_scriptName, a_method, true)
