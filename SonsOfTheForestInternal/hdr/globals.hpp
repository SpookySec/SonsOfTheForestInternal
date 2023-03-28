#pragma once
#include "../ext/imgui/imgui.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

#include "../ext/kiero/kiero.h"
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "hook.hpp"
#include "gui.hpp"
#include "../ext/il2cppresolver/Il2CppResolver.hpp"
#include "il2cpp.h"

namespace Globals
{
    inline uintptr_t GameAssembly{ NULL };
    inline Unity::CGameObject* LocalPlayer;
    inline Unity::CComponent* PlayerVisibility;
    inline Unity::CComponent* FirstPersonCharacter;
    inline Unity::CComponent* Vitals;

    namespace Stats
    {
        inline Unity::CObject* Rest;
        inline Unity::CObject* Health;
        inline Unity::CObject* Stamina;
        inline Unity::CObject* Fullness;
        inline Unity::CObject* Strength;
        inline Unity::CObject* Hydration;
    }

    namespace ResetStats
    {
        inline bool resetVisibility = true;
        inline bool resetStamina = true;
        inline bool resetHealth = true;
        inline bool resetFullness = true;
        inline bool resetRest = true;
        inline bool resetStrength = true;
        inline bool resetHydration = true;
        inline bool resetJumpHeight = true;
        inline bool resetSpeed = true;
    }

    namespace Gui
    {
        inline Present oPresent;
        inline HWND window = NULL;
        inline WNDPROC oWndProc;
        inline ID3D11Device* pDevice = NULL;
        inline ID3D11DeviceContext* pContext = NULL;
        inline ID3D11RenderTargetView* mainRenderTargetView;

        inline ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse;
    }

    inline bool il2cppStatus = false;
    inline bool exitThread = false;
    inline bool initHManager = false;
}

inline void(__fastcall* oDoFallDamage)(FirstPersonCharacter_o* __this);
