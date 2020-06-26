#include "assetManager.h"
#include "ECS/components.h"

AssetManager::AssetManager(Manager* man) : manager(man) {}

AssetManager::~AssetManager() {}

void AssetManager::CreateProjectile(Vector2D pos, int range, int speed, Vector2D vel, std::string id) {
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(id, false);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.AddGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path) {
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontsize) {
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontsize));
}

TTF_Font* AssetManager::GetFont(std::string id) {
    return fonts[id];
}