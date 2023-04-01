#include "../hdr/gui.hpp"
#include "../hdr/globals.hpp"
#include "../hdr/config.hpp"
#include "../hdr/hax.hpp"

#include "../hdr/font_awesome.h"
#include "../hdr/font_byte.h"

#define WIDTH 800
#define HEIGHT 450
#define BUTTON_HEIGHT 40
#define BUTTON_RATIO 3

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImGuiWindowFlags windowFlags;
ImGuiTableFlags tableFlags;
ImGuiTableColumnFlags columnFlags;

ImFont* bedstead;
ImFont* fontawesome;

namespace Settings
{
    static int Tab = 0;
}

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

    ImGui_ImplWin32_Init(Globals::Gui::window);
    ImGui_ImplDX11_Init(Globals::Gui::pDevice, Globals::Gui::pContext);

    bedstead = io.Fonts->AddFontFromFileTTF("C:\\Users\\spooky\\AppData\\Local\\Microsoft\\Windows\\Fonts\\Bedstead.ttf", 18.f, NULL, NULL);
    fontawesome = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 18.0f, &icons_config, icons_ranges);
    io.Fonts->AddFontDefault();
    ImGuiStyle* style = &ImGui::GetStyle();

    windowFlags = ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoBringToFrontOnFocus | //ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoCollapse;

    tableFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerV;

    ImGui::StyleColorsDark();

    style->WindowPadding = ImVec2(6, 1);// ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 2.5f;
    style->ItemSpacing = ImVec2(12, 4.5);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
    //style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImColor(14, 14, 14, 255);
    //style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
    //style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImColor(25, 25, 25, 255);
    style->Colors[ImGuiCol_FrameBgHovered] = ImColor(35, 35, 35, 255);
    style->Colors[ImGuiCol_FrameBgActive] = ImColor(35, 35, 35, 255);
    style->Colors[ImGuiCol_TitleBg] = ImColor(100, 12, 12, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(100, 12, 12, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(100, 12, 12, 255);
    //style->Colors[ImGuiCol_MenuBarBg] = ImColor(100, 12, 12, 255);
    //style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    //style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    //style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    //style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImColor(200, 200, 200, 255);
    style->Colors[ImGuiCol_SliderGrab] = ImColor(130, 130, 130, 255);
    style->Colors[ImGuiCol_SliderGrabActive] = ImColor(200, 200, 200, 255);
    style->Colors[ImGuiCol_Button] = ImColor(25, 25, 25, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(35, 35, 35, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(40, 40, 40, 255);
    //style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    //style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    //style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    //style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    //style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    //style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    //style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    //style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
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
    if (!render)
        return;
    static ImVec4 active = ImColor(40, 40, 40, 255).Value;
    static ImVec4 inactive = ImColor(25, 25, 25, 255).Value;

    ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT), ImGuiCond_Once);
    ImGui::Begin("Cheat menu | SpookySec#6710", &::render, windowFlags);

    if (ImGui::BeginTable("main", 2, tableFlags))
    {
        ImGui::TableNextColumn();
        // BUTTONS HERE
        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);

        if (ImGui::Button(ICON_FA_HEART" VITALS  ", ImVec2(WIDTH / BUTTON_RATIO, BUTTON_HEIGHT)))
            Settings::Tab = 1;

        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
        if (ImGui::Button(ICON_FA_CHILD" MOVEMENT", ImVec2(WIDTH / BUTTON_RATIO, BUTTON_HEIGHT)))
            Settings::Tab = 2;

        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 3 ? active : inactive);
        if (ImGui::Button(ICON_FA_EYE" ESP     ", ImVec2(WIDTH / BUTTON_RATIO, BUTTON_HEIGHT)))
            Settings::Tab = 3;

        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 4 ? active : inactive);
        if (ImGui::Button(ICON_FA_ELLIPSIS_H" MISC    ", ImVec2(WIDTH / BUTTON_RATIO, BUTTON_HEIGHT)))
            Settings::Tab = 4;


        ImGui::SetCursorPos(ImVec2(6, ImGui::GetWindowHeight() - (BUTTON_HEIGHT + 5)));
        ImGui::PushStyleColor(ImGuiCol_Button, ImColor(100, 12, 12, 255).Value);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(120, 12, 12, 255).Value);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(130, 12, 12, 255).Value);

        if (ImGui::Button("EJECT", ImVec2(WIDTH / BUTTON_RATIO, BUTTON_HEIGHT)))
        {
            Globals::exitThread = true;
        }

        ImGui::PopStyleColor(6);
        ImGui::TableNextColumn();

        if (Settings::Tab == 1)
        {
            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(40, BUTTON_HEIGHT - 35));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(80, 3983));
            ImGui::Checkbox("Edit Rest", &Config::bRest);
            ImGui::Checkbox("Edit Health", &Config::bHealth);
            ImGui::Checkbox("Edit Stamina", &Config::bStamina);
            ImGui::Checkbox("Edit Fullness", &Config::bFullness);
            ImGui::Checkbox("Edit Strength", &Config::bStrength);
            ImGui::Checkbox("Edit Hydration", &Config::bHydration);

            if (Config::bRest)
                ImGui::SliderFloat("Rest", &Config::Value::rest, 1.f, 150.f, "%.1f");

            if (Config::bHealth)
                ImGui::SliderFloat("Health", &Config::Value::health, 1.f, 150.f, "%.1f");

            if (Config::bStamina)
                ImGui::SliderFloat("Stamina", &Config::Value::stamina, 1.f, 150.f, "%.1f");

            if (Config::bFullness)
                ImGui::SliderFloat("Fullness", &Config::Value::fullness, 1.f, 150.f, "%.1f");

            if (Config::bStrength)
                ImGui::SliderFloat("Strength", &Config::Value::strength, 1.f, 150.f, "%.1f");

            if (Config::bHydration)
                ImGui::SliderFloat("Hydration", &Config::Value::hydration, 1.f, 150.f, "%.1f");

            ImGui::PopStyleVar(2);
            ImGui::PopItemWidth();
        }

        if (Settings::Tab == 2)
        {
            ImGui::Checkbox("No Fall Damage", &Config::bFallDamage);
            ImGui::Checkbox("Edit Jump Height", &Config::bJump);
            ImGui::Checkbox("Edit Movement / Swimming Speed", &Config::bSpeed);

            if (Config::bJump)
            {
                ImGui::SliderFloat("Jump height", &Config::Value::jumpHeight, 1.f, 200.f, "%.1f");
                Config::bFallDamage = true;
            }

            if (Config::bSpeed)
            {
                ImGui::SliderFloat("Running speed", &Config::Value::runSpeed, 1.f, 200.f, "%.1f");
                ImGui::SliderFloat("Swimming speed", &Config::Value::swimSpeedMultiplier, 1.f, 200.f, "%.1f");
            }
        }

        if (Settings::Tab == 3)
        {
            ImGui::Checkbox("Enable Enemy ESP", &Config::bESP);
            ImGui::Checkbox("Edit ESP Distance", &Config::bESPDistance);
            //// ADD SOME CODE FOR SPECIFIC ESP

            if (Config::bESPDistance)
                ImGui::SliderFloat("ESP Distance", &Config::Value::espDistance, 0.f, 1000.f);
        }

        if (Settings::Tab == 4)
        {
            ImGui::Checkbox("Invisibility", &Config::bInvisible);
            ImGui::Checkbox("Giant Mode", &Config::bGiant);

            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.45f);
            if (Config::bGiant)
                ImGui::SliderInt("Scale", &Config::Value::giantScale, 1, 1000);

            ImGui::PopItemWidth();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}