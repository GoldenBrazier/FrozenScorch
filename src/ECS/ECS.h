#pragma once

#include "Component.h"
#include "Entity.h"
#include "Event.h"
#include "System.h"
#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

template <size_t ComponentCount, size_t SystemCount>
class ECS {
public:
    // ------------------- Entity -------------------
    EntityID create_entity(const std::string& name = "")
    {
        return m_entity_container.create(name);
    }

    void remove_entity(EntityID entity_id)
    {
        m_entity_container.remove(entity_id);
    }

    inline size_t entity_count()
    {
        return m_entity_container.count();
    }

    inline const auto& entity_name(EntityID entity_id) const
    {
        return m_entity_container.entity_name(entity_id);
    }

    inline bool has_entity(EntityID entity_id) const
    {
        return m_entity_container.has_entity(entity_id);
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
        auto system_ptr = static_cast<System*>(m_systems.back().get());
        for (int entity_id = 0; entity_id < entity_count(); entity_id++) {
            if (!has_entity(entity_id)) {
                continue;
            }
            const auto& component_bitset = m_entity_container.entity_components().at(entity_id);
            system_ptr->on_entity_updated(entity_id, component_bitset);
        }
        return system_ptr;
    }

    void update_systems()
    {
        for (auto& system : m_systems) {
            system->update();
        }
    }
    // ----------------------------------------------

    // ------------------- Events -------------------
    template <typename Event>
    void subscribe_for_events(std::function<void(std::unique_ptr<BaseEvent>)> callback)
    {
        m_event_callbacks[EventEnumerator<Event>::ID].push_back(callback);
    }

    template <typename EventT, typename... Args>
    void post_event(Args&&... args)
    {
        m_event_queue.push_back(std::make_unique<EventT>(std::forward<Args>(args)...));
    }

    void dispatch_events()
    {
        std::vector<std::unique_ptr<BaseEvent>> events_to_dispatch(std::move(m_event_queue));
        m_event_queue.clear();
        for (auto& event_ptr : events_to_dispatch) {
            for (const auto& callback : m_event_callbacks[event_ptr->id()]) {
                callback(std::move(event_ptr));
            }
        }
    }
    // ----------------------------------------------

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
    std::vector<std::unique_ptr<BaseEvent>> m_event_queue;
    std::unordered_map<size_t, std::vector<std::function<void(std::unique_ptr<BaseEvent>)>>> m_event_callbacks;
};