#include "Astarok.h"

void Game::seed_Init() {

    seedVars.reset();
    gameState = GameState::Seed;

}

void Game::seed() {

    drawBackground();
    
    PD::drawBitmap(25, 8, Images::EnterRunes_Text);
    PD::drawBitmap(15, 27, Images::EnterRunes_00);
    PD::drawBitmap(15, 53, Images::EnterRunes_02);
    PD::drawBitmap(88, 27, Images::EnterRunes_01);
    PD::drawBitmap(88, 53, Images::EnterRunes_03);

    PD::drawFastHLine(15, 27, 73);
    PD::drawFastHLine(15, 60, 73);
    PD::drawFastHLine(17, 62, 75);

    for (uint8_t i = 0; i < 5; i++) {

        if (i == seedVars.index && seedVars.spinIndex > 0) {
            PD::drawBitmap(21 + (i* 14), 37, Images::Rune_Frame[16 - seedVars.spinIndex]);
        }
        else {
            PD::drawBitmap(21 + (i* 14), 37, Images::Rune_Frame_00);
            PD::drawBitmap(24 + (i* 14), 41, Images::Runes[seedVars.seed[i]]);
        }

    }

    PD::drawBitmap(24 + (seedVars.index * 14), 32, Images::ArrowUp);
    PD::drawBitmap(24 + (seedVars.index* 14), 53, Images::ArrowDown);

    if (seedVars.spinIndex == 0) {

        if (PC::buttons.pressed(BTN_UP)) {
            seedVars.incValue();
            //sound.tones(Sounds::ButtonPress);
        }

        if (PC::buttons.pressed(BTN_DOWN)) { 
            seedVars.decValue();
            //sound.tones(Sounds::ButtonPress);
        }

        if (PC::buttons.pressed(BTN_LEFT)) { 
            seedVars.decIndex();
            //if (seedVars.decIndex()) sound.tones(Sounds::ButtonPress);
        }

        if (PC::buttons.pressed(BTN_RIGHT)) { 
            seedVars.incIndex();
            //if (seedVars.incIndex()) sound.tones(Sounds::ButtonPress);
        }

        if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

            //SJHrandomSeed(seedVars.getSeedValue());
            for (uint8_t a = 0; a < Constants::GameSeeds; a++ ) game.seeds[a] = random(0, 255);

            //sound.tones(Sounds::ButtonPress);
            gameState = GameState::Game_Init;

        }

    }

    seedVars.decSpinIndex();

}

