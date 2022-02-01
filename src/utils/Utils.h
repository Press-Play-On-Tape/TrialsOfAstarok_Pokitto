#pragma once

#include "Pokitto.h"
#include "Enums.h"
#include "Structs.h"
// #include "../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

namespace Utils {

    static inline bool collide(Rect rect1, Rect rect2) {
        return !(rect2.x                >= rect1.x + rect1.width  ||
                 rect2.x + rect2.width  <= rect1.x                ||
                 rect2.y                >= rect1.y + rect1.height ||
                 rect2.y + rect2.height <= rect1.y);
    }
    
    
    // This gets the length of an array at compile time
    template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {
        return N;
    }
    
    
    static inline uint16_t getFrameCount() {
    
        return Pokitto::Core::frameCount;
    
    }
    
    static inline uint16_t getFrameCount(uint16_t mod) {
    
        return (Pokitto::Core::frameCount % mod);
    
    }
    
    static inline bool getFrameCountHalf(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) > (mod /2));
    
    }
    
    static inline bool isFrameCount(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) == 0);
    
    }
    
    static inline bool isFrameCount(uint16_t mod, uint16_t val) {
        
        return ((Pokitto::Core::frameCount % mod) == val);
    
    }
    
    
    static inline void drawDottedColumn(uint8_t x, uint8_t sy, uint8_t ey) {
        
        for (uint8_t y = sy; y <= ey; y = y + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    static inline void drawDottedRow(uint8_t sx, uint8_t ex, uint8_t y) {
        
        for (uint8_t x = sx; x <= ex; x = x + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    
    /* ----------------------------------------------------------------------------
     *  Return the upper 4 bits of a byte.
     */
    static uint8_t leftValue(uint8_t val) {
    
      return val >> 4; 
          
    }
    
    
    /* ----------------------------------------------------------------------------
     *  Return the lower 4 bits of a byte.
     */
    static uint8_t rightValue(uint8_t val) {
    
      return val & 0x0F; 
          
    }
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint8_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint8_t value) {
    
      for (uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint16_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint16_t value) {
    
      for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }

    static inline bool sfxOver() {

        // return ( PS::sfxDataPtr >= PS::sfxEndPtr );

    }

    static void stopSfx() {

        // PS::sfxDataPtr = PS::sfxEndPtr;

    }

    static void playSoundEffect(SoundEffects soundEffect) {

        // switch (soundEffect) {
            
        //     case SoundEffects::JumpObstacle:
        //         PS::playSFX(Sounds::sfx_02_Jump_Over_Obstacle, Sounds::sfx_02_Jump_Over_Obstacle_length);
        //         break;
            
        //     case SoundEffects::Jump:
        //         PS::playSFX(Sounds::sfx_07_Jump, Sounds::sfx_07_Jump_length);
        //         break;
            
        //     case SoundEffects::Pause:
        //         PS::playSFX(Sounds::sfx_03_Pause, Sounds::sfx_03_Pause_length);
        //         break;
            
        //     case SoundEffects::ThrowKey:
        //         PS::playSFX(Sounds::sfx_04_ThrowKey, Sounds::sfx_04_ThrowKey_length);
        //         break;
            
        //     case SoundEffects::KongPound:
        //         PS::playSFX(Sounds::sfx_05_KongPound, Sounds::sfx_05_KongPound_length);
        //         break;
            
        //     case SoundEffects::Collide:
        //         PS::playSFX(Sounds::sfx_06_Collide, Sounds::sfx_06_Collide_length);
        //         break;
            
        //     case SoundEffects::Unlock:
        //         PS::playSFX(Sounds::sfx_12_Unlock, Sounds::sfx_12_Unlock_length);
        //         break;
            
        //     case SoundEffects::Silence:
        //         PS::playSFX(Sounds::sfx_09_Silence, Sounds::sfx_09_Silence_length);
        //         break;
                    
        // }

    }    

        // ----------------------------------------------------------------------------
    //  Start a stream from the SD card .. 
    //
    static void playMusicStream(SoundEffects stream) {

        // #ifdef INCLUDE_SOUND_FROM_SD
        // switch (stream) {

        //     case SoundEffects::Introduction:
        //         PS::playMusicStream("music/kong2_1.raw", 0);
        //         break;

        //     case SoundEffects::GameOver:
        //         PS::playMusicStream("music/kong2_2.raw", 0);
        //         break;

        //     case SoundEffects::FreeKong:
        //         PS::playMusicStream("music/kong2_3.raw", 0);
        //         break;

        //     case SoundEffects::Silence:
        //         PS::playMusicStream("music/kong2_4.raw", 0);
        //         break;

        // }
        // #endif

    }
    
}