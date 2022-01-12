/**
 * @file circle.hpp
 * @author David Figatner (https://github.com/davidfig)
 * @note Translated from JavaScript to C++
 * @brief Collision detection for the engine
 * @version 1.0
 * @date 2022-01-12
 */

#pragma once

/**
 * @see https://github.com/davidfig/intersects/blob/master/circle-circle.js
 * @param circleX 
 * @param circleY 
 * @param circleRadius 
 * @param otherX 
 * @param otherY 
 * @param otherRadius 
 */
bool circleCircle(int circleX, int circleY, int circleRadius, int otherX, int otherY, int otherRadius) {
    int distanceX = circleX - otherX;
    int distanceY = circleY - otherY;
    int radii = circleRadius + otherRadius;
    return distanceX * distanceX + distanceY * distanceY <= radii * radii;
}
