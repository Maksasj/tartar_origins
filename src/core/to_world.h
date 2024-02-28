#ifndef _TO_CORE_WORLD_H_
#define _TO_CORE_WORLD_H_

#include <stdlib.h>
#include <stdio.h>

typedef enum TileType {
    VOID_TILE,
    GROUND_TILE,
    WATER_TILE
} TileType;

typedef struct Tile {
    TileType type;
} Tile;

Tile to_create_tile(TileType type);

typedef struct Chunk {
    long long xChunk;
    long long yChunk;

    Tile tiles[16][16];
} Chunk;

typedef struct World {
    unsigned int chunkCount;
    Chunk* chunks;
} World;

World* to_create_world();

void to_world_create_chunk(World* world, long long xChunk, long long yChunk);
Chunk* to_world_get_chunk(World* world, long long xChunk, long long yChunk);

Tile to_world_get_tile(World* world, long long xPos, long long yPos);

#endif