#pragma once

#include <LibAudio>
#include "../Utils/SFXVolumeSource.hpp"

#include "01_Coin.h"
#include "01_Coin_8K.h"
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

    uint8_t themeToPlay_Next = 255;
    SoundSettings soundSettings_Next;
    FadeMode fadeMode = FadeMode::None;

    static inline uint16_t volume = 255;

    void connectVolumeControl(uint32_t lastChannel){
        Audio::connect(
            lastChannel,
            nullptr,
            +[](uint8_t *buffer, void *){
                for(int i=0; i<512; ++i) 
                    buffer[i] = buffer[i] * volume >> 8;
            }
        );
    }

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


    void updateFades() {

        switch (this->fadeMode) {

            case FadeMode::FadeIn:
                volume = volume + 8;
                if (volume >= 247) {
                    volume = 255;
                    this->fadeMode = FadeMode::None;
                }
                break;

            case FadeMode::FadeOut:

                volume = volume - 8;

                if (volume <= 8) {
                    
                    this->volume = 0;

                    if (this->themeToPlay_Next != 255) {
                        this->fadeMode = FadeMode::FadeIn;
                        this->playTheme(this->themeToPlay_Next, this->soundSettings_Next);
                    }
                    else {
                        this->fadeMode = FadeMode::None;
                    }

                }
                break;

            default: break;

        }

    }



    // Sound effects.

    void playTheme(uint8_t themeToPlay, SoundSettings soundSettings, bool ignoreFadeOut = false, bool ensureFullVolume = false) {

        constexpr char sounds[4][19] = { "music/Astaro01.raw", "music/Astaro02.raw", "music/Astaro03.raw", "music/Astaro04.raw" };

        if (volume > 0 && !ignoreFadeOut) {

            this->fadeMode = FadeMode::FadeOut;
            this->themeToPlay_Next = themeToPlay;
            this->soundSettings_Next = soundSettings;

        }
        else {

            this->themeToPlay_Next = 255;

            if (ensureFullVolume) volume = 255;

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
                        Audio::play<2>(sfx_08_OpenChest, 255, 1);        
                        break;
                    
                    #ifdef COIN_FROM_SD
                    case Sounds::Effects::PickUpCoin:
                        playSoundEffect_FromSD(soundEffect);
                        break;
                    #else
                    case Sounds::Effects::PickUpCoin:
                        Audio::play<2>(sfx_01_Coin_8K, 255, 2);
                        break;
                    #endif

                    case Sounds::Effects::LandOnTop:
                        Audio::play<2>(sfx_05_Stomp, 255, 1);        
                        break;

                    case Sounds::Effects::Jump:
                        Audio::play<2>(sfx_06_Jump, 255, 1);        
                        break;

                    case Sounds::Effects::Die:
                        Audio::stop<0>();
                        Audio::play<3>(sfx_02_Die, 255, 1);        
                        break;

                    case Sounds::Effects::OneUp:
                        Audio::play<2>(sfx_03_One_Up, 255, 1);        
                        break;

                    case Sounds::Effects::ButtonPress:
                        Audio::play<2>(sfx_04_Beep, 255, 1);        
                        break;           

                    case Sounds::Effects::Fail:
                        Audio::play<2>(sfx_10_Fail, 255, 1);        
                        break;           

                }

                break;

            default: break;

        }

    }    


    void playSoundEffect_FromSD(Sounds::Effects soundEffect) {

        constexpr char sounds[1][19] = { "music/Astaro05.raw" }; // Coins

        if (this->soundEffectFile.openRO(sounds[0])) {
            this->music = &Audio::play<2>(soundEffectFile);
            this->music->setLoop(false);
        }

    }
    
};