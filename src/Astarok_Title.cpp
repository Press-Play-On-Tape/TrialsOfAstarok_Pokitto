#include "Astarok.h"

void Game::drawBackground() {


    PD::drawBitmap(-5, 12, Images::Underground_Brick);
    PD::drawBitmap(97, 12, Images::Underground_Brick);

    PD::drawBitmap(-5, 66, Images::Underground_Brick);
    PD::drawBitmap(97, 66, Images::Underground_Brick);

    PD::drawBitmap(2, 37, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(103, 37, Images::Torch[Utils::getFrameCount(16) / 4]);

}

void Game::titleScreen() {

    PD::drawBitmap(15, 16, Images::Title);
    PD::drawBitmap(26, 12, Images::Underground_Chain);
    PD::drawBitmap(81, 12, Images::Underground_Chain);    
    drawBackground();

    PD::drawBitmap(titleScreenVars.index == TitleScreenMode::Play ? 26 : 56, 71, Images::Title_Highlight);

    // if (arduboy.audio.enabled()) {
    //     PD::drawBitmap(119, 56, Images::Sound_On);
    // }
    // else {
    //     PD::drawBitmap(119, 56, Images::Sound_Off);
    // }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

        switch (titleScreenVars.index) {

            case TitleScreenMode::Play:
                gameState = GameState::IntroText_Init;
                break;

            case TitleScreenMode::HighScore:
                gameState = GameState::HighScore_NoFlash;
                break;

        }

    }

    if (PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN)) {
        
        // if (arduboy.audio.enabled()) {

        //     arduboy.audio.off(); 
        //     arduboy.audio.saveOnOff();

        // }
        // else {

        //     arduboy.audio.on(); 
        //     arduboy.audio.saveOnOff();

        // }

    }

    if (PC::buttons.pressed(BTN_LEFT)) {

        titleScreenVars.index = TitleScreenMode::Play;

    }

    if (PC::buttons.pressed(BTN_RIGHT)) {

        titleScreenVars.index = TitleScreenMode::HighScore;

    }

}

