// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <thread>
#include <MinHook.h>
#include <d3d11.h>
#include <string>

#include "../hdr/utils.hpp"
#include "../hdr/hax.hpp"
#include "../hdr/config.hpp"
#include "../hdr/globals.hpp"

#include "../ext/il2cppresolver/Il2CppResolver.hpp"

void HackThread(LPVOID hModule)
{
    FILE* fp = NULL;
    MH_STATUS hax_status = MH_ERROR_NOT_INITIALIZED;
    bool kiero_status = false;

    fp = CreateConsole();
    
    printf("[+] DLL injected!\n");

    Globals::il2cpp_status = IL2CPP::Initialize(true);
    if (!Globals::il2cpp_status)
        exit(1);

    InitHax();

    printf("[+] IL2CPP Resolver initialized!\n");

    do
    {
        try
        {
            if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
            {
                printf("[+] Kiero init success\n");
                kiero::bind(8, (void**)&Globals::Gui::oPresent, hkPresent);
                kiero_status = true;
            }
        }

        catch (...) {
            printf("FAILED\n");
        }
    } while (!kiero_status);

    printf("[+] Kiero hooks created successfully!\n");
    printf("[+] Cheat hooks created successfully!\n");

    //FreeConsole();
    //fclose(fp);
    while (!GetAsyncKeyState(VK_END))
        Sleep(200);

    kiero::shutdown();
    MH_DisableHook(MH_ALL_HOOKS);
    FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        const HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, NULL);

        if (hThread)
            CloseHandle(hThread); // so?
    }

    return TRUE;
}

