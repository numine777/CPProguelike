#include "game.h"
#include "textureManager.h"
#include "map.h"
#include "ECS/components.h"
#include "vector2D.h"
#include "collision.h"
#include "assetManager.h"
#include <sstream>

Map *map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 800, 640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
//auto& label(manager.addEntity()); broken

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        std::cout << "Subsystems Initialized..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout <<"Renderer created!" << std::endl;
        }
        isRunning = true;
    } 

    if(TTF_Init() == -1) {
        std::cout << "Error: SDL_TTF" << std::endl;
    }

    assets->AddTexture("terrain", "../assets/terrain_ss.png");
    assets->AddTexture("player", "../assets/player2.png");
    assets->AddTexture("projectile", "../assets/proj.png");

    //assets->AddFont("arial", "../assets/arial.ttf", 16); broken

    map = new Map("terrain", 2, 32);

    //ECS implementation

    map->LoadMap("../assets/fix.map", 25, 20);

    player.addComponent<TransformComponent>(800.f, 640.f, 16, 16, 2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayers);

    //SDL_Color white = {255, 255, 255, 255};

    //label.addComponent<UILabel>(10, 10, "Test String", "arial", white); broken

    assets->CreateProjectile(Vector2D(600.f,600.f), 200, 2, Vector2D(2.f,0.f), "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
//auto& labels(manager.getGroup(Game::groupUI)); broken

void Game::handleEvents() {

    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
        isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
/*
    std::stringstream ss;
    ss << "Player Position: " << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial"); broken
*/
    manager.refresh();
    manager.update();

    for(auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    for(auto& p : projectiles) {
        if(Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
            std::cout << "Hit player" << std::endl;
            p->destroy();
            //create health component
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if(camera.x < 0) { camera.x = 0; }
    if(camera.y < 0) { camera.y = 0; }
    if(camera.x > camera.w) { camera.x = camera.w; }
    if(camera.y > camera.h) { camera.y = camera.h; }
}



void Game::render() {
    SDL_RenderClear(renderer);

    for(auto& t : tiles) {
        t->draw();
    }
    for(auto& p : players) {
        p->draw();
    }

    /*
    for(auto& e : enemies) {
        e->draw();
    }
    */

    for(auto& p : projectiles) {
        p->draw();
    }

    //label.draw(); broken

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
