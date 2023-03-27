//#include "../hdr/hook.hpp"
#include "../hdr/hax.hpp"
#include "../hdr/globals.hpp"
#include "../hdr/config.hpp"
#include "../hdr/il2cpp.h"

// DEFINE HOOK FUNCTIONS HERE
void InitHax()
{
    Globals::LocalPlayer = Unity::GameObject::Find("LocalPlayer");
    
    if (!Globals::LocalPlayer)
    {
        printf("[-] Cannot find LocalPlayer\n");
        return;
    }

    printf("Found local player @ 0x%p\n", Globals::LocalPlayer);

    Globals::Vitals = Globals::LocalPlayer->GetComponent("Vitals");
    if (!Globals::Vitals)
    {
        printf("[-] Cannot find Vitals\n");
        return;
    }

    printf("Found Vitals @ 0x%p\n", Globals::Vitals);

    Globals::Stats::Rest = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Rest");
    Globals::Stats::Health = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Health");
    Globals::Stats::Stamina = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Stamina");
    Globals::Stats::Fullness = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Fullness");
    Globals::Stats::Strength = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Strength");
    Globals::Stats::Hydration = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Hydration");
}

void HackLoop()
{
    if (!Globals::il2cpp_status)
        exit(1);

    if (!Globals::LocalPlayer)
    {
        printf("[-] Cannot find LocalPlayer\n");
        InitHax();
        return;
    }

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