/**
 * @file box.hpp
 * @author David Figatner (https://github.com/davidfig)
 * @note Translated from JavaScript to C++
 * @brief Collision detection for the engine
 * @version 1.0
 * @date 2022-01-11
 */

#pragma once

/**
 * @see https://github.com/davidfig/intersects/blob/master/box-circle.js
 * @param boxX 
 * @param boxY 
 * @param boxWidth 
 * @param boxHeight 
 * @param circleX 
 * @param circleY 
 * @param circleRadius 
 */
bool boxCircle(int boxX, int boxY, int boxWidth, int boxHeight, int circleX, int circleY, int circleRadius) {
    int halfWidth = boxWidth / 2;
    int halfHeight = boxHeight / 2;

    int centerX = boxX + halfWidth;
    int centerY = boxY + halfHeight;

    int distanceX = circleX - centerX;
    int distanceY = circleY - centerY;

    if (distanceX > halfWidth + circleRadius || distanceY > halfHeight + circleRadius) {
        return false;
    }

    if (distanceX <= halfWidth || distanceY <= halfHeight) {
        return true;
    }

    int cornerDistanceX = distanceX - halfWidth;
    int cornerDistanceY = distanceY - halfHeight;
    return cornerDistanceX * cornerDistanceX + cornerDistanceY * cornerDistanceY <= circleRadius * circleRadius;
}

/**
 * @see https://github.com/davidfig/intersects/blob/master/box-box.js
 * @param boxX 
 * @param boxY 
 * @param boxWidth 
 * @param boxHeight 
 * @param otherX 
 * @param otherY 
 * @param otherWidth 
 * @param otherHeight 
 */
bool boxBox(int boxX, int boxY, int boxWidth, int boxHeight, int otherX, int otherY, int otherWidth, int otherHeight) {
    return boxX < otherX + otherWidth && boxX + boxWidth > otherX && boxY < otherY + otherHeight && boxY + boxHeight > otherY;
}

/**
 * @see https://github.com/davidfig/intersects/blob/master/box-point.js
 * @param boxX 
 * @param boxY 
 * @param boxWidth 
 * @param boxHeight 
 * @param pointX 
 * @param pointY 
 */
bool boxPoint(int boxX, int boxY, int boxWidth, int boxHeight, int pointX, int pointY) {
    return boxX < pointX && boxX + boxWidth > pointX && boxY < pointY && boxY + boxHeight > pointY;
}
