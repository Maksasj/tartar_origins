#ifndef _TO_CORE_WORLD_H_
#define _TO_CORE_WORLD_H_

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "attribute/to_attributes.h"

typedef struct Chunk {
    long long xChunk;
    long long yChunk;

    Attribute* tiles[16][16];
} Chunk;

#define TO_WORLD_MAX_CHUNKS 1024
#define TO_WORLD_MAX_CREATURES 1024

typedef struct World {
    Chunk* chunks[TO_WORLD_MAX_CHUNKS];
    Attribute* creatures[TO_WORLD_MAX_CREATURES];
} World;

World* to_create_world();

void to_world_create_chunk(World* world, long long xChunk, long long yChunk);
Chunk* to_world_get_chunk(World* world, long long xChunk, long long yChunk);

int to_world_summon_creature(World* world, Attribute* creature);
int to_world_terminate_creature(World* world, Attribute* creature);

Attribute* to_world_get_tile(World* world, long long xPos, long long yPos);
int to_world_set_tile(World* world, long long xPos, long long yPos, char* material);

#endif