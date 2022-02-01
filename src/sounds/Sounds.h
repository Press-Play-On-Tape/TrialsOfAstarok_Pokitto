#pragma once

namespace Sounds {

    const uint16_t Theme[] PROGMEM = {
        // NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85,
        // NOTE_CS4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,428, NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85,
        // NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85, NOTE_CS4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,428,
        // NOTE_C4,171, NOTE_REST,171, NOTE_C4,171, NOTE_REST,171, NOTE_CS4,342, NOTE_REST,428, NOTE_C4,85, NOTE_REST,85,
        // NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85, NOTE_CS4,85, NOTE_REST,85,
        // NOTE_C4,85, NOTE_REST,428, NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,85,
        // NOTE_C4,85, NOTE_REST,85, NOTE_CS4,85, NOTE_REST,85, NOTE_C4,85, NOTE_REST,428, NOTE_C4,85, NOTE_REST,85,
        // NOTE_CS4,85, NOTE_REST,85, NOTE_D4,85, NOTE_REST,85, NOTE_CS4,85, NOTE_REST,85, NOTE_C4,85,
        // TONES_END
    };

    const uint16_t NewLevel[] PROGMEM = {
        // NOTE_A6,40, 0, 5, NOTE_C6,40,  0, 5,  NOTE_E6,40, 0, 5, NOTE_G6,40,  0, 5, 
        // TONES_END 
    };

    const uint16_t Dying[] PROGMEM = {
        // NOTE_G5, 50, NOTE_E5, 50, NOTE_C5, 50, NOTE_A5, 50,
        // NOTE_F4, 50, NOTE_D4, 50, NOTE_B4, 50,
        // NOTE_G3, 50, NOTE_E3, 50, NOTE_C3, 50, NOTE_A3, 50,
        // NOTE_F2, 50, NOTE_D2, 50, NOTE_B2, 50,
        // NOTE_B2, 50, NOTE_REST, 20, NOTE_B2, 50, NOTE_REST, 20, NOTE_B2, 50,
        // TONES_END
    };

    const uint16_t OpenChest[] PROGMEM =  { 
        // NOTE_A4,75, NOTE_B4,75, NOTE_CS5,75, NOTE_G5,150, NOTE_DS5,150, TONES_END 
    };

    const uint16_t LandOnTop[] PROGMEM =  { 
        // NOTE_A4,75, NOTE_B4,75, NOTE_CS5,75, TONES_END 
    };

    const uint16_t Jump[] PROGMEM = { 
        // NOTE_A2,20, TONES_END 
    };

    const uint16_t Coin[] PROGMEM = {
        // NOTE_C3, 70, NOTE_REST,20,
        // NOTE_C4, 70, NOTE_REST,20,
        // NOTE_C5, 70, NOTE_REST,20,
        // NOTE_C6, 70, NOTE_REST,20,
        // TONES_END
    };

    const uint16_t ButtonPress[] PROGMEM = { 
        // NOTE_A4, 20, TONES_END 
    };

};
