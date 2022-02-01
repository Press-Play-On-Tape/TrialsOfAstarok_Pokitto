#include "Astarok.h"


const uint8_t textLengths[] = { 91, 84, 87 };

const uint8_t PROGMEM IntroText_00[] = { 8,'E','a','c','h',' ','y','e','a','r',' ','t','h','e',' ','p','e','o','p','l','e','~',2,'o','f',' ','t','h','e',' ','v','i','l','l','a','g','e', 
                            ' ','c','h','o','o','s','e',' ','a','~',2,'n','e','w',' ','c','h','a','m','p','i','o','n',' ','t','o',' ','p','r','o','t','e','c','t','~',14,'t',
                            'h','e','m',' ','f','r','o','m',' ','A','s','t','a','r','o','k','.' };

const uint8_t PROGMEM IntroText_01[] = { 7, 'C','o','m','p','e','t','e',' ','i','n',' ','t','h','e',' ','t','r','i','a','l','s','~',4,'t','o',' ','s','e','e',' ','h','o','w',' ','f','a',
                            'r',' ','y','o','u',' ','c','a','n','~',9,'g','e','t',' ','a','n','d',' ','y','o','u',' ','c','o','u','l','d',' ','b','e','~',23,'t','h','a','t',' ','c','h','a','m','p','i','o','n','!' };


const uint8_t PROGMEM IntroText_02[] = { 8,'Y','o','u','r',' ','c','h','o','i','c','e',' ','o','f',' ','r','u','n','e','s','~',6,'w','i','l','l',' ','s','e','l','e','c','t',' ',
                            'd','i','f','f','e','r','e','n','t','~',11,'c','o','u','r','s','e','s',' ','.','.',' ','s','o','m','e',' ','a','r','e','~',12,'e','a','s','i','e','r',
                            ' ','t','h','a','n',' ','o','t','h','e','r','s','!' };

const uint8_t * const IntroTexts[] = { IntroText_00, IntroText_01, IntroText_02 }; 

void Game::introText_Init() {

    introTextVars.reset();
    gameState = GameState::IntroText;

}

void Game::introText() {

    uint8_t line = 0;
    uint8_t x = 0;
    
    PD::drawBitmap(103, 13, Images::EnterRunes_01);
    PD::drawBitmap(103, 66, Images::EnterRunes_03);
    PD::drawBitmap(0, 13, Images::EnterRunes_00);
    PD::drawBitmap(0, 66, Images::EnterRunes_02);

    PD::setColor(2);
    PD::drawFastHLine(0, 13, 110);
    PD::drawFastHLine(0, 73, 110);
    PD::drawFastHLine(2, 75, 106);


    for (uint8_t i = 0; i < introTextVars.index; i++) {

        uint8_t c = pgm_read_byte(&IntroTexts[introTextVars.panel][i]);

        switch (c) {

            case '~':
                line++;
                x = 0;
                break;

            case 0 ... 31:
                x = x + c;
                break;

            case 'i':
            case 'j':
            case 't':
            case '!':
            case '.':
                PD::drawBitmap(1 + x, 25 + (line * 10), Font::Images[Font::getIndex(c)]);
                x = x + 4;
                break;

            case ' ':
                x = x + 3;
                break;
            
            default:
                PD::drawBitmap(1 + x, 25 + (line * 10), Font::Images[Font::getIndex(c)]);
                x = x + 5;
                break;

        }
        
    }

    if (introTextVars.index < textLengths[introTextVars.panel] && Utils::getFrameCount(2)) {

        introTextVars.index++;

    }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
        
        if (introTextVars.index == textLengths[introTextVars.panel] && introTextVars.skipTypewriter == false) {
            introTextVars.panel++;
            introTextVars.index = 0;
        }
        else {
            if (introTextVars.skipTypewriter) introTextVars.panel++;
            introTextVars.skipTypewriter = true;
            introTextVars.index = textLengths[introTextVars.panel];
        }

        if (introTextVars.panel == 3) gameState = GameState::Seed_Init;

    }

}

