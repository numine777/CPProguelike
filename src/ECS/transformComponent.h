#pragma once

#include "components.h"
#include "../vector2D.h"

class TransformComponent : public Component {

public:

    Vector2D position;
    Vector2D velocity;

    int speed = 3;

    TransformComponent() {
        position.x = 0.f;
        position.y = 0.f;
    }

    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
       position.x += velocity.x * speed;
       position.y += velocity.y * speed;
    }

};