#pragma once
#include <Windows.h>
#include "GameStructs.h"

DWORD currentKey;
HHOOK keyboardHook;
HHOOK mouseHook;
KeyDirections keyDirections;
POINT Mposition;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // Интерфес обработки сообщений для окна
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0);  return 0; } // Выход на крестик
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && (wParam == WM_KEYDOWN)) {
		KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
		currentKey = pKeyStruct->vkCode;
		if (currentKey == 'W')
		{
			keyDirections.up = true;
		}
		if (currentKey == 'S')
		{
			keyDirections.down = true;
		}
		if (currentKey == 'A')
		{
			keyDirections.left = true;
		}
		if (currentKey == 'D')
		{
			keyDirections.right = true;
		}
	}
	else if (nCode >= 0 && (wParam == WM_KEYUP)) {
		KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
		currentKey = pKeyStruct->vkCode;
		if (currentKey == 'W')
		{
			keyDirections.up = false;
		}
		if (currentKey == 'S')
		{
			keyDirections.down = false;
		}
		if (currentKey == 'A')
		{
			keyDirections.left = false;
		}
		if (currentKey == 'D')
		{
			keyDirections.right = false;
		}
	}
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

bool click = 0;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* mouseStruct = (MOUSEHOOKSTRUCT*) lParam;

	if (wParam == WM_LBUTTONDOWN)
	{
		Mposition.x = mouseStruct->pt.x;
		Mposition.y = mouseStruct->pt.y;
		click = 1;
	}
	if (wParam == WM_LBUTTONUP) 
	{
		Mposition.x = 0;
		Mposition.y = 0;
		click = 0;
	}
	if (wParam == WM_MOUSEMOVE && click)
	{
		Mposition.x = mouseStruct->pt.x;
		Mposition.y = mouseStruct->pt.y;
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}