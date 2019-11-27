#pragma once

#include "../pdl_api.h"

#include <stdio.h>
#include <windows.h>
#define WINDOW_CLASS_NAME "CoolGameClassName"

static BITMAPINFO bitmapInfo   = {0};
static void *     bitmapMemory = NULL;
static int        bitmapWidth;
static int        bitmapHeight;
static uint8_t    keys[256];

static HWND pdlWindowHandle = NULL;

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
    RECT rect;

    if (GetClientRect(pdlWindowHandle, &rect))
    {
        int x = rect.left;
        int y = rect.right;

        rect.left   = 0;
        rect.top    = 0;
        rect.right  = width;
        rect.bottom = height;

        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        int winWidth  = rect.right - rect.left;
        int winHeight = rect.bottom - rect.top;

        SetWindowPos(pdlWindowHandle, HWND_TOP, x, y, winWidth, winHeight,
                     SWP_SHOWWINDOW);
    }
}

void PDLCloseWindow()
{
    DestroyWindow(pdlWindowHandle);
}

uint8_t PDLGetKey(uint8_t key)
{
    return keys[key];
}

void Win32ResizeDIBSection(int width, int height)
{
    if (bitmapMemory)
    {
        VirtualFree(bitmapMemory, NULL, MEM_RELEASE);
    }

    bitmapWidth  = width;
    bitmapHeight = height;

    bitmapInfo.bmiHeader.biSize          = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth         = bitmapWidth;
    bitmapInfo.bmiHeader.biHeight        = -bitmapHeight;
    bitmapInfo.bmiHeader.biPlanes        = 1;
    bitmapInfo.bmiHeader.biBitCount      = 32;
    bitmapInfo.bmiHeader.biCompression   = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage     = 0;
    bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
    bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
    bitmapInfo.bmiHeader.biClrUsed       = 0;
    bitmapInfo.bmiHeader.biClrImportant  = 0;

    bitmapMemory = VirtualAlloc(NULL, sizeof(uint32_t) * width * height,
                                MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

void Win32UpdateWindow(HDC hdc, RECT *windowRect, int x, int y, int width,
                       int height)
{
    int windowWidth  = windowRect->right - windowRect->left;
    int windowHeight = windowRect->bottom - windowRect->top;

    StretchDIBits(hdc, 0, 0, windowWidth, windowHeight, 0, 0, bitmapWidth,
                  bitmapHeight, bitmapMemory, &bitmapInfo, DIB_RGB_COLORS,
                  SRCCOPY);
}

void PDLBlit(uint32_t *bitmap)
{
    if (bitmapMemory)
    {
        memcpy(bitmapMemory, bitmap,
               sizeof(uint32_t) * bitmapWidth * bitmapHeight);
    }

    HDC  deviceContext = GetDC(pdlWindowHandle);
    RECT rect          = {0};
    GetClientRect(pdlWindowHandle, &rect);

    int width  = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    Win32UpdateWindow(deviceContext, &rect, 0, 0, width, height);

    ReleaseDC(pdlWindowHandle, deviceContext);
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

            // case WM_SIZE:
            // {
            //     RECT rect = {0};
            //     GetClientRect(hwnd, &rect);

            //     int width  = rect.right - rect.left;
            //     int height = rect.bottom - rect.top;

            //     Win32ResizeDIBSection(width, height);

            //     return 0;
            // }
            // break;

        case WM_KEYUP:
        {
            printf("Key UP: 0x%x\n", (uint32_t)wParam);

            if (wParam <= 255)
            {
                keys[wParam] = 0;
            }
        }
        break;

        case WM_KEYDOWN:
        {
            printf("Key Down: 0x%x\n", (uint32_t)wParam);

            if (wParam <= 255)
            {
                keys[wParam] = 1;
            }
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC         hdc = BeginPaint(hwnd, &ps);

            int x      = ps.rcPaint.left;
            int y      = ps.rcPaint.top;
            int width  = ps.rcPaint.right - ps.rcPaint.left;
            int height = ps.rcPaint.bottom - ps.rcPaint.top;

            Win32UpdateWindow(hdc, &ps.rcPaint, x, y, width, height);

            EndPaint(hwnd, &ps);

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

bool PDLDoWindowMessages()
{
    bool result = true;
    MSG  msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            result = false;
        }

        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return result;
}

bool PDLInit(const char *title, uint32_t title_len, uint32_t x, uint32_t y,
             uint32_t width, uint32_t height)
{
    char *terminated_title = malloc(title_len + 1);
    if (memcpy(terminated_title, title, title_len) == NULL)
    {
        return false;
    }
    terminated_title[title_len] = '\0';

    HINSTANCE hInstance = GetModuleHandleA(NULL);
    if (!hInstance)
    {
        return false;
    }

    WNDCLASS wc      = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClass(&wc);

    RECT rect = {
        x,
        y,
        x + width,
        y + height,
    };

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    pdlWindowHandle = CreateWindowEx(
        0, WINDOW_CLASS_NAME, terminated_title, WS_OVERLAPPEDWINDOW, rect.left,
        rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL,
        hInstance, NULL);

    free(terminated_title);
    terminated_title = NULL;

    if (pdlWindowHandle == NULL)
    {
        return false;
    }

    ShowWindow(pdlWindowHandle, SW_SHOW);
    Win32ResizeDIBSection(width, height);

    return true;
}