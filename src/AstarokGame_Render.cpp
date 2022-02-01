#include "AstarokGame.h"

void AstarokGame::drawScorePanel() {

    PD::drawBitmap(6, 27, Images::GameOver);

}

void AstarokGame::drawMobs() {

    for (AISprite &obj : this->mobs) {

        if (obj.getActive() || obj.explodeCounter > 16) {

            if (obj.getRightX() - this->camera.x > 0 && obj.x - this->camera.x < 128) {
                obj.draw();
            }

        }

        if (obj.explodeCounter > 0) {

            PD::drawBitmap(obj.x - this->camera.x - 2, obj.y - this->camera.y - 2, 
                           Images::Puffs[(21 - obj.explodeCounter) / 3]); 
                        //    pgm_read_word_near(&Images::Puff_Masks[(21 - obj.explodeCounter) / 3]), 
                        //    this->mapNumber % 2 == 0 ? 0 : 1, 0);

        }

    }

}

void AstarokGame::drawHUD() {

    uint16_t tmpScore = this->score + this->player.x / Constants::TileSize; 
    uint8_t digits[6] = {};
    Utils::extractDigits(digits, tmpScore);

    PD::setColor(0);
    PD::fillRect(0, 0, 58, 8);

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        PD::drawBitmap(1, 1, Images::Heart[this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(9, 1, Images::Heart[this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(17, 1, Images::Heart[this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline]);

        for (uint8_t x = 6; x > 0; x--) {
            PD::drawBitmap(27 + ((6 - x) * 5), 1, Images::Numbers[digits[x - 1]]);
        }

    }
    else {

        PD::drawBitmap(1, 1, Images::Heart[this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(9, 1, Images::Heart[this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(17, 1, Images::Heart[this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline]);

        for (uint8_t x = 6; x > 0; x--) {
            PD::drawBitmap(27 + ((6 - x) * 5), 1, Images::Numbers[digits[x - 1]]);
        }

    }

}

void AstarokGame::drawMap_Background() {

    int16_t backgroundXOffset = (this->camera.x / 4) % 64;
    int16_t backgroundYOffset = (this->camera.y / 12) - 8;

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        for (uint8_t i = 0; i <= 128; i += 64) {
            PD::drawBitmap(i - backgroundXOffset, backgroundYOffset + 2, Images::Sky);
        }

    }
    else {

        for (uint8_t i = 0; i <= 128; i += 64) {

            PD::drawBitmap(i + 7 - backgroundXOffset, backgroundYOffset, Images::Underground_Chain);
            PD::drawBitmap(i + 22 - backgroundXOffset, backgroundYOffset + 6, Images::Underground_Brick);
            PD::drawBitmap(i + 42 - backgroundXOffset, backgroundYOffset + 11, Images::Underground_Brick);

        }

    }

    for (int x = (this->camera.x / Constants::TileSize) - 12; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (this->level.isTile(x, y)) {

                if (y == 15 || this->level.isTile(x, y + 1)) {

                    if (this->mapNumber % 2 == MapLevel::AboveGround) {   
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                                  Images::Tile_Brick[MapLevel::AboveGround]);
                    }
                    else {
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                                  Images::Tile_Brick[MapLevel::BelowGround]);
                    }

                }
                else {
                    PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Platform);

                }

            }
            else {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    // case ObjectTypes::QBlock ... ObjectTypes::Bricks:
                    //     PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::SpriteImages[tile]);
                    //     break;

                    case ObjectTypes::AboveGroundExit:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x - 36, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_00);
                        break;

                    case ObjectTypes::UnderGroundExit:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x - 13, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_00);
                        break;

                    case ObjectTypes::Sign:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x - 4, y * Constants::TileSize - this->camera.y - 4, Images::SignPost[this->mapNumber % 2]);
                        break;

                    case ObjectTypes::Coin:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Coins[Utils::getFrameCount(16) / 4]);
                        break;

                    case ObjectTypes::Chest_Closed:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 3, Images::Chest_Closed);
                        break;

                    case ObjectTypes::Chest_Open:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 2, Images::Chest_Open);
                        break;

                    default: break;
                }

            }

        }

    }

}

void AstarokGame::drawMap_Foreground() {

    for (int x = this->camera.x / Constants::TileSize; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (!this->level.isTile(x, y)) {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::AboveGroundExit:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x - 10, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_01);
                        break;

                    case ObjectTypes::UnderGroundExit:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_01);
                        break;

                    default: break;

                }

            }

        }

    }

}

void AstarokGame::drawPlayer() {


    // Render player ..

    switch (this->event) {

        case EventType::StartLevel:

            if (this->eventCounter < 12) { // Do not display for first half of puff cycle.
                this->player.draw();
            }

            break;

        case EventType::Death_Init:
        case EventType::Death:
        case EventType::Playing:   
        case EventType::Flash:   
            if (!(this->eventCounter % 2)) this->player.draw();
            break;

        default:
            this->player.draw();
            break;

    }


    // Render entrance puff of smoke ..

    if (this->event == EventType::StartLevel) { 

        PD::drawBitmap(this->player.x - this->camera.x - 2, this->player.y - this->camera.y - 4, 
                                  Images::Puffs[(28 - this->eventCounter) / 4]); 
                                //   pgm_read_word_near(&Images::Puff_Masks[(28 - this->eventCounter) / 4]), 
                                //   this->mapNumber % 2 == 0 ? 0 : 1, 0);

    }

}

void AstarokGame::draw() {

    drawMap_Background(); 
    drawPlayer(); 
    drawMobs(); 
    drawMap_Foreground(); 
    drawHUD();

    //arduboy->drawRect(player.getLeftX() - this->camera.x, player.getTopY() - this->camera.y, player.getWidth() - 3, player.getHeight(), BLACK);


    // Particles?

    for (uint8_t i = 0; i < Constants::ParticlesMax; i++) {

        this->particles[i].update();

        if (this->particles[i].render()) { // the dot should be rendered

            uint8_t pSize = particles[i].getSize();

            switch (pSize) {

                case 1:
                    PD::drawBitmap(this->particles[i].getX(), this->particles[i].getY(), Images::Pixel_01);
                    break;

                case 2:
                    PD::drawBitmap(this->particles[i].getX(), this->particles[i].getY(), Images::Pixel_02);
                    break;

                case 3:
                    PD::drawBitmap(this->particles[i].getX(), this->particles[i].getY(), Images::Pixel_03);
                    break;

            } 

        }

    }

}