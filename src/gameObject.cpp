#include "gameObject.h"
#include "textureManager.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);
    xpos = x;
    ypos = y;
}

void GameObject::Update() {
    xpos++;
    ypos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRectl.x = xpos;
    destRectl.y = ypos;
    destRectl.w = srcRect.w * 2;
    destRectl.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRectl);
}