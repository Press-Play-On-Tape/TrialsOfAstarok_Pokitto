#pragma once

#include "Pokitto.h"
#include "../../utils/Constants.h"

namespace Images {

    #include "Sky.h"
    #include "Underground_Brick.h"
    #include "Underground_Chain.h"
    #include "Outside_Exit_00.h"
    #include "Outside_Exit_01.h"
    #include "Underground_Exit_00.h"
    #include "Underground_Exit_01.h"
    #include "Platform.h"
    #include "SignPost_AboveGround.h"
    #include "SignPost_BelowGround.h"
    #include "TBrick_Outside.h"
    #include "TBrick_Underground.h"

    const uint8_t * const SignPost[] = { 
        SignPost_BelowGround,
        SignPost_AboveGround,
    };

    const uint8_t * const Tile_Brick[] = { 
        TBrick_Underground,
        TBrick_Outside,
    };

};
