// This file is part of the Godot Orchestrator project.
//
// Copyright (c) 2023-present Vahera Studios LLC and its contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef ORCHESTRATOR_GRAPH_ACTION_MENU_ITEM_FILTER_H
#define ORCHESTRATOR_GRAPH_ACTION_MENU_ITEM_FILTER_H

#include "action_menu_item.h"
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

/// Forward declarations
class OrchestratorGraphEdit;
class OrchestratorGraphNodePin;

/// An information object passed around to provide details about the actions that should
/// be generated by the action menu subsystem.
struct OrchestratorGraphActionContext
{
    /// OrchestratorGraphEdit references to obtain actions for.
    OrchestratorGraphEdit* graph{ nullptr };

    /// List of OrchestratorGraphNodePin references to obtain actions for.
    List<OrchestratorGraphNodePin*> pins;
};

/// An action filter object, passed to the EditorActionMenu to filter all available actions
/// based on the search criteria contained within.
struct OrchestratorGraphActionFilter
{
    enum Flags
    {
        Filter_NoFlags              = 1 << 0,
        Filter_RejectProperties     = 1 << 1,
        Filter_RejectVirtualMethods = 1 << 2,
        Filter_RejectMethods        = 1 << 3,
        Filter_RejectEvents         = 1 << 4,
        Filter_RejectSignals        = 1 << 5,
        Filter_RejectVariables      = 1 << 6,
        Filter_RejectScriptNodes    = 1 << 7,
        Filter_OverridesOnly        = Filter_RejectProperties | Filter_RejectMethods | Filter_RejectSignals
                               | Filter_RejectVariables | Filter_RejectScriptNodes
    };

    /// The search flags
    Flags flags{ Filter_NoFlags };

    /// Whether the filter should be context-sensitive or not, defaults to true.
    bool context_sensitive{ true };

    /// The action context the filter is created for
    OrchestratorGraphActionContext context;

    /// List of keywords entered by the user.
    Vector<String> keywords;

    /// A list of class names that you want members for. If an action would produce a
    /// node with a target pin and that pin is incompatible with one of these classes,
    /// then the action is filtered out.
    Vector<StringName> target_classes;

    /// The target object to expressly get context details about
    Object* target_object;
};

#endif  // ORCHESTRATOR_GRAPH_ACTION_MENU_ITEM_FILTER_H
