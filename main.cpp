// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"
#pragma comment(lib, "libMinHook.x64.lib")
#include "MinHook.h"
#include "imgui_hook.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

std::string ghostType = "None";
//std::string ghostName = "None";
std::string ghostName = "Empty";

using namespace app;

GhostAI* g_GhostStateInstance = nullptr;
u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34 thing;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using fn_changestate_ghostAI = void(*)(GhostAI* __this, GhostAI_u0D2Au0D1Du0D3Au0D21u0D1Cu0D29u0D21u0D37u0D29__Enum u0D2Cu0D39u0D1Cu0D3Au0D36u0D21u0D1Fu0D31u0D3A, PhotonObjectInteract* u0D2Fu0D22u0D1Fu0D2Du0D35u0D20u0D27u0D32u0D24, bool u0D3Bu0D3Bu0D35u0D2Du0D1Du0D3Au0D35u0D27u0D2F, MethodInfo* method);
static fn_changestate_ghostAI orig_changestate = nullptr;   

using fn_Init_GhostAI = void(*)(GhostAI* __this, u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34 u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34, MethodInfo* method);
static fn_Init_GhostAI orig_init_ghostAI = nullptr;

using fn_EvidenceController_SpawnAllGhostTypeEvidences = void(*)(EvidenceController* __this, u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34 u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21, MethodInfo* method);
static fn_EvidenceController_SpawnAllGhostTypeEvidences orig_spawnallghosttypeevidences = nullptr;

using fn_OnPlayerStartedKilling = void(*)(Player_1* __this, bool u0D2Fu0D35u0D2Au0D2Du0D2Fu0D24u0D26u0D24u0D25, PhotonMessageInfo u0D31u0D20u0D1Eu0D2Au0D28u0D37u0D2Bu0D28u0D3A, MethodInfo* method);
static fn_OnPlayerStartedKilling orig_onplayerstartkilling = nullptr;

void EnableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void getOffset(void* adr) {

    HMODULE gameAsm = GetModuleHandleA("GameAssembly.dll");
    uintptr_t base = reinterpret_cast<uintptr_t>(gameAsm);
    uintptr_t rtadr = reinterpret_cast<uintptr_t>(adr) - base;
    //std::cout << "[*] Hook / Method at offset " << reinterpret_cast<void*>(rtadr) << std::endl;
}

void consoleRED() {
    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

    std::cout << "\033[31m";
}
void consoleGREEN() {
	//SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    std::cout << "\033[32m";
}

void consoleBLUE() {
    //SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

    std::cout << "\033[34m";
}

void consoleRESET() {
    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    std::cout << "\033[0m";
}

// You need to find Present address first
// Here's a simple method using a dummy device:

HRESULT GetPresentAddress(void** pPresent) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"DX", NULL };
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow(wc.lpszClassName, NULL, WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, wc.hInstance, NULL);

    D3D_FEATURE_LEVEL featureLevel;
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    IDXGISwapChain* pSwapChain;
    ID3D11Device* pDevice;
    ID3D11DeviceContext* pContext;

    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, &featureLevel, &pContext))) {
        DestroyWindow(hWnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return E_FAIL;
    }

    // Get Present from vtable
    void** pVTable = *(void***)pSwapChain;
    *pPresent = pVTable[8]; // Present is at index 8

    pSwapChain->Release();
    pDevice->Release();
    pContext->Release();
    DestroyWindow(hWnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return S_OK;
}

// Then in your init:




void Hooked_EvidenceController_SpawnAllGhostTypeEvidences(EvidenceController* __this, u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34 u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21, MethodInfo* method) {
	consoleBLUE();
    std::cout << "[Intercepted] SpawnAllGhostTypeEvidence intercepted" << std::endl;
    consoleRESET();
    /*
    auto first_int = u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21.u0D23u0D28u0D39u0D31u0D2Eu0D1Cu0D32u0D34u0D3A;
    auto second_int = u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21.u0D20u0D1Du0D1Eu0D1Fu0D22u0D26u0D27u0D32u0D1C;
    auto third_int = u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21.u0D2Cu0D26u0D1Du0D3Au0D21u0D21u0D28u0D24u0D2A;
    auto fourth_int = u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21.u0D1Du0D22u0D38u0D1Du0D37u0D23u0D26u0D31u0D28;

	std::cout << "First int: " << first_int << std::endl;
	std::cout << "Second int: " << second_int << std::endl;
	std::cout << "Third int: " << third_int << std::endl;
    std::cout << "Fourth int: " << fourth_int << std::endl;
    
    */
    auto str = u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C;
    if (str == nullptr) {
        consoleRED();
        std::cout << "[!] Null referance instance protected" << std::endl;
        consoleRESET();
    }
    else {
        consoleGREEN();
        std::cout << "[Ingame Information] Ghost Name:";
        consoleRESET();
        const wchar_t* chars = reinterpret_cast<const wchar_t*>(&str->fields._firstChar);
        std::wcout << chars << std::endl;
        std::wstring temp(chars);
        std::string str2(temp.begin(), temp.end());

		ghostName = str2;
    }
    enum class u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34_u0D2Du0D36u0D25u0D35u0D36u0D29u0D2Fu0D24u0D1C__Enum : int32_t {
        Spirit = 0x00000000,
        Wraith = 0x00000001,
        Phantom = 0x00000002,
        Poltergeist = 0x00000003,
        Banshee = 0x00000004,
        Jinn = 0x00000005,
        Mare = 0x00000006,
        Revenant = 0x00000007,
        Shade = 0x00000008,
        Demon = 0x00000009,
        Yurei = 0x0000000a,
        Oni = 0x0000000b,
        Yokai = 0x0000000c,
        Hantu = 0x0000000d,
        Goryo = 0x0000000e,
        Myling = 0x0000000f,
        Onryo = 0x00000010,
        TheTwins = 0x00000011,
        Raiju = 0x00000012,
        Obake = 0x00000013,
        Mimic = 0x00000014,
        Moroi = 0x00000015,
        Deogen = 0x00000016,
        Thaye = 0x00000017,
        None = 0x00000018,
        Gallu = 0x00000019,
        Dayan = 0x0000001a,
        Obambo = 0x0000001b,
    };
    auto test = u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21.u0D1Fu0D20u0D34u0D38u0D21u0D37u0D2Au0D31u0D31;
	int value = static_cast<int>(test);
    consoleGREEN();
    switch (value) {
        case 0:
			std::cout << "[Ingame Information] Ghost type: Spirit" << std::endl;
			ghostType = "Spirit";
			break;
        case 1:
			std::cout << "[Ingame Information] Ghost type: Wraith" << std::endl;
			ghostType = "Wraith";
            break;
		case 2:
			std::cout << "[Ingame Information] Ghost type: Phantom" << std::endl;
			ghostType = "Phantom";
            break;
		case 3:
            std::cout << "[Ingame Information] Ghost type: Poltergeist" << std::endl;
			break;
        case 4:
		    std::cout << "[Ingame Information] Ghost type: Banshee" << std::endl;
            ghostType = "Banshee";
            break;
        case 5:
            std::cout << "[Ingame Information] Ghost type: Jinn" << std::endl;
            ghostType = "Jinn";
            break;
        case 6:
            std::cout << "[Ingame Information] Ghost type: Mare" << std::endl;
            ghostType = "Mare";
            break;
        case 7:
			std::cout << "[Ingame Information] Ghost type: Revenant" << std::endl;
            ghostType = "Revenant";
            break;
		case 8:
            std::cout << "[Ingame Information] Ghost type: Shade" << std::endl;
            ghostType = "Mare";
            break;
        case 9:
			std::cout << "[Ingame Information] Ghost type: Demon" << std::endl;
            ghostType = "Demon";
            break;
        case 10:
			std::cout << "[Ingame Information] Ghost type: Yurei" << std::endl;
            ghostType = "Yurei";
            break;
		case 11:
            std::cout << "[Ingame Information] Ghost type: Oni" << std::endl;
            ghostType = "Oni";
            break;
		case 12:
            std::cout << "[Ingame Information] Ghost type: Yokai" << std::endl;
            ghostType = "Yokai";
			break;
        case 13:
            std::cout << "[Ingame Information] Ghost type: Hantu" << std::endl;
            ghostType = "Hantu";
            break;
		case 14:
            std::cout << "[Ingame Information] Ghost type: Goryo" << std::endl;
            ghostType = "Goryo";
            break;
		case 15:
            std::cout << "[Ingame Information] Ghost type: Myling" << std::endl;
            ghostType = "Myling";
			break;
        case 16:
            std::cout << "[Ingame Information] Ghost type: Onryo" << std::endl;
            ghostType = "Onryo";
            break;
        case 17:
			std::cout << "[Ingame Information] Ghost type: TheTwins" << std::endl;
            ghostType = "TheTwins";
            break;
        case 18:
			std::cout << "[Ingame Information] Ghost type: Raiju" << std::endl;
            ghostType = "Raiju";
            break;
		case 19:
            std::cout << "[Ingame Information] Ghost type: Obake" << std::endl;
            ghostType = "Obake";
			break;
        case 20:
            std::cout << "[Ingame Information] Ghost type: Mimic" << std::endl;
            ghostType = "Mimic";
			break;
        case 21:
            std::cout << "[Ingame Information] Ghost type: Moroi" << std::endl;
            ghostType = "Moroi";
            break;
		case 22:
            std::cout << "[Ingame Information] Ghost type: Deogen" << std::endl;
            ghostType = "Deogen";
			break;
        case 23:
            std::cout << "[Ingame Information] Ghost type: Thaye" << std::endl;
            ghostType = "Thaye";
            break;
	    case 24:
            std::cout << "[Ingame Information] Ghost type: None" << std::endl;
            ghostType = "None";
            break;
		case 25:
            std::cout << "[Ingame Information] Ghost type: Gallu" << std::endl;
            ghostType = "Gallu";
            break;
		case 26:
            std::cout << "[Ingame Information] Ghost type: Dayan" << std::endl;
            ghostType = "Dayan";
            break;
        case 27:
            std::cout << "[Ingame Information] Ghost type: Obambo" << std::endl;
            ghostType = "Obambo";
            break;
        default:
            consoleRED();
            std::cout << "[Ingame Information] Unknown ghost type" << std::endl;
            ghostType = "Unknown";
			break;
    }
    consoleRESET();
    //std::cout << "Ghost Type Enum Value: " << value << std::endl;

    if (orig_spawnallghosttypeevidences) {
        orig_spawnallghosttypeevidences(__this, u0D3Au0D21u0D30u0D20u0D3Bu0D36u0D39u0D22u0D21, method);
        consoleBLUE();
        std::cout << "[Info] Relayed on to SpawnAllGhostTypeEvidences" << std::endl; 
        consoleRESET();
	}

}

void Hooked_ChangeStateAI(GhostAI* __this, GhostAI_u0D2Au0D1Du0D3Au0D21u0D1Cu0D29u0D21u0D37u0D29__Enum u0D2Cu0D39u0D1Cu0D3Au0D36u0D21u0D1Fu0D31u0D3A, PhotonObjectInteract* u0D2Fu0D22u0D1Fu0D2Du0D35u0D20u0D27u0D32u0D24, bool u0D3Bu0D3Bu0D35u0D2Du0D1Du0D3Au0D35u0D27u0D2F, MethodInfo* method) {
    consoleBLUE();
    std::cout << "[Interception] ChangeState intercepted" << std::endl;
    consoleRESET();
    g_GhostStateInstance = __this;

    enum class GhostAI_u0D2Au0D1Du0D3Au0D21u0D1Cu0D29u0D21u0D37u0D29__Enum : int32_t {
        idle = 0x00000000,
        wander = 0x00000001,
        hunting = 0x00000002,
        favouriteRoom = 0x00000003,
        light = 0x00000004,
        door = 0x00000005,
        throwing = 0x00000006,
        fusebox = 0x00000007,
        appear = 0x00000008,
        doorKnock = 0x00000009,
        windowKnock = 0x0000000a,
        carAlarm = 0x0000000b,
        flicker = 0x0000000c,
        cctv = 0x0000000d,
        randomEvent = 0x0000000e,
        GhostAbility = 0x0000000f,
        mannequin = 0x00000010,
        teleportObject = 0x00000011,
        interact = 0x00000012,
        summoningCircle = 0x00000013,
        musicBox = 0x00000014,
        dots = 0x00000015,
        salt = 0x00000016,
        ignite = 0x00000017,
    };
    auto test = u0D2Cu0D39u0D1Cu0D3Au0D36u0D21u0D1Fu0D31u0D3A;
    int value = static_cast<int>(test);
    consoleGREEN();
    switch (value) {
        case 0:
            std::cout << "[Info] Ghost State: idle" << std::endl;
			break;
            case 1:
            std::cout << "[Info] Ghost State: wander" << std::endl;
            break;
        case 2:
            consoleRED();
            std::cout << "[Info] Ghost State: hunting" << std::endl;
            break;
        case 3:
            std::cout << "[Info] Ghost State: favouriteRoom" << std::endl;
            break;
        case 4:
            std::cout << "[Info] Ghost State: light" << std::endl;
            break;
        case 5:
            std::cout << "[Info] Ghost State: door" << std::endl;
            break;
        case 6:
            std::cout << "[Info] Ghost State: throwing" << std::endl;
            break;
        case 7:
            std::cout << "[Info] Ghost State: fusebox" << std::endl;
            break;
        case 8:
            std::cout << "[Info] Ghost State: appear" << std::endl;
            break;
		case 9:
            std::cout << "[Info] Ghost State: doorKnock" << std::endl;
			break;
        case 10:
            std::cout << "[Info] Ghost State: windowKnock" << std::endl;
			break;
        case 11:
			std::cout << "[Info] Ghost State: carAlarm" << std::endl;
			break;
        case 12:
			std::cout << "[Info] Ghost State: flicker" << std::endl;
			break;
        case 13:
            std::cout << "[Info] Ghost State: cctv" << std::endl;
			break;
        case 14:
			std::cout << "[Info] Ghost State: randomEvent" << std::endl;
        case 15:
			std::cout << "[Info] Ghost State: GhostAbility" << std::endl;
			break;
        case 16:
			std::cout << "[Info] Ghost State: mannequin" << std::endl;
			break;
        case 17:
			std::cout << "[Info] Ghost State: teleportObject" << std::endl; 
			break;
		case 18:
			std::cout << "[Info] Ghost State: interact" << std::endl;
			break;
		case 19:
			std::cout << "[Info] Ghost State: summoningCircle" << std::endl;
			break;
		case 20:
			std::cout << "[Info] Ghost State: musicBox" << std::endl;
			break;
		case 21:
			std::cout << "[Info] Ghost State: dots" << std::endl;
			break;
		case 22:
			std::cout << "[Info] Ghost State: salt" << std::endl;
			break;
		case 23:
			std::cout << "[Info] Ghost State: ignite" << std::endl;
			break;
        default:
            consoleRED();
			std::cout << "[Info] Ghost State: Unknown state" << std::endl;
    }
	consoleRESET();



    if (orig_changestate) {
        orig_changestate(__this, u0D2Cu0D39u0D1Cu0D3Au0D36u0D21u0D1Fu0D31u0D3A, u0D2Fu0D22u0D1Fu0D2Du0D35u0D20u0D27u0D32u0D24, u0D3Bu0D3Bu0D35u0D2Du0D1Du0D3Au0D35u0D27u0D2F, method);
        consoleBLUE();
        std::cout << "[Info] Relayed on to ChangeState" << std::endl; 
        consoleRESET();
    }
}

static void* Hooked_OnPlayerStartedKilling(Player_1* __this, bool u0D2Fu0D35u0D2Au0D2Du0D2Fu0D24u0D26u0D24u0D25, PhotonMessageInfo u0D31u0D20u0D1Eu0D2Au0D28u0D37u0D2Bu0D28u0D3A, MethodInfo* method) {
    consoleBLUE();
    std::cout << "[Intercepted] OnPlayerStartedKilling intercepted" << std::endl;
    consoleRESET();
    consoleGREEN();
	std::cout << "[Info] Death intercepted" << std::endl;

    if (godMode) {
        std::cout << "[Info] GodMode is enabled, death prevented" << std::endl;
        return nullptr;
    }
    
    if (orig_onplayerstartkilling) {
        orig_onplayerstartkilling(__this, u0D2Fu0D35u0D2Au0D2Du0D2Fu0D24u0D26u0D24u0D25, u0D31u0D20u0D1Eu0D2Au0D28u0D37u0D2Bu0D28u0D3A, method);
        consoleBLUE();
        std::cout << "[Info] Relayed on to OnPlayerStartedKilling" << std::endl; 
        consoleRESET();
    }
}

DWORD WINAPI KeyCheckThread(LPVOID lpParam) {
    while (true) {
        if (GetAsyncKeyState(VK_F5) & 0x8000) {
            // Do stuff
            u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34 thing2 = thing;
            app::String* str = thing2.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C;

            if (str == nullptr) {
                consoleRED();
                std::cout << "[!] Null referance instance protected" << std::endl;
                consoleRESET();
                continue;
            }

            if (str->fields._stringLength == 0) {
                consoleRED();
                std::cout << "[!] Null referance instance protected" << std::endl;
                consoleRESET();
                continue;
            }


            const wchar_t* chars = reinterpret_cast<const wchar_t*>(&str->fields._firstChar);
            std::wcout << chars << std::endl;
			//ghostName = chars;

            Sleep(200); // Debounce
        }
        Sleep(10);
    }
    return 0;
}

void Hooked_Init_GhostAI(GhostAI* __this, u0D2Au0D1Eu0D31u0D32u0D37u0D36u0D2Fu0D36u0D34 u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34, MethodInfo* method) {
    consoleBLUE();
    std::cout << "[Intercepted] GhostAI intercepted" << std::endl;
    consoleRESET();
    //std::string what_is_this = il2cppi_to_string(u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C);
    // If the field is Il2CppString*:
    /*
    try {
        std::string name;
        for (int i = 0; i < u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C->fields._stringLength; i++)
            name += *((&u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C->fields._firstChar) + i);
        std::cout << name << std::endl;
    }
    catch (...) {
		std::cout << "Exception caught while trying to read Ghost Type by manual char access" << std::endl;
    }
    */
    
    
    // If the field is Il2CppString (by-value):
    //app::String& ghostTypeVal = u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C;
    //std::cout << "Ghost Type: " << il2cppi_to_string(&ghostTypeVal) << std::endl;
    //std::cout << "Ghost Type: " << il2cppi_to_string(u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C) << std::endl;
    //std::cout << u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D1Fu0D35u0D33u0D20u0D2Eu0D25u0D23u0D32u0D33 << std::endl;

    //std::cout << *u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D1Fu0D35u0D33u0D20u0D2Eu0D25u0D23u0D32u0D33 << std::endl;
    //std::cout << *u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D1Fu0D35u0D33u0D20u0D2Eu0D25u0D23u0D32u0D33 << std::endl;
	//std::cout << u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D24u0D34u0D33u0D25u0D20u0D2Au0D23u0D2Fu0D36 << std::endl;
	//std::cout << &u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D24u0D34u0D33u0D25u0D20u0D2Au0D23u0D2Fu0D36 << std::endl;

    if (orig_init_ghostAI) {
        orig_init_ghostAI(__this, u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34, method);
        consoleBLUE();
        std::cout << "[Info] Relayed on to GhostAI" << std::endl;
        consoleRESET();

        app::String* str = u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34.u0D26u0D1Cu0D35u0D30u0D32u0D24u0D3Bu0D38u0D1C;

        if (str == nullptr) {
            consoleRED();
            std::cout << "[!] Null referance instance protected" << std::endl;
            consoleRESET();
            return;
        }

        const wchar_t* chars = reinterpret_cast<const wchar_t*>(&str->fields._firstChar);
        std::wcout << chars << std::endl;
        thing = u0D20u0D2Cu0D34u0D25u0D2Cu0D24u0D29u0D26u0D34;
    }
}



void initHook_ChangeStateAI() {

    void* target = GhostAI_ChangeState;

    if (MH_CreateHook(target,
        reinterpret_cast<LPVOID>(&Hooked_ChangeStateAI),
        reinterpret_cast<LPVOID*>(&orig_changestate)) == MH_OK) {
        MH_EnableHook(target);
        getOffset(target);
    }
    else {
        consoleRED();
        std::cout << "[Error] Unable to hook ChangeStateAI" << std::endl;
        consoleRESET();
    }
}

void initHook_Init_GhostAI() {
    void* target = GhostAI_Init;
    if (MH_CreateHook(target,
        reinterpret_cast<LPVOID>(&Hooked_Init_GhostAI),
        reinterpret_cast<LPVOID*>(&orig_init_ghostAI)) == MH_OK) {
        MH_EnableHook(target);
        getOffset(target);
    }
    else {
        consoleRED();
        std::cout << "[Error] Unable to hook Init_GhostAI" << std::endl;
        consoleRESET();
    }
}

void initHook_SpawnAllGhostTypeEvidences() {
    void* target = EvidenceController_SpawnAllGhostTypeEvidence;
    if (MH_CreateHook(target,
        reinterpret_cast<LPVOID>(&Hooked_EvidenceController_SpawnAllGhostTypeEvidences),
        reinterpret_cast<LPVOID*>(&orig_spawnallghosttypeevidences)) == MH_OK) {
        MH_EnableHook(target);
        getOffset(target);
    }
    else {
        consoleRED();
        std::cout << "[Error] Unable to hook SpawnALlGhostTypeEvidence" << std::endl;
        consoleRESET();
    }
}

void initHook_OnPlayerStartedKilling() {
    void* target = Player_1_StartKillingPlayerNetworked;
    if (MH_CreateHook(target,
        reinterpret_cast<LPVOID>(&Hooked_OnPlayerStartedKilling),
        reinterpret_cast<LPVOID*>(&orig_onplayerstartkilling)) == MH_OK) {
        MH_EnableHook(target);
        getOffset(target);
    }
    else {
        consoleRED();
        std::cout << "[Error] Unable to hook OnPlayerStartedKilling" << std::endl;
        consoleRESET();
    }
}

void Run()
{
    il2cpp_thread_attach(il2cpp_domain_get());


   il2cppi_new_console();
   EnableANSI();

   consoleGREEN();
   std::cout << "" << std::endl;
   consoleRESET();
   void* pPresentAddr = nullptr;
   GetPresentAddress(&pPresentAddr);

   if (MH_Initialize() != MH_OK) {
	   consoleRED();
       std::cout << "[Catastrophic Error] Failed to initalize MinHook" << std::endl;
       consoleRESET();
       return;
   }
   MH_CreateHook(pPresentAddr, &hkPresent, reinterpret_cast<void**>(&oPresent));
   MH_EnableHook(pPresentAddr);

   initHook_ChangeStateAI();
   initHook_Init_GhostAI();
   initHook_SpawnAllGhostTypeEvidences();
   initHook_OnPlayerStartedKilling();
   CreateThread(NULL, 0, KeyCheckThread, NULL, 0, NULL);
}