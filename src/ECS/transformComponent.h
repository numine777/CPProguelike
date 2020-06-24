#pragma once

#include "components.h"
#include "../vector2D.h"

class TransformComponent : public Component {

public:

    Vector2D position;

    TransformComponent() {
        position.x = 0.f;
        position.y = 0.f;
    }

    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void update() override {
       
    }

};