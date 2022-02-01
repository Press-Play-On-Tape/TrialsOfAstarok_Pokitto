#pragma once

#include "Pokitto.h"

namespace Images {

    #include "Left/PlayerIdle_Left_00.h"
    #include "Left/PlayerIdle_Left_01.h"
    #include "Left/PlayerIdle_Left_02.h"
    #include "Right/PlayerIdle_Right_00.h"
    #include "Right/PlayerIdle_Right_01.h"
    #include "Right/PlayerIdle_Right_02.h"

    const uint8_t * const Player_Idle[] = { 
        PlayerIdle_Left_00,
        PlayerIdle_Left_01,
        PlayerIdle_Left_02,
        PlayerIdle_Right_00,
        PlayerIdle_Right_01,
        PlayerIdle_Right_02,
    };

    #include "Left/PlayerWalking_Left_00.h"
    #include "Left/PlayerWalking_Left_01.h"
    #include "Left/PlayerWalking_Left_02.h"
    #include "Left/PlayerWalking_Left_03.h"
    #include "Right/PlayerWalking_Right_00.h"
    #include "Right/PlayerWalking_Right_01.h"
    #include "Right/PlayerWalking_Right_02.h"
    #include "Right/PlayerWalking_Right_03.h"

    const uint8_t * const Player_Walking[] = { 
        PlayerWalking_Left_00,
        PlayerWalking_Left_01,
        PlayerWalking_Left_02,
        PlayerWalking_Left_03,
        PlayerWalking_Right_00,
        PlayerWalking_Right_01,
        PlayerWalking_Right_02,
        PlayerWalking_Right_03,
    };

    #include "Left/PlayerJumpingUp_Left_00.h"
    #include "Right/PlayerJumpingUp_Right_00.h"

    const uint8_t * const Player_Jumping[] = { 
        PlayerJumpingUp_Left_00,
        PlayerJumpingUp_Right_00,
    };

};
