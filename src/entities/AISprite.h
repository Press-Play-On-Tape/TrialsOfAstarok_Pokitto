#pragma once

#include "Pokitto.h"
#include "../utils/Constants.h"
#include "Sprite.h"

class AISprite : public Sprite {

    private:
        void seek();
        void detectJump();
        void detectWall();
        void detectGap();
        uint8_t getSpeed();
        uint8_t getIntelligence();

    public:
        void activate(const uint8_t * data, int tX, int tY);
        void think();
        bool getActive();
        void updateExplosion();

};