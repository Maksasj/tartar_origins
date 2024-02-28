#include "to_world.h"


World* to_create_world() {
    World* world = malloc(sizeof(World));

    world->chunkCount = 0;
    world->chunks = NULL;
    memset(world->creatures, 0, sizeof(world->creatures));

    return world;
};

Creature* to_world_summon_creature(World* world, Creature creature) {
    for(int i = 0; i < 1024; ++i) {
        if(world->creatures[i] == NULL) {
            world->creatures[i] = malloc(sizeof(Creature));
            *world->creatures[i] = creature;

            return world->creatures[i];
        }
    }

    return NULL;
}

Tile to_create_tile(TileType type) {
    Tile tile;

    tile.type = type;

    return tile;
}

void to_chunk_fill_tiles(Chunk* chunk, Tile tile) {
    for(unsigned int x = 0; x < 16; ++x) {
        for(unsigned int y = 0; y < 16; ++y) {
            chunk->tiles[x][y] = tile;
        }
    }
}

void to_world_create_chunk(World* world, long long xChunk, long long yChunk) {
    if(world->chunks == NULL) {
        world->chunks = malloc(sizeof(Chunk));
    } else {
        world->chunks = realloc(world->chunks, sizeof(Chunk) * (world->chunkCount + 1));
    }

    Chunk* chunk = &world->chunks[world->chunkCount];
    chunk->xChunk = xChunk;
    chunk->yChunk = yChunk;

    to_chunk_fill_tiles(chunk, to_create_tile(GROUND_TILE));
    ++world->chunkCount;
}

Chunk* to_world_get_chunk(World* world, long long xChunk, long long yChunk) {
    for(unsigned int i = 0; i < world->chunkCount; ++i) {
        Chunk* chunk = &world->chunks[i];

        if(chunk->xChunk == xChunk && chunk->yChunk == yChunk)
            return chunk;
    }

    return NULL;
}

Tile to_world_get_tile(World* world, long long xPos, long long yPos) {
    long long xChunk = xPos >> 4;
    long long yChunk = yPos >> 4;

    Chunk* chunk = to_world_get_chunk(world, xChunk, yChunk);
    if(chunk == NULL)
        return to_create_tile(VOID_TILE);

    unsigned long xRelative = xPos % 16;
    unsigned long yRelative = yPos % 16;

    return chunk->tiles[xRelative][yRelative];
};
