#include "Pokitto.h"
#include <LibAudio>
#include "src/utils/Constants.h"
#include "src/utils/GameCookie.h"
#include "src/utils/Enums.h"
#include "src/Astarok.h"
#include "src/utils/DuelPalette.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;

Audio::Sink<2, PROJ_AUD_FREQ> audio;

int main() {
    
    cookie.begin("Astarok", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(duel);  
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(149);
    PC::setFrameRate(40);
    PD::textWrap = false;
    PD::setFont(font3x5);


    // Has the cookie been initialised?

    if (cookie.initialised != COOKIE_INITIALISED) {

        cookie.initialise();

    }

    game.setup(&cookie);
    
    while (PC::isRunning()) {

        if (!PC::update()) continue;
        game.loop();

    }
    
    return 0;
}
