#pragma once
#include "../pdl_api.h"

#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

#define WINDOW_CLASS_NAME "CoolGameClassName"

HWND pdlWindowHandle = NULL;

/*
        API to be used externally from the game
*/
void PDLShowWindow()
{
    ShowWindow(pdlWindowHandle, SW_SHOW);
}

void PDLHideWindow()
{
    ShowWindow(pdlWindowHandle, SW_HIDE);
}

void PDLResizeWindow(unsigned int width, unsigned int height)
{
    MessageBox(pdlWindowHandle, "Resizing Not Supported", "Nope",
               MB_OK | MB_ICONERROR);
}

void PDLCloseWindow()
{
    DestroyWindow(pdlWindowHandle);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
        }
        break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;

        default:
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        break;
    }
}

bool DoWindowMessages()
{
    MSG msg;

    bool result = GetMessage(&msg, NULL, 0, 0);

    if (result)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return result;
}

int main(int argc, char *argv[])
{
    HINSTANCE hInstance = GetModuleHandleA(argv[0]);
    if (!hInstance)
    {
        return 1;
    }

    WNDCLASS wc      = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClass(&wc);

    pdlWindowHandle =
        CreateWindowEx(0, WINDOW_CLASS_NAME, "Game Window", WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (pdlWindowHandle == NULL)
    {
        return 1;
    }

    ShowWindow(pdlWindowHandle, SW_SHOW);

    return game_main(argc, argv);
}

#define main(argc, argv) game_main(argc, argv)