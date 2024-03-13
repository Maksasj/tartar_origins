#include "to_world.h"


World* to_create_world() {
    World* world = malloc(sizeof(World));

    memset(world->chunks, 0, sizeof(world->chunks));
    memset(world->creatures, 0, sizeof(world->creatures));

    return world;
};

void todo_fill_chunk(Chunk* chunk) {
    for(int x = 0; x < 16; ++x) {
        for(int y = 0; y < 16; ++y) {
            Attribute* tile = to_create_set_attribute("Tile");

            Attribute* material = to_create_material_attribute("Grass");
            to_set_append_attribute(tile, material);

            Attribute* position = to_create_position_attribute(x + chunk->xChunk * 16, y + chunk->yChunk * 16);
            to_set_append_attribute(tile, position);

            chunk->tiles[x][y] = tile;
        }
    }
}

void to_world_create_chunk(World* world, long long xChunk, long long yChunk) {
    for(int i = 0; i < TO_WORLD_MAX_CHUNKS; ++i) {
        if(world->chunks[i] != NULL)
            continue;

        Chunk* chunk = malloc(sizeof(Chunk));

        chunk->xChunk = xChunk;
        chunk->yChunk = yChunk;

        todo_fill_chunk(chunk);

        world->chunks[i] = chunk;

        return;
    }
}

Chunk* to_world_get_chunk(World* world, long long xChunk, long long yChunk) {
    for(int i = 0; i < TO_WORLD_MAX_CHUNKS; ++i) {
        Chunk* chunk = world->chunks[i];

        if(chunk == NULL)
            continue;

        if(chunk->xChunk == xChunk && chunk->yChunk == yChunk)
            return chunk;
    }

    return NULL;
}

int to_world_summon_creature(World* world, Attribute* creature) {
    for(int i = 0; i < TO_WORLD_MAX_CREATURES; ++i) {
        if(world->creatures[i] != NULL)
            continue;

        world->creatures[i] = creature;
        return 1;
    }

    return 0;
}

Attribute* to_world_get_tile(World* world, long long xPos, long long yPos) {
    long long xChunk = xPos >> 4;
    long long yChunk = yPos >> 4;

    Chunk* chunk = to_world_get_chunk(world, xChunk, yChunk);

    if(chunk == NULL)
        return NULL;

    int xRelative = xPos % 16;
    int yRelative = yPos % 16;

    if(xRelative < 0) xRelative += 16;
    if(yRelative < 0) yRelative += 16;

    return chunk->tiles[xRelative][yRelative];
}

int to_world_set_tile(World* world, long long xPos, long long yPos, char* material) {
    long long xChunk = xPos >> 4;
    long long yChunk = yPos >> 4;

    Chunk* chunk = to_world_get_chunk(world, xChunk, yChunk);

    if(chunk == NULL)
        return 0;

    int xRelative = xPos % 16;
    int yRelative = yPos % 16;

    if(xRelative < 0) xRelative += 16;
    if(yRelative < 0) yRelative += 16;

    if(chunk->tiles[xRelative][yRelative] == NULL)
        free(chunk->tiles[xRelative][yRelative]);

    Attribute* tile = to_create_set_attribute("Tile");

    Attribute* mat = to_create_material_attribute(material);
    to_set_append_attribute(tile, mat);

    Attribute* position = to_create_position_attribute(xPos, yPos);
    to_set_append_attribute(tile, position);

    chunk->tiles[xRelative][yRelative] = tile;

    return 1;
}