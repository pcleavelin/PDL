#pragma once

#include "../pdl_api.h"

#include <stdio.h>
#include <windows.h>
#define WINDOW_CLASS_NAME "CoolGameClassName"

static HDC        bitmapDeviceContext = NULL;
static BITMAPINFO bitmapInfo          = {0};
static HBITMAP    bitmapHandle        = {0};
static void *     bitmapMemory        = NULL;

static HWND pdlWindowHandle = NULL;

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
    RECT rect;
    if (GetWindowRect(pdlWindowHandle, &rect))
    {
        SetWindowPos(pdlWindowHandle, HWND_TOP, rect.left, rect.top, width,
                     height, SWP_SHOWWINDOW);
    }
}

void PDLCloseWindow()
{
    DestroyWindow(pdlWindowHandle);
}

void Win32ResizeDIBSection(int width, int height)
{
    if (bitmapHandle)
    {
        DeleteObject(bitmapHandle);
    }

    if (!bitmapDeviceContext)
    {
        bitmapDeviceContext = CreateCompatibleDC(0);
    }

    bitmapInfo.bmiHeader.biSize          = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth         = width;
    bitmapInfo.bmiHeader.biHeight        = height;
    bitmapInfo.bmiHeader.biPlanes        = 1;
    bitmapInfo.bmiHeader.biBitCount      = 32;
    bitmapInfo.bmiHeader.biCompression   = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage     = 0;
    bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
    bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
    bitmapInfo.bmiHeader.biClrUsed       = 0;
    bitmapInfo.bmiHeader.biClrImportant  = 0;

    bitmapHandle = CreateDIBSection(bitmapDeviceContext, &bitmapInfo,
                                    DIB_RGB_COLORS, &bitmapMemory, 0, 0);
}

void Win32UpdateWindow(HDC hdc, int x, int y, int width, int height)
{
    StretchDIBits(hdc, x, y, width, height, x, y, width, height, bitmapMemory,
                  &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
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

        case WM_SIZE:
        {
            // LRESULT result = DefWindowProc(hwnd, uMsg, wParam, lParam);

            RECT rect = {0};
            GetClientRect(hwnd, &rect);

            int width  = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            Win32ResizeDIBSection(width, height);

            return 0;
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

            Win32UpdateWindow(hdc, x, y, width, height);

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
    MSG msg;

    bool result = GetMessage(&msg, NULL, 0, 0);

    if (result)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return result;
}

bool PDLInit(const char *title, size_t title_len)
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

    pdlWindowHandle = CreateWindowEx(
        0, WINDOW_CLASS_NAME, terminated_title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
        hInstance, NULL);

    free(terminated_title);
    terminated_title = NULL;

    if (pdlWindowHandle == NULL)
    {
        return false;
    }

    ShowWindow(pdlWindowHandle, SW_SHOW);

    return true;
}