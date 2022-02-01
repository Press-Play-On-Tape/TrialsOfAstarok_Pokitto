#pragma once

#include "Pokitto.h"
#include "../../utils/Constants.h"

namespace Images {

    #include "Title.h"
    #include "Title_Highlight.h"
    #include "EnterRunes_Text.h"
    #include "EnterRunes_00.h"
    #include "EnterRunes_01.h"
    #include "EnterRunes_02.h"
    #include "EnterRunes_03.h"
    #include "Sound_On.h"
    #include "Sound_Off.h"
    #include "ArrowUp.h"
    #include "ArrowDown.h"
    #include "GameOver.h"
    #include "TopThree.h"
    #include "HighScore_Pattern.h"
    #include "HighScore_Pattern2.h"

    #include "Torch_00.h"
    #include "Torch_01.h"
    #include "Torch_02.h"
    #include "Torch_03.h"

    #include "EmptyHeart.h"
    #include "FullHeart.h"

    #include "Numbers0.h"
    #include "Numbers1.h"
    #include "Numbers2.h"
    #include "Numbers3.h"
    #include "Numbers4.h"
    #include "Numbers5.h"
    #include "Numbers6.h"
    #include "Numbers7.h"
    #include "Numbers8.h"
    #include "Numbers9.h"

    const uint8_t * const Torch[] = { 
        Torch_00,
        Torch_01,
        Torch_02,
        Torch_03,
    };

    const uint8_t * const Heart[] = { 
        FullHeart,
        EmptyHeart,
    };

    const uint8_t * const Numbers[] = { 
        Numbers0,
        Numbers1,
        Numbers2,
        Numbers3,
        Numbers4,
        Numbers5,
        Numbers6,
        Numbers7,
        Numbers8,
        Numbers9,
    };

};