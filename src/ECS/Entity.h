#pragma once

#include <bitset>
#include <cstdint>
#include <vector>

using EntityID = uint32_t;

template <size_t ComponentCount, size_t SystemCount>
class EntityContainer {
public:
    EntityID create()
    {
        if (m_free_entity_ids.empty()) {
            m_entity_components.emplace_back();
            return m_entity_components.size() - 1;
        }
        auto free_entity_id = m_free_entity_ids.back();
        m_free_entity_ids.pop_back();
        m_entity_components[free_entity_id].reset();
        return free_entity_id;
    }

    void remove(EntityID entity_id)
    {
        m_free_entity_ids.push_back(entity_id);
    }

    auto& entity_components()
    {
        return m_entity_components;
    }

private:
    std::vector<std::bitset<ComponentCount>> m_entity_components;
    std::vector<EntityID> m_free_entity_ids;
};
