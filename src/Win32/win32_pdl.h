#pragma once
#include <stdio.h>
#include <windows.h>

#define WINDOW_CLASS_NAME "CoolGameClassName"

#define main(argc, argv) game_main(argc, argv)

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow)
{
    WNDCLASS wc;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClass(&wc);

    HWND windowHandle =
        CreateWindowEx(0, WINDOW_CLASS_NAME, "Game Window", WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (windowHandle == NULL)
    {
        return 1;
    }

    ShowWindow(windowHandle, nCmdShow);

    return 0;
}