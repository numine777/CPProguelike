#include "map.h"
#include "game.h"
#include <fstream>
#include "ECS/components.h"
#include "ECS/ecs.h"

extern Manager manager;


Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) {
    scaledSize = ms * ts;
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char c;
    std::fstream mapfile;
    mapfile.open(path);

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
            mapfile.get(c);
            srcY = atoi(&c) * tileSize;
            mapfile.get(c);
            srcX = atoi(&c) * tileSize;
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapfile.ignore();
        }
    }

    mapfile.ignore();

    for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
            mapfile.get(c);
            if(c == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.AddGroup(Game::groupColliders);
            }
            mapfile.ignore();
        }
    }

    mapfile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
    tile.AddGroup(Game::groupMap);
}