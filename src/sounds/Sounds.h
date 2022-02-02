#pragma once

#include <LibAudio>
#include "../Utils/SFXVolumeSource.hpp"

#include "OpenChest.h"
#include "PickUpCoin.h"

extern File mainThemeFile;
extern Audio::RAWFileSource *music;

struct Sounds {

    enum class Effects : uint8_t {
        OpenChest,
        PickUpCoin,
    };


    // Sound effects.

    void playTheme(uint8_t themeToPlay, uint8_t &currentTheme, bool mute, bool updateTheme) {

        // constexpr char sounds[5][19] = { "music/roadtr03.raw", "music/roadtr04.raw", 
        //                                 "music/roadtr05.raw", "music/roadtr01.raw", 
        //                                 "music/roadtr02.raw",  };

        // if (!mute) {

        //     if (!updateTheme || currentTheme != themeToPlay) {

        //         if (mainThemeFile.openRO(sounds[themeToPlay])) {
        //             auto& music = Audio::play<0>(mainThemeFile);
        //             music.setLoop(true);
        //         }

        //         if (updateTheme) currentTheme = themeToPlay;

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
                    Audio::play<1>(sfx_PickUpCoin, 255, 1);        
                    break;
                                        
            }

        #endif

    }    
    
};