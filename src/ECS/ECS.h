#pragma once

#include "Component.h"
#include "Entity.h"
#include "System.h"
#include <array>
#include <memory>
#include <vector>

template <size_t ComponentCount, size_t SystemCount>
class ECS {
public:
    // ------------------- Entity -------------------
    EntityID create_entity()
    {
        return m_entity_container.create();
    }

    void remove_entity(EntityID entity_id)
    {
        m_entity_container.remove(entity_id);
    }

    template <typename ComponentType>
    bool entity_has_component(EntityID entity_id)
    {
        return m_entity_container.entity_components().at(entity_id)[ComponentType::ID];
    }
    // ----------------------------------------------

    // ------------------- Component -------------------
    template <typename ComponentType>
    void register_component()
    {
        m_component_containers[ComponentType::ID] = std::make_unique<ComponentContainer<ComponentType, ComponentCount, SystemCount>>(m_entity_container.entity_components());
    }

    template <typename ComponentType, typename... Args>
    void add_component(EntityID entity_id, Args&&... args)
    {
        get_component_container<ComponentType>().add_component(entity_id, std::forward<Args>(args)...);
        const auto& component_bitset = m_entity_container.entity_components().at(entity_id);
        for (auto& system : m_systems) {
            auto system_ptr = static_cast<System<ComponentCount, SystemCount>*>(system.get());
            system_ptr->on_entity_updated(entity_id, component_bitset);
        }
    }

    template <typename ComponentType>
    void remove_component(EntityID entity_id)
    {
        get_component_container<ComponentType>().remove_component(entity_id);
        const auto& component_bitset = m_entity_container.entity_components().at(entity_id);
        for (auto& system : m_systems) {
            auto system_ptr = static_cast<System<ComponentCount, SystemCount>*>(system.get());
            system_ptr->on_entity_updated(entity_id, component_bitset);
        }
    }

    template <typename ComponentType>
    ComponentType& get_component(EntityID entity_id)
    {
        return get_component_container<ComponentType>().get(entity_id);
    }
    // -------------------------------------------------

    // ------------------- System -------------------
    template <typename System, typename... Args>
    System* create_system(Args&&... args)
    {
        m_systems.push_back(std::make_unique<System>(this, std::forward<Args>(args)...));
        return static_cast<System*>(m_systems.back().get());
    }
    // ----------------------------------------------

    void update_systems()
    {
        for (auto& system : m_systems) {
            system->update();
        }
    }

private:
    template <typename ComponentType>
    auto& get_component_container()
    {
        return *static_cast<ComponentContainer<ComponentType, ComponentCount, SystemCount>*>(m_component_containers[ComponentType::ID].get());
    }

private:
    EntityContainer<ComponentCount, SystemCount> m_entity_container;
    std::array<std::unique_ptr<ComponentContainerBase>, ComponentCount> m_component_containers;
    std::vector<std::unique_ptr<BaseSystem>> m_systems;
};