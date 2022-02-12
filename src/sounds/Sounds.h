#pragma once

#include <LibAudio>

#include "01_Coin.h"
#include "02_Die.h"
#include "03_One_Up.h"
#include "04_Beep.h"
#include "05_Stomp.h"
#include "06_Jump.h"
#include "07_Bump.h"
#include "08_OpenChest.h"
#include "09_Game_Over.h"
#include "10_Fail.h"

struct Sounds {

    File mainThemeFile;
    File soundEffectFile;
    Audio::RAWFileSource *music;

    enum class Effects : uint8_t {
        OpenChest,
        PickUpCoin,
        LandOnTop,
        Jump,
        Die,
        OneUp,
        ButtonPress,
        Fail,
    };


    // Sound effects.

    void playTheme(uint8_t themeToPlay, SoundSettings soundSettings) {

        constexpr char sounds[4][19] = { "music/Astaro01.raw", "music/Astaro02.raw", "music/Astaro03.raw", "music/Astaro04.raw" };

        switch (soundSettings) {

            case SoundSettings::Music:
            case SoundSettings::Both:

                if (this->mainThemeFile.openRO(sounds[themeToPlay])) {
                    auto& music = Audio::play<0>(this->mainThemeFile);
                    
                    if (themeToPlay <= 2) {
                        music.setLoop(true);
                    }
                    else {
                        music.setLoop(false);
                    }

                }

                break;

            case SoundSettings::SFX:
            case SoundSettings::None:
    
                Audio::stop<0>();
                break;

        }

    }

    void muteTheme() {

        Audio::stop<0>();        
        
    }

    void playSoundEffect(Sounds::Effects soundEffect, SoundSettings soundSettings) {

        switch (soundSettings) {

            case SoundSettings::SFX:
            case SoundSettings::Both:

                switch (soundEffect) {
                    
                    case Sounds::Effects::OpenChest:
                        Audio::play<1>(sfx_08_OpenChest);        
                        break;
                    
                    case Sounds::Effects::PickUpCoin:
                        playSoundEffect_FromSD(soundEffect);
                        break;

                    case Sounds::Effects::LandOnTop:
                        Audio::play<1>(sfx_05_Stomp);        
                        break;

                    case Sounds::Effects::Jump:
                        Audio::play<1>(sfx_06_Jump);        
                        break;

                    case Sounds::Effects::Die:
                        Audio::stop<0>();
                        Audio::play<1>(sfx_02_Die);        
                        break;

                    case Sounds::Effects::OneUp:
                        Audio::play<1>(sfx_03_One_Up);        
                        break;

                    case Sounds::Effects::ButtonPress:
                        Audio::play<1>(sfx_04_Beep);        
                        break;           

                    case Sounds::Effects::Fail:
                        Audio::play<1>(sfx_10_Fail);        
                        break;           

                }

                break;

            default: break;

        }

    }    


    void playSoundEffect_FromSD(Sounds::Effects soundEffect) {

        constexpr char sounds[1][19] = { "music/Astaro05.raw" }; // Coins

        if (this->soundEffectFile.openRO(sounds[0])) {
            this->music = &Audio::play<1>(soundEffectFile);
            this->music->setLoop(false);
        }

    }
    
};