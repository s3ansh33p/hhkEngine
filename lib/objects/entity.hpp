/**
 * @file entity.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Generic entity class for the engine
 * @version 1.0
 * @date 2021-12-29
 */

#pragma once

#include "../environment.hpp"
#include "../../calc.hpp"

int entityCount = 0;
int entityIDCounter = 0;
int typeCounter[3] = {0, 0, 0};

class Entity {
public:
    int id;
    int x;
    int y;
    int type;
    uint16_t color;
    void create(int x, int y, uint16_t color, int type);
    void remove();
};

// Global array of entites.
Entity entities[MAX_ENTITIES];

/* TYPES
 0 = RECTANGLE
 1 = PARTICLE
 2 = RIGIDBODY
*/

// Create the entity
void Entity::create(int x, int y, uint16_t color, int type) {
    this->x = x;
    this->y = y;
    this->color = color;
    this->type = type;
    this->id = entityIDCounter;
    typeCounter[type]++;
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
    typeCounter[this->type]--;
}

// get all entities of a certain type
Entity* getEntitiesOfType(int type) {
    if (typeCounter[type] == 0) {
        Entity* entitiesOfType = new Entity[1];
        entitiesOfType[0].id = -1;
        return entitiesOfType;
    }
    Entity* entitiesOfType = new Entity[typeCounter[type]];
    int count = 0;
    for (int i = 0; i < entityCount; i++) {
        if (entities[i].type == type) {
            entitiesOfType[count] = entities[i];
            count++;
        }
    }
    return entitiesOfType;
}

// remove all entities of a certain type
void removeEntitiesOfType(int type) {
    Entity* entitiesOfType = getEntitiesOfType(type);
    if (entitiesOfType[0].id != -1) {
        for (int i = 0; i < typeCounter[type]; i++) {
            entitiesOfType[i].remove();
        }
    }
}