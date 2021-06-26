#pragma once

#include <bitset>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ECS {

using EntityID = uint32_t;

template <size_t ComponentCount, size_t SystemCount>
class EntityContainer {
public:
    EntityContainer() = default;

    EntityID create(const std::string& name = "")
    {
        if (m_free_entity_ids.empty()) {
            auto new_entity_id = m_entity_components.size();
            m_entity_components.emplace_back();

            if (name.empty()) {
                m_entity_names.emplace_back(unnamed_entity(new_entity_id));
            } else {
                m_entity_names.emplace_back(name);
            }

            return new_entity_id;
        }

        auto free_entity_id = m_free_entity_ids.back();
        m_free_entity_ids.pop_back();
        m_entity_components[free_entity_id].reset();

        if (name.empty()) {
            m_entity_names[free_entity_id] = unnamed_entity(free_entity_id);
        } else {
            m_entity_names[free_entity_id] = name;
        }

        return free_entity_id;
    }

    void remove(EntityID entity_id)
    {
        m_free_entity_ids.push_back(entity_id);
    }

    size_t count() const { return m_entity_components.size(); }

    auto& entity_components()
    {
        return m_entity_components;
    }

    inline const auto& entity_name(EntityID entity_id) const
    {
        return m_entity_names[entity_id];
    }

    inline bool has_entity(EntityID entity_id) const
    {
        return entity_id < count() && std::find(m_free_entity_ids.begin(), m_free_entity_ids.end(), entity_id) == m_free_entity_ids.end();
    }

private:
    std::string unnamed_entity(int id)
    {
        std::stringstream name;
        name << "Entity " << id;
        return name.str();
    }

private:
    std::vector<std::bitset<ComponentCount>> m_entity_components {};
    std::vector<EntityID> m_free_entity_ids {};
    std::vector<std::string> m_entity_names {};
};

}