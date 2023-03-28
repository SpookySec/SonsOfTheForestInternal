//#include "../hdr/hook.hpp"
#include "../hdr/hax.hpp"
#include "../hdr/globals.hpp"
#include "../hdr/config.hpp"
#include "../hdr/il2cpp.h"

#define PTRCAST(t, a) reinterpret_cast<t>(a)

void hkDoFallDamage(FirstPersonCharacter_o* __this)
{
    if (Config::bFallDamage)
        return;

    return oDoFallDamage(__this);
}

// DEFINE HOOK FUNCTIONS HERE
void InitHax()
{
    Globals::GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

    if (!Globals::initHManager)
    {
        if (MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
            MH_Initialize();

        MH_CreateHook(PTRCAST(LPVOID*, Globals::GameAssembly + 0x37BAFF0), &hkDoFallDamage, (LPVOID*)&oDoFallDamage);
        MH_EnableHook(PTRCAST(LPVOID*, Globals::GameAssembly + 0x37BAFF0));
    }
    Globals::LocalPlayer = Unity::GameObject::Find("LocalPlayer");
    
    if (!Globals::LocalPlayer)
    {
        printf("[-] Cannot find LocalPlayer\n");
        return;
    }

    printf("Found local player @ 0x%p\n", Globals::LocalPlayer);

    Globals::Vitals = Globals::LocalPlayer->GetComponent("Vitals");
    Globals::PlayerVisibility = Globals::LocalPlayer->GetComponent("PlayerVisibility");
    Globals::FirstPersonCharacter = Globals::LocalPlayer->GetComponent("FirstPersonCharacter");

    Globals::Stats::Rest = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Rested");
    Globals::Stats::Health = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Health");
    Globals::Stats::Stamina = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Stamina");
    Globals::Stats::Fullness = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Fullness");
    Globals::Stats::Strength = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Strength");
    Globals::Stats::Hydration = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Hydration");

    printf("Found PlayerVisibility @ 0x%p\n", Globals::PlayerVisibility);
    printf("Found FirstPersonCharacter @ 0x%p\n", Globals::FirstPersonCharacter);
}


void HackLoop()
{
    if (!Globals::il2cppStatus)
        exit(1);

    if (!Globals::LocalPlayer)
    {
        printf("[-] Cannot find LocalPlayer\n");
        InitHax();
        return;
    }

    // Check code above lmao
    StatHax();

    if (Config::bInvisible)
    {
        if (Globals::PlayerVisibility)
            Globals::PlayerVisibility->SetMemberValue<bool>("_invisible", true);

        else
            Globals::PlayerVisibility = Globals::LocalPlayer->GetComponent("PlayerVisibility");
    }
    else if (!Globals::ResetStats::resetVisibility)
    {
        Globals::ResetStats::resetVisibility = true;
        Globals::PlayerVisibility->SetMemberValue<bool>("_invisible", false);
    }

    if (Config::bJump)
    {
        if (Globals::FirstPersonCharacter)
            Globals::FirstPersonCharacter->SetMemberValue<float>("_jumpHeight", Config::Value::jumpHeight);

        else
            Globals::FirstPersonCharacter = Globals::LocalPlayer->GetComponent("FirstPersonCharacter");
    }
    else if (!Globals::ResetStats::resetJumpHeight)
    {
        Globals::ResetStats::resetJumpHeight = true;
        Globals::FirstPersonCharacter->SetMemberValue<float>("_jumpHeight", 2.6f);
    }

    if (Config::bSpeed)
    {
        if (Globals::FirstPersonCharacter)
        {
            Globals::FirstPersonCharacter->SetMemberValue<float>("_runSpeed", Config::Value::runSpeed);
            Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeed", 2.f);
            Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeedMultiplier", Config::Value::swimSpeedMultiplier);
        }
        else
            Globals::FirstPersonCharacter = Globals::LocalPlayer->GetComponent("FirstPersonCharacter");
    }
    else if (!Globals::ResetStats::resetSpeed)
    {
        Globals::ResetStats::resetSpeed = true;
        Globals::FirstPersonCharacter->SetMemberValue<float>("_runSpeed", 5.4f);
        Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeedMultiplier", 1.f);
    }
}
void StatHax()
{
    // REST 
    if (Config::bRest)
    {
        if (!Globals::Stats::Rest)
            return;

        Globals::Stats::Rest->SetMemberValue<float>("_currentValue", Config::Value::rest);
        Globals::ResetStats::resetRest = false;
    }
    else if (!Globals::ResetStats::resetRest)
    {
        Globals::ResetStats::resetRest = true;
        float _defaultvalue = Globals::Stats::Rest->GetMemberValue<float>("_defaultValue");
        Globals::Stats::Rest->SetMemberValue<float>("_currentValue", _defaultvalue);
    }

    // HEALTH
    if (Config::bHealth)
    {
        if (!Globals::Stats::Health)
            return;

        Globals::Stats::Health->SetMemberValue<float>("_currentValue", Config::Value::health);
        Globals::ResetStats::resetHealth = false;
    }
    else if (!Globals::ResetStats::resetHealth)
    {
        Globals::ResetStats::resetHealth = true;
        float _defaultvalue = Globals::Stats::Health->GetMemberValue<float>("_defaultValue");
        Globals::Stats::Health->SetMemberValue<float>("_currentValue", _defaultvalue);
    }

    // STAMINA
    if (Config::bStamina)
    {
        if (!Globals::Stats::Stamina)
            return;

        Globals::Stats::Stamina->SetMemberValue<float>("_currentValue", Config::Value::stamina);
        Globals::ResetStats::resetStamina = false;
    }
    else if (!Globals::ResetStats::resetStamina)
    {
        Globals::ResetStats::resetStamina = true;
        float _defaultvalue = Globals::Stats::Stamina->GetMemberValue<float>("_defaultValue");
        Globals::Stats::Stamina->SetMemberValue<float>("_currentValue", _defaultvalue);
    }

    // FULLNESS
    if (Config::bFullness)
    {
        if (!Globals::Stats::Fullness)
            return;

        Globals::Stats::Fullness->SetMemberValue<float>("_currentValue", Config::Value::fullness);
        Globals::ResetStats::resetFullness = false;
    }
    else if (!Globals::ResetStats::resetFullness)
    {
        Globals::ResetStats::resetFullness = true;
        float _defaultvalue = Globals::Stats::Fullness->GetMemberValue<float>("_defaultValue");
        Globals::Stats::Fullness->SetMemberValue<float>("_currentValue", _defaultvalue);
    }

    // STRENGTH
    if (Config::bStrength)
    {
        if (!Globals::Stats::Strength)
            return;

        Globals::Stats::Strength->SetMemberValue<float>("_currentValue", Config::Value::strength);
        Globals::ResetStats::resetStrength = false;
    }
    else if (!Globals::ResetStats::resetStrength)
    {
        Globals::ResetStats::resetStrength = true;
        float _defaultvalue = Globals::Stats::Strength->GetMemberValue<float>("_defaultValue");
        Globals::Stats::Strength->SetMemberValue<float>("_currentValue", _defaultvalue);
    }

    // HYDRATION
    if (Config::bHydration)
    {
        if (!Globals::Stats::Hydration)
            return;

        Globals::Stats::Hydration->SetMemberValue<float>("_currentValue", Config::Value::hydration);
        Globals::ResetStats::resetHydration = false;
    }
    else if (!Globals::ResetStats::resetHydration)
    {
        Globals::ResetStats::resetHydration = true;
        float _defaultvalue = Globals::Stats::Hydration->GetMemberValue<float>("_defaultValue");
        Globals::Stats::Hydration->SetMemberValue<float>("_currentValue", _defaultvalue);
    }
}
