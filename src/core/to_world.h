#ifndef _TO_CORE_WORLD_H_
#define _TO_CORE_WORLD_H_

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "to_entity.h"

typedef struct Chunk {
    long long xChunk;
    long long yChunk;

    Entity* tiles[16][16];
} Chunk;

typedef struct World {
    unsigned int chunkCount;
    Chunk* chunks;

    Entity* creatures[1024];
} World;

World* to_create_world();

// Entity* to_world_summon_creature(World* world, Entity creature);

void to_world_create_chunk(World* world, long long xChunk, long long yChunk);
Chunk* to_world_get_chunk(World* world, long long xChunk, long long yChunk);

// Tile to_world_get_tile(World* world, long long xPos, long long yPos);

#endif