#include "AstarokGame.h"

#include "utils/Utils.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;

AstarokGame::AstarokGame() {

    this->player.game = this;
    this->level.game = this;

    for (AISprite &mobileObject : this->mobs) {

        mobileObject.game = this;

    }

    for (InteractiveObject &interactiveObject : this->level.objects) {

        interactiveObject.game = this;

    }

}

void AstarokGame::newGame() {

    this->score = 0;
    this->lives = 1;
    this->mapNumber = 1;
    this->player.init(Data::Astarok, 24, spawnY());

    startLevel();

}

void AstarokGame::startLevel() {

    //this->sound->tones(Sounds::NewLevel);

    this->level.newMap();
    this->player.init(Data::Astarok, 24, spawnY());
    this->player.facing = Direction::Right;
    this->cameraOffset = 35;

    while (this->player.isFalling()) {
        this->player.move();
    }

    adjustCamera();

    this->event = EventType::StartLevel;
    this->eventCounter = Constants::EventCounter_LevelStart;

}

uint8_t AstarokGame::spawnY() {

    if (this->mapNumber % 2) return 0;
    else return 88;

}

void AstarokGame::processButtons() {

    uint8_t MaxSpeed = 3; //SJHarduboy->pressed(A_BUTTON) ? 4 : 3;

    if (!(PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && !(PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1))) {
        if (this->player.vx > 0) this->player.vx--;
        if (this->player.vx < 0) this->player.vx++;
    }

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1))  { 
    
        this->player.facing = Direction::Left;
        this->player.vx--; 
    
        if (this->player.vx < MaxSpeed * -1) {
            this->player.vx = MaxSpeed * -1; 
        }

    }

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) { 

        this->player.facing = Direction::Right;
        this->player.vx++; 

        if (this->player.vx > MaxSpeed) {
            this->player.vx = MaxSpeed; 
        }
    }

    if (PC::buttons.pressed(BTN_B)) {

        if (!this->player.isFalling()) {
            if (this->player.jump()) {
                this->player.continuousBButton = true;
                sounds.playSoundEffect(Sounds::Effects::Jump);
            }
        }

    }

    else if (this->player.continuousBButton && (PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 1))) {

        if (this->player.isFalling()) {

            if (this->player.jumpBoost < 6) {

                this->player.jumpBoost++;

                if (this->player.jumpBoost % 2 == 0) this->player.vy-=2;

            }
            else if (this->player.jumpBoost < 12) {

                this->player.jumpBoost++;

                if (this->player.jumpBoost % 2 == 0) this->player.vy--;

            }

        }

    }

    else  {
        this->player.continuousBButton = false;
    }

    // if (PC::buttons.pressed(BTN_A)) {
    //     this->player.x = 1600;
    // }

}

void AstarokGame::adjustCamera() {

    int16_t maxX = this->level.maxXPixel() - 110;
    int16_t maxY = this->level.maxYPixel() - 88;
    int16_t minX = this->level.minXPixel();

    if (this->player.facing == Direction::Right) {

        this->camera.x = this->player.x - this->cameraOffset; 

        if (this->cameraOffset > 35) {
            this->cameraOffset--;
        }

    }
    else {
            
        this->camera.x = this->player.x - this->cameraOffset; // Center X on player

        if (this->cameraOffset < 65) {
            this->cameraOffset++;
        }

    }

    this->camera.y = this->player.y - 15;


    // Constrain for map edges ..

    if (this->camera.y > maxY) this->camera.y = maxY;
    if (this->camera.x > maxX) this->camera.x = maxX;
    if (this->camera.x < minX) this->camera.x = minX;


    // Reload map data ..

    this->level.loadMap();

}

void AstarokGame::cycle(GameState &gameState) {

    int mapPixelHeight = this->level.maxYPixel();

    this->processButtons();



    // Handle any events that are still active ..

    switch (this->event) {

        case EventType::Death_Init:
        case EventType::Death:

            switch (this->eventCounter) {

                case Constants::EventCounter_Death - 2 ... Constants::EventCounter_Death:  // bump up before going down
                    this->player.y--;
                    break;

                case 1 ... Constants::EventCounter_Death - 3:
                    this->player.y+=2;
                    break;

            }

            if (this->player.y > mapPixelHeight) {
                this->eventCounter = 0;
            }
            else {
                this->eventCounter--;
            }

            break;

        case EventType::Playing:
            this->player.move();
            adjustCamera();
            break;

        case EventType::StartLevel:
            if (this->eventCounter > 0) {
                this->eventCounter--;
                if (this->eventCounter == 0) {
                    this->event = EventType::Playing;
                }
            }
            break;

        case EventType::Flash:
            this->player.move();
            adjustCamera();
            if (this->eventCounter > 0) {
                this->eventCounter--;
                if (this->eventCounter == 0) {
                    this->event = EventType::Playing;
                }
            }
            break;

        default: break;

    }


    // Have we touched any interactive objects (EOL, chests, etc) ..

    for (InteractiveObject &obj : this->level.objects) {

        if (obj.x >= 0) {

            Rect playerRect = this->player.getRect();
            Rect objRect = { obj.x * Constants::TileSize, obj.y * Constants::TileSize, Constants::TileSize, Constants::TileSize };

            switch (obj.getType()) {

                case ObjectTypes::Chest_Closed:
                    objRect.width = 20;
                    break;

                case ObjectTypes::AboveGroundExit:
                case ObjectTypes::UnderGroundExit:
                    objRect.x = (obj.x * Constants::TileSize) - 2;
                    playerRect.width = 12;
                    break;

                default: break;

            }
            
            if (Utils::collide(playerRect, objRect)) {
                    
                switch (obj.getType()) {

                    case ObjectTypes::AboveGroundExit:
                    case ObjectTypes::UnderGroundExit:

                        this->event = EventType::LevelExit;
                        this->eventCounter = 0;

                        break;

                    case ObjectTypes::Coin:

                        obj.deactivate();
                        this->score += Constants::Points_Coin;
                        printf("start of PUC\n");
                        sounds.playSoundEffect(Sounds::Effects::PickUpCoin);

                        break;

                    case ObjectTypes::Chest_Closed:
                        
                        if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {
                            
                            gameState = GameState::Game_Mini;

                            this->chestObj = &obj;
                            this->ballDirection = Direction::Left;
                            this->ballX = 15;
                            this->ballIdx = 5;
                            this->ballDelay = 4;

                        }

                        break;

                    default: break;

                }

            }

        }

    }


    // Handle the movement of sprites ..

    bool isFalling = this->player.isFalling() && this->player.vy >= 0;

    for (AISprite &obj : this->mobs) {

        // Adjust explode counter if explostion is in action ..

        obj.updateExplosion();

        if (obj.getActive()) {

            switch (obj.getType()) {

                case ObjectTypes::Fireball:
                    if (this->event == EventType::Playing) {
                        obj.move();
                    }
                    break;

                case ObjectTypes::Health:
                    // Do nothing ..
                    break;

                default:

                    if (obj.y > mapPixelHeight) {
                        obj.deactivate(true);
                    }

                    obj.think();

                    if (obj.y > mapPixelHeight) {
                        obj.deactivate(true);
                    }

                    break;

            }


            // Have we touched another object?

            if (obj.getActive() && testCollision(&player, &obj)) {
              
                uint8_t type = obj.getType();

                switch (type) {

                    case ObjectTypes::Health:
                        obj.deactivate(true);
                        this->score += Constants::Points_Health;
                        if (this->lives < 3) this->lives++;
                        break;

                    case ObjectTypes::Coin:
                        obj.deactivate(false);
                        this->score += Constants::Points_Coin;
                        sounds.playSoundEffect(Sounds::Effects::PickUpCoin);
                        break;
                        
                    default: break;

                }

                if (obj.getActive()) { // May have been deativated just above (ie. a health) ..

                    if (isFalling) { // And therefore landing on top of an object

                        switch (type) {

                            case ObjectTypes::Fireball:

                                #ifndef NO_DEATH

                                if (event != EventType::Flash) {

                                    if (this->lives > 0) this->lives--; 

                                    if (this->lives == 0) {

                                        if (this->eventCounter == 0) {
                                            
                                            this->event = EventType::Death_Init; 
                                            this->eventCounter = Constants::EventCounter_Death;   
                                            //this->sound->tones(Sounds::Dying);
                                            obj.deactivate(true);

                                        }

                                    }
                                    else {

                                        #ifndef NO_DEATH
                                        this->event = EventType::Flash; 
                                        this->eventCounter = Constants::EventCounter_Flash;
                                        //this->sound->tones(Sounds::Dying);
                                        #endif

                                    }

                                }

                                #endif

                                break;

                            default:

                                obj.deactivate(true);
                                this->score += Constants::Points_Skill;
                                sounds.playSoundEffect(Sounds::Effects::LandOnTop);


                                // Get a bounce if we are pressing 'A' ..

                                if ((PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 1))) { 
                                    this->player.vy = -8;
                                }
                                else { 
                                    this->player.vy = -3; 
                                } 

                                break;

                        }

                    }
                    else if (this->eventCounter == 0) {

                        if (this->lives > 0) this->lives--; 

                        if (this->lives == 0) {

                            #ifndef NO_DEATH
                            this->event = EventType::Death_Init; 
                            this->eventCounter = Constants::EventCounter_Death;
                            //this->sound->tones(Sounds::Dying);
                            #endif

                        }
                        else {

                            #ifndef NO_DEATH
                            this->event = EventType::Flash; 
                            this->eventCounter = Constants::EventCounter_Flash;
                            //this->sound->tones(Sounds::Dying);
                            #endif

                        }

                    }

                }

            }

        }

    }

    switch (this->event) {

        case EventType::Playing:

            if (this->player.y > mapPixelHeight) { 

                this->lives = 0;
                this->event = EventType::Death_Init; 
                //this->sound->tones(Sounds::Dying);
                this->eventCounter = Constants::EventCounter_Death - 3; 

            }

            if (this->eventCounter > 0) this->eventCounter--;
            break;

        case EventType::Death_Init:
        case EventType::Death:

            if (this->eventCounter == 0) {

                die(gameState);

            }
            break;

        case EventType::LevelExit:
        
            this->eventCounter = 0;
            this->mapNumber++;
            this->player.x = 10;
            this->player.y = spawnY();
            startLevel();
            break;

        default: break;

    }

}

bool AstarokGame::testCollision(Sprite * player, AISprite * sprite) {

    Rect rect1 = player->getRect();
    Rect rect2 = sprite->getRect();

    return Utils::collide(rect1, rect2);

}

void AstarokGame::die(GameState &gameState) {

    if (this->lives > 0) {

        this->player.init(Data::Astarok,  10, spawnY());
        startLevel();

    }
    else {

        if (this->event == EventType::Death_Init) {
            this->event = EventType::Death;
        }


        // Move to High Score mode .. 

        if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
            gameState = GameState::HighScore_Check;
            this->event = EventType::Off;
        }

    }

}

uint8_t AstarokGame::addMob(const uint8_t *data, int16_t x, uint8_t y, uint8_t maxHeight) {

    int distances[Constants::SpriteCap];

    for (uint8_t a = 0; a < Constants::SpriteCap; a++) {

        if (!this->mobs[a].getActive()) {

            this->mobs[a].activate(data, x, y); 

            if (maxHeight != 255) {
                this->mobs[a].maxHeight = maxHeight * Constants::TileSize;
            }

            return a; 
        }

        distances[a] = this->player.x - this->mobs[a].x;
        if (distances[a] < 0) distances[a] *= -1;

    }

    uint8_t distance = distances[0];
    uint8_t candidate = 0;

    for (uint8_t a = 1; a < Constants::SpriteCap; a++) {
        if (distances[a] > distance) {
            candidate = a;
            distance = distances[a];
        }
    }

    this->mobs[candidate].activate(data, x, y);

    if (maxHeight != 255) {
        this->mobs[candidate].maxHeight = maxHeight * Constants::TileSize;
    }

    return candidate;

}

void AstarokGame::playMiniGame(GameState &gameState) {

    const uint8_t increments[] = { 1, 2, 3, 3, 3, 3, 3, 3, 3, 2, 1 }; // 27

    int16_t chestY = (this->chestObj->y * Constants::TileSize) - camera.y;
    uint8_t y = (chestY < 20 ? chestY + 16 : chestY - 17);
    uint8_t x = (this->chestObj->x * Constants::TileSize) - 8 - camera.x;

    PD::drawBitmap(x, y, Images::Frame);
    PD::drawBitmap(x + this->ballX + 4, y + 5, Images::Ball);


    switch (this->ballDirection) {

        case Direction::Left:
            this->ballX = this->ballX - increments[ballIdx];
            this->ballIdx--;
            if (this->ballIdx == 0) {
                this->ballDirection = Direction::Right;
            }
            break;

        case Direction::Right:
            this->ballX = this->ballX + increments[ballIdx];
            this->ballIdx++;
            if (this->ballIdx == 10) {
                this->ballDirection = Direction::Left;
            }
            break;
        
        default:
            break;

    }

    if (this->ballDelay == 0) {
        
        if (this->ballDirection != Direction::None) {

            if (PC::buttons.pressed(BTN_A)) {

                this->ballDirection = Direction::None;
                this->ballDelay = 24;
                sounds.playSoundEffect(Sounds::Effects::OpenChest);

            } 

        }
        else  {
            
            gameState = GameState::Game_Play;
            this->chestObj->type = ObjectTypes::Chest_Open;

            for (int i = 0; i < Constants::ParticlesMax; i++) {
                particles[i].setX((this->chestObj->x * Constants::TileSize) - this->camera.x + 8 + random(0, 7));
                particles[i].setY((this->chestObj->y * Constants::TileSize) - this->camera.y - 5 - random(0, 7));
                particles[i].setVelX(random(-5, 6));
                particles[i].setVelY(random(1, 5));
                particles[i].setCounter(random(15, 46));
            
            }

            if (this->ballIdx >= 4 && ballIdx <= 6) {
                this->addMob(Data::Health, this->chestObj->x, this->chestObj->y - 1);
            }
            else {

                for (uint8_t i = 0; i < 5; i++) {

                    this->addMob(Data::Coin, this->chestObj->x, this->chestObj->y - 1);

                }

            }

        }

    }
    else {
        this->ballDelay--;
    }

}
