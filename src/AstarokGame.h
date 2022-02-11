#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>

#include "data/SpriteData.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/Constants.h"
#include "utils/Utils.h"
#include "utils/GameCookie.h"

#include "entities/Sprite.h"
#include "entities/AISprite.h"
#include "entities/InteractiveObject.h"
#include "entities/Room.h"
#include "entities/Map.h"
#include "entities/Particle.h"
#include "sounds/Sounds.h"

class AstarokGame {

    public:  // Variables
        EventType             event;
        uint8_t               eventCounter;
        uint8_t               seeds[Constants::GameSeeds];
        uint8_t               lives;
        int16_t               score;
        uint16_t              mapNumber;
        Point                 camera;

        InteractiveObject     * chestObj;
        Direction             ballDirection;
        uint8_t               ballX;
        uint8_t               ballIdx;
        uint8_t               ballDelay;

        Sprite                player;
        AISprite              mobs[Constants::SpriteCap];
        Map                   level;
        Sounds                * sounds;
        GameCookie            * cookie;
        bool                  pause = false;
        uint32_t              seed = 0;



uint8_t death_loc = 0;
uint8_t death_loc_Map;
uint8_t death_loc_Room;
uint8_t death_Sprite_Type;
uint8_t death_Sprite;
int16_t death_SX;
int16_t death_SY;
int16_t death_EC;
bool death_IA;
int16_t death_PX;
int16_t death_PY; 



    private:
        uint8_t               cameraOffset;
        uint8_t               signDelay;
        Direction             cameraPan;

        Particle particles[Constants::ParticlesMax];


    public:  // Constructor
        AstarokGame();

    public:  // Methods
        void newGame();
        void cycle(GameState &gameState);
        void draw();
        uint8_t addMob(const uint8_t *data, int16_t x, uint8_t y, uint8_t maxHeight = 255);
        uint8_t getSpareMobCount();
        void renderTrialOver();
        void renderPause();
        void renderSign();
        void playMiniGame(GameState &gameState);
        void displaySign(GameState &gameState);

    private:  // Methods
        void startLevel();
        bool testCollision(Sprite * player, AISprite * sprite);
        void die(GameState &gameState);
        void drawMap_Background();
        void drawMap_Background_2();
        void drawMap_Foreground();
        void drawHUD();
        void drawPlayer();
        void drawMobs();
        void adjustCamera();
        void processButtons();
        uint8_t spawnY();

};
