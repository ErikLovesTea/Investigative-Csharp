#pragma once
#include <d3d11.h>
#include <dxgi.h>

typedef HRESULT(WINAPI* Present_t)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

extern Present_t oPresent;
extern HRESULT WINAPI hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern bool godMode;

HRESULT GetPresentAddress(void** pPresent);