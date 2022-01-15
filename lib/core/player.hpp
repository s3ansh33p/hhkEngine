/**
 * @file player.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Player class for the engine
 * @version 1.0
 * @date 2022-01-14
 */

#pragma once

#include "../../draw_functions.hpp"

struct PlayerTextures {
    uint16_t *idle[6];
    uint16_t *idleLeft[6];
    uint16_t *walk[8];
    uint16_t *walkLeft[8];
    uint16_t *jump[2];
    uint16_t *jumpLeft[2];
    uint16_t *fall[2];
    uint16_t *fallLeft[2];
};

class Player {
    public:
        int16_t x = 96;
        int16_t y = 48;
        int16_t velocity = 0;
        int8_t moveSpeed = 4;
        int8_t jumpPower = 10;
        int8_t txWidth = 32;
        int8_t txHeight = 32;
        PlayerTextures textures;
        bool isMoving = false;
        bool isRight = true;
        bool isOnGround = true;
        int8_t moveCheck = 0;
        int8_t animationFrame = 0;
        void animate();
        void loadTextures();
        void checkTiles();
        void moveLeft();
        void moveRight();
        void moveJump();
        void calculateAnimationFrame();
};

void Player::moveJump() {
    if (this->isOnGround) {
        this->isOnGround = false;
        this->velocity = this->jumpPower;
    }
}

void Player::calculateAnimationFrame() {
    // x restrictions
    // if (this->x < 24) {
    //     this->x = 24;
    // } else if (this->x > 216) {
    //     this->x = 216;
    // }

    // jump velocity
    if (!this->isOnGround) {
        this->velocity--;
        this->checkTiles();
        this->y -= this->velocity;
    }

    // check if the player has hit a tile
    // if so, set the player to the ground
    int8_t tileY = this->y / TILE_HEIGHT + 2;
    if (tileY > TILE_COUNT_Y) {
        tileY = TILE_COUNT_Y;
    }
    int8_t tileX = this->x / TILE_WIDTH + 1;
    if (tileX > TILE_COUNT_X) {
        tileX = TILE_COUNT_X;
    }
    bool isSolid = tile_manager_pointer->IsTileSolid(tileX, tileY);
    if (isSolid) {
        Debug_Printf(2,21,true,0,"%d %d Collission...", tileX, tileY);
        this->isOnGround = true;
        this->velocity = 0;
        if (this->y % TILE_HEIGHT != 0) {
            this->y = (this->y / TILE_HEIGHT + 1) * TILE_HEIGHT;
        }
        // check if the tile above is solid
        if (tile_manager_pointer->IsTileSolid(tileX, tileY - 1)) {
            this->y -= TILE_HEIGHT;
        }
    } else {
        Debug_Printf(2,21,true,0,"%d %d No Collission", tileX, tileY);
        if (this->isOnGround) {
            this->isOnGround = false;
            this->velocity = -1;
        }
    }

    if (this->y > 224) {
        this->y = 0;
    }

    // move check update
    if (this->moveCheck > 0) {
        this->moveCheck--;
    } else {
        this->isMoving = false;
    }
    this->checkTiles();
}

void Player::moveLeft() {
	this->isRight = false;
	this->isMoving = true;
	this->moveCheck = 2;
    this->checkTiles();
    this->x = this->x - this->moveSpeed;
}

void Player::moveRight() {
    this->isRight = true;
    this->isMoving = true;
    this->moveCheck = 2;
    this->checkTiles();
    this->x = this->x + this->moveSpeed;
}

void Player::animate() {
    this->animationFrame++;
    if (this->isOnGround) {
        if (!this->isMoving && this->isRight) { // IDLE
            if (this->animationFrame >= 6) {
                this->animationFrame = 0;
            }
            DRAW_TEXTURE(this->textures.idle[this->animationFrame], this->x, this->y);
        } else if (!this->isMoving && !this->isRight) { // IDLE LEFT
            if (this->animationFrame >= 6) {
                this->animationFrame = 0;
            }
            DRAW_TEXTURE(this->textures.idleLeft[this->animationFrame], this->x, this->y);
        } else if (this->isMoving && this->isRight) { // WALKING
            if (this->animationFrame >= 8) {
                this->animationFrame = 0;
            }
            DRAW_TEXTURE(this->textures.walk[this->animationFrame], this->x, this->y);
        } else if (this->isMoving && !this->isRight) { // WALKING LEFT
            if (this->animationFrame >= 8) {
                this->animationFrame = 0;
            }
            DRAW_TEXTURE(this->textures.walkLeft[this->animationFrame], this->x, this->y);
        }
    } else {
        if (this->animationFrame >= 2) {
            this->animationFrame = 0;
        }
        if (this->velocity > 0 && this->isRight) { // JUMP
            DRAW_TEXTURE(this->textures.jump[this->animationFrame], this->x, this->y);
        } else if (this->velocity > 0 && !this->isRight) { // JUMP LEFT
            DRAW_TEXTURE(this->textures.jumpLeft[this->animationFrame], this->x, this->y);
        } else if (this->velocity < 0 && this->isRight) { // FALL
            DRAW_TEXTURE(this->textures.fall[this->animationFrame], this->x, this->y);
        } else if (this->velocity < 0 && !this->isRight) { // FALL LEFT
            DRAW_TEXTURE(this->textures.fallLeft[this->animationFrame], this->x, this->y);
        }
    }
}

void Player::loadTextures() {
    char hexChars[] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    };
    char path[32] = "player\\p_idle";
    char pathLeft[32] = "player\\pl_idle";
    char pathWalk[32] = "player\\p_walk";
    char pathWalkLeft[32] = "player\\pl_walk";
    char pathJump[32] = "player\\p_jump";
    char pathJumpLeft[32] = "player\\pl_jump";
    char pathFall[32] = "player\\p_fall";
    char pathFallLeft[32] = "player\\pl_fall";
    for (int i=0; i<2; i++) {
        path[13] = hexChars[i];
        pathLeft[14] = hexChars[i];
        pathWalk[13] = hexChars[i];
        pathWalkLeft[14] = hexChars[i];
        pathJump[13] = hexChars[i];
        pathJumpLeft[14] = hexChars[i];
        pathFall[13] = hexChars[i];
        pathFallLeft[14] = hexChars[i];
        this->textures.idle[i] = load_texture(path);
        this->textures.idleLeft[i] = load_texture(pathLeft);
        this->textures.walk[i] = load_texture(pathWalk);
        this->textures.walkLeft[i] = load_texture(pathWalkLeft);
        this->textures.jump[i] = load_texture(pathJump);
        this->textures.jumpLeft[i] = load_texture(pathJumpLeft);
        this->textures.fall[i] = load_texture(pathFall);
        this->textures.fallLeft[i] = load_texture(pathFallLeft);
    }
    for (int i=2; i<6; i++) {
        path[13] = hexChars[i];
        pathLeft[14] = hexChars[i];
        pathWalk[13] = hexChars[i];
        pathWalkLeft[14] = hexChars[i];
        this->textures.idle[i] = load_texture(path);
        this->textures.idleLeft[i] = load_texture(pathLeft);
        this->textures.walk[i] = load_texture(pathWalk);
        this->textures.walkLeft[i] = load_texture(pathWalkLeft);
    }
    for (int i=6; i<8; i++) {
        pathWalk[13] = hexChars[i];
        pathWalkLeft[14] = hexChars[i];
        this->textures.walk[i] = load_texture(pathWalk);
        this->textures.walkLeft[i] = load_texture(pathWalkLeft);
    }
}

void Player::checkTiles() {
    // update player tiels around it
    for (int i=0; i<=2; i++) {
        for (int j=0; j<=2; j++) {
            tile_manager_pointer->RefreshTile(this->x/TILE_WIDTH + i, this->y/TILE_HEIGHT + j);
        }
    }

}