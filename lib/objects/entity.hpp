/**
 * @file entity.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Generic entity class for the engine
 * @version 1.1
 * @date 2021-01-11
 */

#pragma once

#include "../environment.hpp"
#include "../../calc.hpp"

int entityCount = 0;
int entityIDCounter = 0;
int typeCounter[4] = {0, 0, 0, 0};

class Entity {
public:
    int id;
    int x;
    int y;
    int type;
    bool hasUpdate;
    uint16_t color;
    void createEnt(int x, int y, uint16_t color, int type);
    void create(int x, int y, uint16_t color, int type);
    void removeEnt();
    void remove();
};

// Global array of entites.
Entity entities[MAX_ENTITIES];

/* TYPES
 0 = RECTANGLE
 1 = PARTICLE
 2 = RIGIDBODY
 3 = CIRCLE
*/

// Create the entity
void Entity::createEnt(int x, int y, uint16_t color, int type) {
    this->x = x;
    this->y = y;
    this->color = color;
    this->type = type;
    this->hasUpdate = true;
    this->id = entityIDCounter;
    typeCounter[type]++;
    entities[entityCount] = *this;
    entityCount++;
    entityIDCounter++;
}

// place holder method "create" that is used in derived classes.
void Entity::create(int x, int y, uint16_t color, int type) {
    this->createEnt(x, y, color, type);
}
// Remove the entity from the array.
void Entity::removeEnt() {
    for (int i = this->id; i < entityCount; i++) {
        entities[i] = entities[i + 1];
    }
    entityCount--;
    typeCounter[this->type]--;
}

// place holder method "remove" that is used in derived classes.
void Entity::remove() {
    this->removeEnt();
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
        for (int i = 0; i < typeCounter[type] + 1; i++) {
            entitiesOfType[i].remove();
        }
    }
}
