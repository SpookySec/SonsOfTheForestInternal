#include "../hdr/gui.hpp"
#include "../hdr/globals.hpp"
#include "../hdr/config.hpp"
#include "../hdr/hax.hpp"
#include "../hdr/font_awesome.h"
#include "../hdr/font_byte.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImFont* bigIcons;

void InitGui()
{
    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 2.5;
    icons_config.OversampleV = 2.5;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 18.0f, &icons_config, icons_ranges);
    ImGui_ImplWin32_Init(Globals::Gui::window);
    bigIcons = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 18.01f, NULL, icons_ranges);
    ImGui_ImplDX11_Init(Globals::Gui::pDevice, Globals::Gui::pContext);

    ImGuiStyle* style = &ImGui::GetStyle();

    // THEME STOLEN FROM https://www.unknowncheats.me/forum/c-and-c-/189635-imgui-style-settings.html
    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5); 
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
}

HRESULT EndGui(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    kiero::shutdown();
    Globals::Gui::pDevice->Release();
    Globals::Gui::pContext->Release();
    Globals::Gui::oWndProc = (WNDPROC)SetWindowLongPtr(Globals::Gui::window, GWLP_WNDPROC, (LONG_PTR)(Globals::Gui::oWndProc));
    return Globals::Gui::oPresent(pSwapChain, SyncInterval, Flags);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(Globals::Gui::oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
bool render = true;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (Globals::exitThread)
        return EndGui(pSwapChain, SyncInterval, Flags);

    if (GetAsyncKeyState(VK_INSERT) & 1)
        render = !render;

    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&Globals::Gui::pDevice)))
        {
            Globals::Gui::pDevice->GetImmediateContext(&Globals::Gui::pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            Globals::Gui::window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            Globals::Gui::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &Globals::Gui::mainRenderTargetView);
            pBackBuffer->Release();
            Globals::Gui::oWndProc = (WNDPROC)SetWindowLongPtr(Globals::Gui::window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitGui();
            init = true;
        }

        else
            return Globals::Gui::oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Menu(render);
    HackLoop();

    //ImGui::ShowDemoWindow();

    ImGui::Render();

    Globals::Gui::pContext->OMSetRenderTargets(1, &Globals::Gui::mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return Globals::Gui::oPresent(pSwapChain, SyncInterval, Flags);
}
void Menu(bool render)
{
    ImGui::SetNextWindowSizeConstraints(ImVec2(225, 360), ImVec2(400, 400));
    ImGui::SetNextWindowSize(ImVec2(225, 360), ImGuiCond_Once);

    if (!render)
        return;

    ImGui::Begin("Cheat Menu | SpookySec#6710", &::render, Globals::Gui::windowFlags);

    if (ImGui::BeginTabBar("Tabs", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem(ICON_FA_HEART "Vitals", NULL, ImGuiTabItemFlags_None))
        {
            ImGui::Checkbox("Edit Rest", &Config::bRest);
            ImGui::Checkbox("Edit Health", &Config::bHealth);
            ImGui::Checkbox("Edit Stamina", &Config::bStamina);
            ImGui::Checkbox("Edit Fullness", &Config::bFullness);
            ImGui::Checkbox("Edit Strength", &Config::bStrength);
            ImGui::Checkbox("Edit Hydration", &Config::bHydration);

            if (Config::bRest)
                ImGui::SliderFloat("Rest", &Config::Value::rest, 1.f, 150.f);

            if (Config::bHealth)
                ImGui::SliderFloat("Health", &Config::Value::health, 1.f, 150.f);

            if (Config::bStamina)
                ImGui::SliderFloat("Stamina", &Config::Value::stamina, 1.f, 150.f);

            if (Config::bFullness)
                ImGui::SliderFloat("Fullness", &Config::Value::fullness, 1.f, 150.f);

            if (Config::bStrength)
                ImGui::SliderFloat("Strength", &Config::Value::strength, 1.f, 150.f);

            if (Config::bHydration)
                ImGui::SliderFloat("Hydration", &Config::Value::hydration, 1.f, 150.f);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Movement", NULL, ImGuiTabItemFlags_None))
        {
            ImGui::Checkbox("No Fall Damage", &Config::bFallDamage);
            ImGui::Checkbox("Edit Jump Height", &Config::bJump);
            ImGui::Checkbox("Edit Movement / Swimming Speed", &Config::bSpeed);

            if (Config::bJump)
            {
                ImGui::SliderFloat(ICON_FA_FROG "Jump height", &Config::Value::jumpHeight, 1.f, 100.f);
                Config::bFallDamage = true;
            }

            if (Config::bSpeed)
            {
                ImGui::SliderFloat(ICON_FA_RUNNING "Running speed", &Config::Value::runSpeed, 1.f, 100.f);
                ImGui::SliderFloat(ICON_FA_FISH "Swimming speed", &Config::Value::swimSpeedMultiplier, 1.f, 100.f);
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc", NULL, ImGuiTabBarFlags_None))
        {
            ImGui::Checkbox(ICON_FA_EYE_SLASH "Invisibility", &Config::bInvisible);
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }

    if (ImGui::Button("EJECT", ImVec2(ImGui::GetWindowContentRegionWidth() * .999, 20)))
        Globals::exitThread = true;

    ImGui::End();
}