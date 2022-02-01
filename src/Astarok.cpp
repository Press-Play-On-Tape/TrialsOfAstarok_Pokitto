#include "Astarok.h"

#include "AstarokGame.h"
#include "src/images/Images.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/font/Font4x6.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

AstarokGame game();
GameState gameState = GameState::SplashScreen_Init;

TitleScreenVars titleScreenVars;
HighScoreVars highScoreVars;
IntroTextVars introTextVars;
SeedVars seedVars;

void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PC::buttons.pollButtons();

    switch (gameState) {

        case GameState::SplashScreen_Init:

            PD::clear();
            splashScreen_Init();
            [[fallthrough]]

        case GameState::SplashScreen:

            PD::clear();
            splashScreen();
            //arduboy.display(false);
            break;

        case GameState::Title_Init:

//            sound.tones(Sounds::Theme);
            PD::clear();
            gameState = GameState::Title;
            [[fallthrough]]

        case GameState::Title:

            PD::clear();
            titleScreen();
            //arduboy.display(true);
            break;

        case GameState::IntroText_Init:

            PD::clear();
            introText_Init();
            [[fallthrough]]

        case GameState::IntroText:

            PD::clear();
            introText();
            //arduboy.display(true);
            break;

        case GameState::Seed_Init:

            PD::clear();
            seed_Init();
            [[fallthrough]]

        case GameState::Seed:

            PD::clear();
            seed();
            //arduboy.display(true);
            break;

        case GameState::Game_Init:

            PD::clear();
            this->game.newGame();
            gameState = GameState::Game_Play;
            [[fallthrough]]

        case GameState::Game_Play:

            if (game.mapNumber % 2) {
                PD::fillScreen(7);
            }
            else {
                PD::clear();
            }

            game.cycle(gameState);
            game.draw();

            if (game.event == EventType::Death) {
                game.drawScorePanel();
            }

            break;

        case GameState::Game_Mini:

            if (game.mapNumber % 2) {
                PD::fillScreen(7);
            }
            else {
                PD::clear();
            }

            game.draw();
            game.playMiniGame(gameState);
            break;

        case GameState::HighScore_Check:

            PD::clear();
            highScoreVars.reset();
            checkHighScoreSlot(game.score + game.player.x / Constants::TileSize);

            if (highScoreVars.slot != Constants::No_Slot) {
                PC::frameCount = 0;
                gameState = GameState::HighScore_Flash;
            } 
            else {
                gameState = GameState::HighScore_NoFlash;
            }

            highScores();
            break;

        case GameState::HighScore_Flash:
        case GameState::HighScore_NoFlash:

            PD::clear();
            highScores();
            break;

    }

}