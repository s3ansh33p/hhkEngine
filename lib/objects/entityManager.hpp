/**
 * @file entityManager.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Entity manager class for the engine
 * @todo Get an entity by id
 * @version 1.0
 * @date 2021-12-23
 */

#pragma once

#include "entity.hpp"

class EntityManager {
public:
    ~EntityManager();

    void removeAll();
    void remove(int entityId);
    
};

// Remove an entity from the array.
void EntityManager::remove(int entityId) {
    if (entityId < entityCount) {
        for (int i = entityId; i < entityCount; i++) {
            entities[i] = entities[i + 1];
        }
        entityCount--;
    }
}

// Remove all entities from the array.
void EntityManager::removeAll() {
    entityCount = 0;
}