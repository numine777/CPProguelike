#pragma once

#include "components.h"

class PositionComponent : public Component {
private:
    int xpos; 
    int ypos;

public:
    PositionComponent() {
        xpos = 0;
        ypos = 0;
    }

    PositionComponent(int x, int y) {
        xpos = x;
        ypos = y;
    }

    int x() { return xpos; }
    int y() { return ypos; }

    void update() override {
        xpos++;
        ypos++;
    }

    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }
};