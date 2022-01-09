/**
 * @file environment.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Engine settings
 * @version 1.0
 * @date 2021-12-12
 */

#pragma once

// Include all structs
#include "objects/vector.hpp"

// Physical constants
int GRAVITY = 2; // gravity that is applied to all objects

// Engine settings
const int MAX_ENTITIES = 40; // max number of entities
const int MAX_PARTICLES = 10; // max number of particles
const int MAX_RIGIDBODIES = 10; // max number of rigidbodies
const int MAX_RECTANGLES = 10; // max number of rectangles
const int MAX_CIRCLES = 10; // max number of circles