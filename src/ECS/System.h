#pragma once

#include "Entity.h"
#include <bitset>
#include <unordered_set>

class BaseSystem {
public:
    virtual ~BaseSystem() = default;
};

template <size_t ComponentCount, size_t SystemCount>
class ECS;

template <size_t ComponentCount, size_t SystemCount>
class System : public BaseSystem {
public:
    explicit System(ECS<ComponentCount, SystemCount>* ecs)
        : m_ecs(ecs)
    {
    }

    inline void on_entity_updated(EntityID entity_id, const std::bitset<ComponentCount>& required_components)
    {
        auto satisfied = (m_required_components & required_components) == m_required_components && m_required_components.any();

        if (satisfied) {
            add_managed_entity(entity_id);
        } else {
            remove_managed_entity(entity_id);
        }
    }

    template <typename... ComponentTypes>
    inline void set_required_components()
    {
        (m_required_components.set(ComponentTypes::ID), ...);
    }

protected:
    inline void add_managed_entity(EntityID entity_id)
    {
        m_managed_entities.insert(entity_id);
    }

    inline void remove_managed_entity(EntityID entity_id)
    {
        m_managed_entities.erase(entity_id);
    }

    auto& ecs()
    {
        return *static_cast<ECS<ComponentCount, SystemCount>*>(m_ecs);
    }

protected:
    std::bitset<ComponentCount> m_required_components;

    // entities that satisfies required components
    std::unordered_set<EntityID> m_managed_entities;

private:
    ECS<ComponentCount, SystemCount>* m_ecs;
};