/**
 * @file tile_handler.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Tile handler for the engine
 * @version 1.0
 * @date 2022-01-09
 */

#pragma once

#include "../../draw_functions.hpp"

struct Tile
{
    uint16_t *texture;
    bool isSolid;   
};

// Tiles must be 16x16 pixels.
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

const int TILE_COUNT_X = 2;
const int TILE_COUNT_Y = 2;

const int TILE_MAX = TILE_COUNT_X * TILE_COUNT_Y;

const int TILESET_MAX = 1;

class TileManager {
public:
    Tile tileset[TILESET_MAX];
    int map[TILE_MAX];
    void DrawTiles(int x, int y);
    void Init();
    const Tile& GetTile(int x, int y);
    bool IsTileSolid(int x, int y);
};

void TileManager::Init() {
    int map[TILE_MAX] = {
        1,1,
        1,0
    };
    // set the map to myMap
    for (int i = 0; i < TILE_MAX; i++) {
        this->map[i] = map[i];
    }

    // set the tileset
    LOAD_TEXTURE_PTR("tile1", tile1);
    // LOAD_TEXTURE_PTR("tile2", tile2);

    Tile tileset[TILESET_MAX] = {
        {tile1, true}
    };

    for (int i = 0; i < TILESET_MAX; i++) {
        this->tileset[i] = tileset[i];
    }

}

const Tile& TileManager::GetTile(int x, int y) {
    return this->tileset[ this->map[ (y*TILE_COUNT_Y) + x ] ];
}

bool TileManager::IsTileSolid(int x, int y) {
    return GetTile(x, y).isSolid;
}

// draw the tiles
void TileManager::DrawTiles(int x, int y)
{
    for (int tileY = 0; tileY < TILE_COUNT_Y; tileY++)
    {
        for (int tileX = 0; tileX < TILE_COUNT_X; tileX++)
        {
            int tileIndex = (tileY * TILE_COUNT_X) + tileX;
            if (map[tileIndex] != 0)
            {
                int drawX = (x + (tileX * TILE_WIDTH));
                int drawY = (y + (tileY * TILE_HEIGHT));
                // remder the tile sprite
                DRAW_TEXTURE(tileset[map[tileIndex]-1].texture, drawX, drawY);

            }
        }
    }
}