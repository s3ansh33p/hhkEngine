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
    uint16_t *walking[4];
};

const uint8_t frameSkip = 4;

class Player {
    public:
        int8_t x = 3;
        int8_t y = 1;
        int8_t txWidth = 32;
        int8_t txHeight = 32;
        PlayerTextures textures;  
        int8_t direction = 0; // 0 = right, 1 = left, 2 = up, 3 = down
        int8_t animationFrame = 0;
        int8_t cycleState = 0; // 0 = idle, 1 = idleLeft, 2 = walking
        void animate();
        void loadTextures();
        void checkTiles();
};

void Player::animate() {
    // check the cycle state
    if (renderer_pointer->currentTime % frameSkip != 0) return;
    this->animationFrame++;
    if (cycleState == 0) { // IDLE
        if (this->animationFrame >= 6) {
            this->animationFrame = 0;
        }
        DRAW_TEXTURE(this->textures.idle[this->animationFrame], this->x*this->txWidth, this->y*this->txHeight);
    } else if (cycleState == 1) { // IDLE LEFT
        if (this->animationFrame >= 6) {
            this->animationFrame = 0;
        }
        DRAW_TEXTURE(this->textures.idleLeft[this->animationFrame], this->x*this->txWidth, this->y*this->txHeight);
    } else if (cycleState == 2) { // WALKING
        if (this->animationFrame >= 4) {
            this->animationFrame = 0;
        }
        DRAW_TEXTURE(this->textures.walking[this->animationFrame], this->x*this->txWidth, this->y*this->txHeight);
    }
}

void Player::loadTextures() {
    // load the textures 32x32 pixels
    LOAD_TEXTURE_PTR("p_idle0", p_idle0);
    LOAD_TEXTURE_PTR("p_idle1", p_idle1);
    LOAD_TEXTURE_PTR("p_idle2", p_idle2);
    LOAD_TEXTURE_PTR("p_idle3", p_idle3);
    LOAD_TEXTURE_PTR("p_idle4", p_idle4);
    LOAD_TEXTURE_PTR("p_idle5", p_idle5);
    this->textures.idle[0] = p_idle0;
    this->textures.idle[1] = p_idle1;
    this->textures.idle[2] = p_idle2;
    this->textures.idle[3] = p_idle3;
    this->textures.idle[4] = p_idle4;
    this->textures.idle[5] = p_idle5;
    
    LOAD_TEXTURE_PTR("pl_idle0", pl_idle0);
    LOAD_TEXTURE_PTR("pl_idle1", pl_idle1);
    LOAD_TEXTURE_PTR("pl_idle2", pl_idle2);
    LOAD_TEXTURE_PTR("pl_idle3", pl_idle3);
    LOAD_TEXTURE_PTR("pl_idle4", pl_idle4);
    LOAD_TEXTURE_PTR("pl_idle5", pl_idle5);
    this->textures.idleLeft[0] = pl_idle0;
    this->textures.idleLeft[1] = pl_idle1;
    this->textures.idleLeft[2] = pl_idle2;
    this->textures.idleLeft[3] = pl_idle3;
    this->textures.idleLeft[4] = pl_idle4;
    this->textures.idleLeft[5] = pl_idle5;
}

void Player::checkTiles() {
    if (renderer_pointer->currentTime % frameSkip == 0) {
        // tile manager using 16x16 tiles and 32x32 player
        tile_manager_pointer->RefreshTile(this->x*2, this->y*2);
        tile_manager_pointer->RefreshTile(this->x*2 + 1, this->y*2);
        tile_manager_pointer->RefreshTile(this->x*2 + 1, this->y*2 + 1);
        tile_manager_pointer->RefreshTile(this->x*2, this->y*2 + 1);
    }
}