#include "to_world.h"


World* to_create_world() {
    World* world = malloc(sizeof(World));

    world->chunkCount = 0;
    world->chunks = NULL;
    memset(world->creatures, 0, sizeof(world->creatures));

    return world;
};

void todo_fill_chunk(Chunk* chunk) {
    for(unsigned int x = 0; x < 16; ++x) {
        for(unsigned int y = 0; y < 16; ++y) {
            Attribute* tile = to_create_set_attribute("Self");

            Attribute* material = to_create_material_attribute("Grass");
            to_set_append_attribute(tile, material);

            Attribute* position = to_create_position_attribute(x + chunk->xChunk * 16, y + chunk->yChunk * 16);
            to_set_append_attribute(tile, position);

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

    // Todo
    todo_fill_chunk(chunk);

    // to_chunk_fill_tiles(chunk, to_create_tile(GROUND_TILE));
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

Attribute* to_world_get_tile(World* world, long long xPos, long long yPos) {
    long long xChunk = xPos >> 4;
    long long yChunk = yPos >> 4;

    Chunk* chunk = to_world_get_chunk(world, xChunk, yChunk);

    if(chunk == NULL)
        return NULL;

    unsigned long xRelative = xPos % 16;
    unsigned long yRelative = yPos % 16;

    return chunk->tiles[xRelative][yRelative];
}

int to_world_set_tile(World* world, long long xPos, long long yPos, char* material) {
    long long xChunk = xPos >> 4;
    long long yChunk = yPos >> 4;

    Chunk* chunk = to_world_get_chunk(world, xChunk, yChunk);

    if(chunk == NULL)
        return 0;

    unsigned long xRelative = xPos % 16;
    unsigned long yRelative = yPos % 16;

    if(chunk->tiles[xRelative][yRelative] == NULL)
        free(chunk->tiles[xRelative][yRelative]);

    Attribute* tile = to_create_set_attribute("Self");

    Attribute* mat = to_create_material_attribute(material);
    to_set_append_attribute(tile, mat);

    Attribute* position = to_create_position_attribute(xPos, yPos);
    to_set_append_attribute(tile, position);

    chunk->tiles[xRelative][yRelative] = tile;

    return 1;
}