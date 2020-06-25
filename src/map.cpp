#include "map.h"
#include "game.h"
#include <fstream>


Map::Map() {
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
            srcY = atoi(&c) * 32;
            mapfile.get(c);
            srcX = atoi(&c) * 32;
            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapfile.ignore();
        }
    }
    mapfile.close();
}

