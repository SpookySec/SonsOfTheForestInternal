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

    namespace Value
    {
        inline float health = 10.f;
        inline float stamina = 10.f;
        inline float fullness = 10.f;
        inline float rest = 10.f;
        inline float strength = 10.f;
        inline float hydration = 10.f;
    }
}