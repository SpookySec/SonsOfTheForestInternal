//#include "../hdr/hook.hpp"
#include "../hdr/hax.hpp"
#include "../hdr/globals.hpp"
#include "../hdr/config.hpp"
#include "../hdr/il2cpp.h"

#include <cmath>

#define PTRCAST(t, a) reinterpret_cast<t>(a)

// DEFINE HOOK FUNCTIONS HERE
void InitHax()
{
    Globals::GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

    if (!Globals::initHManager)
    {
        if (MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
            MH_Initialize();

        // POSSIBLE HOOKS HERE
    }

    Globals::LocalPlayer = Unity::GameObject::Find("LocalPlayer");
    Globals::VailActorManagerParent = Unity::GameObject::Find("_VailActorManager_");
    Globals::MainCamera = Unity::Camera::GetMain();

    printf("[+] Found VailActorManagerParent @ 0x%p\n", Globals::VailActorManagerParent);

    
    if (!Globals::LocalPlayer)
    {
        printf("[-] Cannot find LocalPlayer\n");
        return;
    }

    printf("[+] Found local player @ 0x%p\n", Globals::LocalPlayer);

    Globals::Vitals = Globals::LocalPlayer->GetComponent("Vitals");
    Globals::PlayerVisibility = Globals::LocalPlayer->GetComponent("PlayerVisibility");
    Globals::FirstPersonCharacter = Globals::LocalPlayer->GetComponent("FirstPersonCharacter");
    Globals::VailActorManager = Globals::VailActorManagerParent->GetComponent("Sons.Ai.Vail.VailActorManager");

    Globals::VailActors = Globals::VailActorManager->GetMemberValue<Unity::il2cppList<Unity::CComponent*>*>("_activeActors");

    Globals::Stats::Rest = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Rested");
    Globals::Stats::Health = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Health");
    Globals::Stats::Stamina = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Stamina");
    Globals::Stats::Fullness = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Fullness");
    Globals::Stats::Strength = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Strength");
    Globals::Stats::Hydration = Globals::Vitals->GetPropertyValue<Unity::CObject*>("Hydration");

    printf("[+] Found MainCamera @ 0x%p\n", Globals::MainCamera);
    printf("[+] Found VailActorManager @ 0x%p\n", Globals::VailActorManager);
    printf("[+] Found PlayerVisibility @ 0x%p\n", Globals::PlayerVisibility);
    printf("[+] Found FirstPersonCharacter @ 0x%p\n", Globals::FirstPersonCharacter);
    printf("[+] Found List<VailActors> @ 0x%p\n", Globals::VailActors);
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

    if (!Globals::VailActorManager)
    {
        printf("[-] Cannot find VailActorManager\n");
        InitHax();
        return;
    }

    // Check code above lmao
    StatHax();

    ESPHax();

    if (Config::bGiant)
    {
        Globals::LocalPlayer->GetTransform()->SetLocalScale(Unity::Vector3(Config::Value::giantScale, Config::Value::giantScale, Config::Value::giantScale));
    }
    else
    {
        Globals::LocalPlayer->GetTransform()->SetLocalScale(Unity::Vector3(1.f, 1.f, 1.f));
    }

    if (Config::bInvisible)
    {
        if (!Globals::PlayerVisibility)
            return;

        Globals::PlayerVisibility->SetMemberValue<bool>("_invisible", true);
        Globals::ResetStats::resetVisibility = false;
    }
    else if (!Globals::ResetStats::resetVisibility)
    {
        Globals::ResetStats::resetVisibility = true;
        Globals::PlayerVisibility->SetMemberValue<bool>("_invisible", false);
    }

    if (Config::bJump)
    {
        if (!Globals::FirstPersonCharacter)
            return;

        Globals::FirstPersonCharacter->SetMemberValue<float>("_jumpHeight", Config::Value::jumpHeight);
        Globals::ResetStats::resetRest = false;
    }
    else if (!Globals::ResetStats::resetJumpHeight)
    {
        Globals::ResetStats::resetJumpHeight = true;
        Globals::FirstPersonCharacter->SetMemberValue<float>("_jumpHeight", 2.6f);
    }

    if (Config::bSpeed)
    {
        if (!Globals::FirstPersonCharacter)
            return;

        Globals::FirstPersonCharacter->SetMemberValue<float>("_runSpeed", Config::Value::runSpeed);
        Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeed", Config::Value::swimSpeedMultiplier);
        Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeedMultiplier", Config::Value::swimSpeedMultiplier);
        Globals::ResetStats::resetSpeed = false;
    }
    else if (!Globals::ResetStats::resetSpeed)
    {
        Globals::ResetStats::resetSpeed = true;
        Globals::FirstPersonCharacter->SetMemberValue<float>("_runSpeed", 5.4f);
        Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeed", 5.4f);
        Globals::FirstPersonCharacter->SetMemberValue<float>("_swimSpeedMultiplier", 1.f);
    }

    if (Config::bFallDamage)
    {
        if (Globals::FirstPersonCharacter)
            Globals::FirstPersonCharacter->SetMemberValue<bool>("_allowFallDamage", false);
    }
    else
        Globals::FirstPersonCharacter->SetMemberValue<bool>("_allowFallDamage", true);
    

    if (Config::bPosition)
    {
        Unity::Vector3 playerPosition = Globals::LocalPlayer->GetTransform()->GetPosition();

        char position[64];

        snprintf(position, 64, "(\n\tx: %.2f,\n\ty: %.2f,\n\tz: %.2f\n)", playerPosition.x, playerPosition.y, playerPosition.z);

        ImGui::GetForegroundDrawList()->AddText(ImVec2(15, 15), ImColor(255, 255, 255, 255), (const char*)position);

    }

}

void ESPHax()
{
    if (Config::bESP)
    {
        if (!Globals::MainCamera)
        {
            printf("[-] Camera not found!\n");
            Globals::MainCamera = Unity::Camera::GetMain();//Use GetMain directly because current does not exist
            return;
        }
        
        printf("[*] VailActors List @ 0x%p\n", Globals::VailActors);
        //printf("ESP ENABLED\n");
        if (!Globals::VailActors)
        {
            Globals::VailActors = Globals::VailActorManager->GetMemberValue<Unity::il2cppList<Unity::CComponent*>*>("_activeActors");
            return;
        }

        for (uintptr_t u = 0U; Globals::VailActors->ToArray()->m_uMaxLength > u; ++u)
        {
            Unity::Vector3 buffer{ 0,0,0 };
            Unity::Vector3 m_Position{ 0,0,0 };
            Unity::CComponent* VailActor{ 0 };

            try
            {
                printf("[%d] ===================\n", (int)u);
                VailActor = Globals::VailActors->ToArray()->operator[](u);

                printf("[*] VailActor @ 0x%p\n", VailActor);

                if (!VailActor)
                {
                    Globals::VailActors->m_pListArray->RemoveAt(u);
                    continue;
                }

                Unity::CTransform* m_pTransform = VailActor->GetTransform();
                m_Position = m_pTransform->GetPosition();

                // sometimes this value is below the world
                //if (m_Position.y <= 0.f || m_Position.z <= 0.f)
                //    continue;

                float _distanceFromTarget = VailActor->GetMemberValue<float>("_distanceFromTarget");
                Sleep(0.05);

                printf("[*] m_pTransoform @ 0x%p ( %f, %f, %f ) distance: %f\n", m_pTransform, m_Position.x, m_Position.y, m_Position.x, _distanceFromTarget);


                if (_distanceFromTarget <= 0.f)
                    continue;


                 
                // literally no idea how to solve this shit
                buffer = Globals::MainCamera->CallMethodSafe<Unity::Vector3, Unity::Vector3, int>("WorldToScreenPoint", m_Position, 2);
            }
            catch (...)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(100, 12, 12, 255).Value);
                if (ImGui::Begin("error", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar  | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground))
                {
                    ImGui::Text("You're experiencing a weird bug where the entlist is empty.\ncurrently I have no solution for this so forgive me lmao, just restart the game :)");
                    if (ImGui::Button("SHUT DOWN"))
                        for (; ;)
                            exit(1);

                }
                ImGui::PopStyleColor();

                ImGui::End();
                continue;
            }

            if (buffer.y < 1.f || buffer.z < 1.f)
                continue;

            Unity::Vector3 localPos = Globals::LocalPlayer->GetTransform()->GetPosition();

            float x1, x2, y1, y2, z1, z2;

            x1 = localPos.x;
            x2 = m_Position.x;

            y1 = localPos.y;
            y2 = m_Position.y;

            z1 = localPos.z;
            z2 = m_Position.z;

            float distance = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2) + std::pow(z1 - z2, 2));
            printf("[*] Distance: %f\n", distance);

            if (buffer.z < 0)
                continue;

            Sons_Ai_Vail_VailActor_o* il2cpp_VailActor = reinterpret_cast<Sons_Ai_Vail_VailActor_o*>(VailActor);
            int typeId = il2cpp_VailActor->fields._id;
            printf("[*] TypeId: TypeIdString[%d] = %s\n", typeId, TypeIdString[typeId]);

            // ENEMIES
            if (typeId == Fingers && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Andy && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Danny && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Billy && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Baby && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Twins && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == GoldMask && Config::bEnemies) {DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Slug && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == MuddyFemale && Config::bEnemies) {DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == MuddyMale && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == HeavyMale && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == FatMale && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == FatFemale && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == John2 && Config::bEnemies) {DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == FacelessMale && Config::bEnemies) {DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Demon && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == PaintedMale && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == PaintedFemale && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Carl && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == MrPuffy && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == MissPuffy && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Crystal && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Destiny && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Angel && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Brandy && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == Timmy && Config::bEnemies) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }

            // PEACEFUL ANIMALS
            if (typeId == Rabbit && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Squirrel && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Turtle && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Seagull && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Eagle && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Duck && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Moose && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Salmon && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Bat && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Deer && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Bluebird && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == Hummingbird && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }
            if (typeId == LandTurtle && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(12, 100, 12, 125)); }

            // HOSTILE ANIMALS
            if (typeId == Shark && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }
            if (typeId == KillerWhale && Config::bAnimals) { DrawESP(distance, typeId, buffer, ImColor(100, 12, 12, 125)); }

            // NPCs
            if (typeId == Robby && Config::bNPCs) { DrawESP(distance, typeId, buffer, ImColor(255, 255, 255, 125)); }
            if (typeId == Virginia && Config::bNPCs) { DrawESP(distance, typeId, buffer, ImColor(255, 255, 255, 125)); }


            //char distance_name_buffer[64];

            //snprintf(distance_name_buffer, 16, "%s\n%.1fm", TypeIdString[typeId], distance);

            //ImGui::GetBackgroundDrawList()->AddLine(ImVec2(1920 / 2, 1080), ImVec2(buffer.x, (1080 - buffer.y)), ImColor(255, 255, 255, 125), 1.5f);
            //ImGui::GetBackgroundDrawList()->AddText(ImVec2(buffer.x, 1080 - buffer.y), ImColor(255, 255, 255, 255), (const char*)distance_name_buffer);


            //printf("[*] ACTOR 0x%p (%f, %f, %f)\n", VailActor, m_Position.x, m_Position.y, m_Position.z);
        }

        Globals::VailActors = Globals::VailActorManager->GetMemberValue<Unity::il2cppList<Unity::CComponent*>*>("_activeActors");
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

void DrawESP(float distance, int typeId, Unity::Vector3 buffer, ImColor color)
{
    auto size = ImGui::GetIO().DisplaySize;

    if (Config::bESPDistance)
        if (distance >= Config::Value::espDistance)
            return;

    char distance_name_buffer[64];

    snprintf(distance_name_buffer, 16, "%s\n%.1fm", TypeIdString[typeId], distance);

    if (Config::bLines)
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(size.x / 2, size.y), ImVec2(buffer.x, (size.y - buffer.y)), color, 1.5f);

    ImGui::GetBackgroundDrawList()->AddText(ImVec2(buffer.x, size.y - buffer.y), color, (const char*)distance_name_buffer);
}