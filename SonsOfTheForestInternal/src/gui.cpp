#include "../hdr/gui.hpp"
#include "../hdr/globals.hpp"
#include "../hdr/config.hpp"
#include "../hdr/hax.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InitGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    ImGui_ImplWin32_Init(Globals::Gui::window);
    ImGui_ImplDX11_Init(Globals::Gui::pDevice, Globals::Gui::pContext);
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
    ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);

    if (!render)
        return;

    ImGui::Begin("Cheat Menu", &::render, Globals::Gui::windowFlags);

    if (ImGui::BeginTabBar("Tabs", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Vitals", NULL, ImGuiTabItemFlags_None))
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
                ImGui::SliderFloat("Jump height", &Config::Value::jumpHeight, 1.f, 100.f);
                Config::bFallDamage = true;
            }

            if (Config::bSpeed)
            {
                ImGui::SliderFloat("Running speed", &Config::Value::runSpeed, 1.f, 100.f);
                ImGui::SliderFloat("Swimming speed", &Config::Value::swimSpeedMultiplier, 1.f, 100.f);
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc", NULL, ImGuiTabBarFlags_None))
        {
            ImGui::Checkbox("Invisibility", &Config::bInvisible);
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }

    if (ImGui::Button("EJECT"))
        Globals::exitThread = true;

    ImGui::End();
}