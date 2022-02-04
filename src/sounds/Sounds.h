#pragma once

#include <LibAudio>
#include "../Utils/SFXVolumeSource.hpp"

#include "01_Coin.h"
//#include "02_Level_Theme.h"
//#include "03_Level Theme.h"
// #include "04_Invincible.h"
// #include "05_Round_Cleared.h"
// #include "06_Boss.h"
// #include "07_Ending.h"
// #include "08_Name_Entry.h"
#include "09_Die.h"
// #include "10_Game_Over.h"
// #include "11_One_Up.h"
// #include "12_Get_Skateboard_Fairy-Mushroom.h"
// #include "13_Unknown.h"
// #include "14_Unknown_2.h"
#include "smb_stomp.h"
#include "smb_jump_small.h"
#include "smb_bump.h"
#include "OpenChest.h"

extern File mainThemeFile;
extern Audio::RAWFileSource *music;

struct Sounds {

    enum class Effects : uint8_t {
        OpenChest,
        PickUpCoin,
        LandOnTop,
        Jump,
        Die,
    };


    // Sound effects.

    void playTheme(uint8_t themeToPlay, bool mute) {

        // constexpr char sounds[2][19] = { "music/Astaro01.raw", "music/Astaro02.raw" };

        // if (!mute) {

        //     if (mainThemeFile.openRO(sounds[themeToPlay])) {
        //         auto& music = Audio::play<0>(mainThemeFile);
        //         music.setLoop(true);
        //     }

        // }
        // else {

        //     Audio::stop<0>();

        // }

    }

    void playSoundEffect(Sounds::Effects soundEffect) {

        #ifdef SOUNDS
            
            uint8_t vol = 255;

            //if (!music->ended()) { return; }

            switch (soundEffect) {
                
                case Sounds::Effects::OpenChest:
                    Audio::play<1>(sfx_OpenChest, 128, 1);        
                    break;
                
                case Sounds::Effects::PickUpCoin:
                    Audio::play<1>(sfx_01_Coin, 255, 1);        
                    break;

                case Sounds::Effects::LandOnTop:
                    Audio::play<1>(sfx_smb_stomp, 255, 1);        
                    break;

                case Sounds::Effects::Jump:
                    Audio::play<1>(sfx_smb_jump_small, 255, 1);        
                    break;

                case Sounds::Effects::Die:
                    Audio::play<1>(sfx_09_Die, 255, 1);        
                    break;
            }

        #endif

    }    
    
};