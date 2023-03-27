#pragma once
#include "../ext/imgui/imgui.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

#include "../ext/kiero/kiero.h"
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"
//#include "hook.hpp"
#include "gui.hpp"
#include "../ext/il2cppresolver/Il2CppResolver.hpp"

namespace Globals
{
    // Possible global vars here
    //inline Hooks::HooksManager HookManager;
    inline Unity::CGameObject* LocalPlayer;
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
        inline bool resetStamina = true;
        inline bool resetHealth = true;
        inline bool resetFullness = true;
        inline bool resetRest = true;
        inline bool resetStrength = true;
        inline bool resetHydration = true;
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

    inline bool il2cpp_status = false;
}