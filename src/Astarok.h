#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
#include "utils/Structs.h"
#include "AstarokGame.h"
#include "font/Font4x6.h"
#include "src/utils/DuelPalette.h"
#include "src/sounds/Sounds.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;

class Game {

    private:
        bool mute = false;
        AstarokGame game;
        GameState gameState = GameState::SplashScreen_Init;

        SplashScreenVars splashScreenVars;
        TitleScreenVars titleScreenVars;
        HighScoreVars highScoreVars;
        IntroTextVars introTextVars;
        SeedVars seedVars;

        GameCookie *cookie;
        Sounds sounds;

    // public:
    //     File mainThemeFile;
    //     Audio::RAWFileSource *music;

    public:
        void setup(GameCookie *cookie);
        void loop();

    private:
        void checkHighScoreSlot(uint16_t score);
        void writeHighScoreEntry(HighScoreVars &highScoreVars);
        void highScores();

        void introText_Init();
        void introText();

        void seed_Init();
        void seed();

        void splashScreen_Init();
        void splashScreen();

        void drawBackground();
        void titleScreen();

};

