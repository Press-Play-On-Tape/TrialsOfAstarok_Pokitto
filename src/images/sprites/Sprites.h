#pragma once

#include "Pokitto.h"
#include "../../utils/Constants.h"

namespace Images {

    #include "Health.h"
    #include "Skull_LH.h"
    #include "Skull_RH.h"
    #include "Starman.h"
    #include "Spider_LH.h"
    #include "Spider_RH.h"
    #include "Bolt.h"
    #include "Fireball_Up.h"
    #include "Fireball_Down.h"
    #include "Pirahna_Up_00.h"
    #include "Pirahna_Up_01.h"
    #include "Pirahna_Down_00.h"
    #include "Pirahna_Down_01.h"
    #include "MemoryMan.h"

    const uint8_t * const Pirahna_Up[] = { 
        Pirahna_Up_00,
        Pirahna_Up_01,
    };

    const uint8_t * const Pirahna_Down[] = { 
        Pirahna_Down_00,
        Pirahna_Down_01,
    };

};
