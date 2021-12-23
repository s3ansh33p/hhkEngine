/**
 * @file entity.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Generic entity class for the engine
 * @version 1.0
 * @date 2021-12-23
 */

#pragma once

#include "../environment.hpp"
#include "../../calc.hpp"

int entityCount = 0;
int entityIDCounter = 0;

class Entity {
public:
    int id;
    int x;
    int y;
    uint16_t color;
    void create(int x, int y, uint16_t color);
    void remove();
};

// Global array of entites.
Entity entities[MAX_ENTITIES];

// Create the entity
void Entity::create(int x, int y, uint16_t color) {
    this->x = x;
    this->y = y;
    this->color = color;
    this->id = entityIDCounter;
    entities[entityCount] = *this;
    entityCount++;
    entityIDCounter++;
}

// Remove the entity from the array.
void Entity::remove() {
    for (int i = this->id; i < entityCount; i++) {
        entities[i] = entities[i + 1];
    }
    entityCount--;
}
