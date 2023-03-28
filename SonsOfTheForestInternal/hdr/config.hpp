#pragma once

// Define configs here

namespace Config
{
    inline bool bHealth = false;
    inline bool bStamina = false;
    inline bool bFullness = false;
    inline bool bRest = false;
    inline bool bStrength = false;
    inline bool bHydration = false;
    inline bool bInvisible = false;
    inline bool bSpeed = false;
    inline bool bJump = false;
    inline bool bFallDamage = false;

    namespace Value
    {
        inline float health = 50.f;
        inline float stamina = 50.f;
        inline float fullness = 50.f;
        inline float rest = 50.f;
        inline float strength = 50.f;
        inline float hydration = 50.f;

        inline float jumpHeight = 2.6f;
        inline float runSpeed = 5.4f;
        inline float swimSpeedMultiplier = 1.f;
    }
}