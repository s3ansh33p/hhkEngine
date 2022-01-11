/**
 * @file tile_handler.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Tile handler for the engine
 * @version 1.0
 * @date 2022-01-09
 */

#pragma once

#include "../../draw_functions.hpp"

// determines if the TileManager is active
bool isTileManagerActive = false;

struct Tile
{
    uint16_t *texture;
    bool isSolid;   
};

struct Cell
{
    int tileID;
    bool hasUpdate;
};

// Tiles must be 16x16 pixels.
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

const int TILE_COUNT_X = 20;
const int TILE_COUNT_Y = 33;

const int TILE_MAX = TILE_COUNT_X * TILE_COUNT_Y;

const int TILESET_MAX = 2;

class TileManager {
public:
    Tile tileset[TILESET_MAX];
    Cell map[TILE_MAX];
    void DrawTiles(int x, int y);
    void Init();
    const Tile& GetTile(int x, int y);
    bool IsTileSolid(int x, int y);
    void UpdateTile(int x, int y, int tileID);
    void RefreshTile(int x, int y);
    void BGTile(int x1, int y1, int w, int h, uint16_t color);
};

// pointer for the tile manager that gets created later on
TileManager *tile_manager_pointer = nullptr;

// 320 × 528

void TileManager::Init() {
    int map[TILE_MAX] = {
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
    };
    // set the map to myMap
    for (int i = 0; i < TILE_MAX; i++) {
        this->map[i] = {
            map[i],
            true
        };
    }

    // set the tileset
    LOAD_TEXTURE_PTR("tile1", tile1);
    LOAD_TEXTURE_PTR("tile2", tile2);

    Tile tileset[TILESET_MAX] = {
        {tile1, true},
        {tile2, true}
    };

    for (int i = 0; i < TILESET_MAX; i++) {
        this->tileset[i] = tileset[i];
    }
    // set isActive to true
    isTileManagerActive = true;
}

const Tile& TileManager::GetTile(int x, int y) {
    return this->tileset[ this->map[ (y*TILE_COUNT_Y) + x ].tileID ];
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
            if (map[tileIndex].hasUpdate) {
                if (map[tileIndex].tileID != 0) {
                    int drawX = (x + (tileX * TILE_WIDTH));
                    int drawY = (y + (tileY * TILE_HEIGHT));
                    // remder the tile sprite
                    DRAW_TEXTURE(tileset[map[tileIndex].tileID-1].texture, drawX, drawY);
                } else {
                    this->BGTile(x + (tileX * TILE_WIDTH), y + (tileY * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT, color(0, 0, 64));
                }
                map[tileIndex].hasUpdate = false;
            }
        }
    }
}

void TileManager::UpdateTile(int x, int y, int tileID) {
    int tileIndex = (y * TILE_COUNT_X) + x;
    map[tileIndex].tileID = tileID;
    map[tileIndex].hasUpdate = true;
}

void TileManager::RefreshTile(int x, int y) {
    int tileIndex = (y * TILE_COUNT_X) + x;
    map[tileIndex].hasUpdate = true;
}

// draw a background colour for cells that need to be set back
// e.g. Debug text is shown, then hidden, those cells need to be set back to the original colour
void TileManager::BGTile(int x1, int y1, int w, int h, uint16_t color) {
	for (int x=x1; x<x1+w; x++){
		for (int y=y1; y<y1+h; y++){
			setPixel(x,y, color);
		}
    }
}