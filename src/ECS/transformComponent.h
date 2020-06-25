#pragma once

#include "components.h"
#include "../vector2D.h"

class TransformComponent : public Component {

public:

    Vector2D position;
    Vector2D velocity;

    int height = 16;
    int width = 16;
    int scale = 1;

    int speed = 3;

    TransformComponent() {
        position.Zero();
    }

    TransformComponent(int sc) {
        position.x = 400.f;
        position.y = 320.f;
        scale = sc;
    }

    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int h, int w, int sc) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
       
    }

};