#include "game.h"
#include "textureManager.h"
#include "map.h"
#include "ECS/components.h"
#include "vector2D.h"
#include "collision.h"

Map *map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto &player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        std::cout << "Subsystems Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout <<"Renderer created!" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    map = new Map();

    //ECS implementation

    Map::LoadMap("../assets/p16x16.map", 16, 16);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("../assets/player2.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayers);

    wall.addComponent<TransformComponent>(300.f, 300.f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("../assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.AddGroup(groupMap);

}

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
    manager.refresh();
    manager.update();

    for (auto cc : colliders) {
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    }
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render() {
    SDL_RenderClear(renderer);

    for(auto& t : tiles) {
        t->draw();
    }
    for(auto& p : players) {
        p->draw();
    }
    for(auto& e : enemies) {
        e->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.AddGroup(groupMap);
}