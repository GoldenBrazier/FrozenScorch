#pragma once

#include "Entity.h"
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace ECS {

template <typename T>
class Component {
public:
    static const size_t ID;
};

inline size_t generateComponentType()
{
    static size_t counter = 0;
    return counter++;
}

template <typename T>
const size_t Component<T>::ID = generateComponentType();

class ComponentContainerBase {
public:
    virtual ~ComponentContainerBase() = default;
};

template <typename ComponentType, size_t ComponentCount, size_t SystemCount>
class ComponentContainer : public ComponentContainerBase {
public:
    explicit ComponentContainer(std::vector<std::bitset<ComponentCount>>& entity_components)
        : m_entity_components(entity_components)
    {
    }

    inline ComponentType& get(EntityID id)
    {
        return m_components[m_entity_id_to_component[id]];
    }

    inline EntityID get_entity_by_component(const ComponentType& component)
    {
        auto index = &component - m_components.begin();
        return m_component_to_entity_id[index];
    }

    template <typename... Args>
    inline ComponentType& add_component(EntityID entity_id, Args&&... args)
    {
        size_t component_index = m_components.size();
        m_components.emplace_back(std::forward<Args>(args)...);

        m_component_to_entity_id[component_index] = entity_id;
        m_entity_id_to_component[entity_id] = component_index;
        m_entity_components[entity_id][ComponentType::ID] = true;

        return m_components[component_index];
    }

    inline void remove_component(EntityID entity_id)
    {
        if (!m_entity_components[entity_id][ComponentType::ID]) {
            return;
        }

        const size_t component_index = m_entity_id_to_component[entity_id];

        if (m_components.size() > 1 && m_components.size() - 1 != component_index) {
            size_t last_component_index = m_components.size() - 1;
            size_t last_enitity_id = m_component_to_entity_id[last_component_index];
            m_components[component_index] = std::move(m_components.back());
            m_component_to_entity_id[component_index] = last_enitity_id;
            m_entity_id_to_component[last_enitity_id] = component_index;
            m_entity_id_to_component.erase(last_component_index);
            m_entity_id_to_component.erase(entity_id);
        } else {
            m_component_to_entity_id.erase(component_index);
            m_entity_id_to_component.erase(entity_id);
        }

        m_components.pop_back();
        m_entity_components[entity_id][ComponentType::ID] = false;
    }

private:
    std::vector<ComponentType> m_components;
    std::unordered_map<size_t, EntityID> m_component_to_entity_id;
    std::unordered_map<EntityID, size_t> m_entity_id_to_component;
    std::vector<std::bitset<ComponentCount>>& m_entity_components;
};

}