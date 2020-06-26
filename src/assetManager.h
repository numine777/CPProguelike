#pragma once

#include <map>
#include <string>
#include "textureManager.h"
#include "vector2D.h"
#include "ECS/ecs.h"


class AssetManager {
public:
    AssetManager(Manager* man);
    ~AssetManager();

    //game objects
    void CreateProjectile(Vector2D pos, int range, int speed, Vector2D vel, std::string id);

    //texture management
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);

private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
};