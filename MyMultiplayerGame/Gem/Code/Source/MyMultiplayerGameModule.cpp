/*
 * Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <Components/ExampleFilteredEntityComponent.h>
#include <Components//NetworkPrefabSpawnerComponent.h>
#include <Source/AutoGen/AutoComponentTypes.h>

#include "MyMultiplayerGameSystemComponent.h"

namespace MyMultiplayerGame
{
    class MyMultiplayerGameModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(MyMultiplayerGameModule, "{17D53724-248C-490C-B521-CC853B442900}", AZ::Module);
        AZ_CLASS_ALLOCATOR(MyMultiplayerGameModule, AZ::SystemAllocator, 0);

        MyMultiplayerGameModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyMultiplayerGameSystemComponent::CreateDescriptor(),
                ExampleFilteredEntityComponent::CreateDescriptor(),
                NetworkPrefabSpawnerComponent::CreateDescriptor(),
            });

            CreateComponentDescriptors(m_descriptors);
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyMultiplayerGameSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(Gem_MyMultiplayerGame, MyMultiplayerGame::MyMultiplayerGameModule)
