#pragma once
#include <Windows.h>
#include "GameStructs.h"

DWORD currentKey;
HHOOK keyboardHook;
HHOOK mouseHook;
KeyDirections keyDirections;
POINT Mposition;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // �������� ��������� ��������� ��� ����
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0);  return 0; } // ����� �� �������
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
	Mposition.x = 0;
	Mposition.y = 0;
	MOUSEHOOKSTRUCT* mouseStruct = (MOUSEHOOKSTRUCT*) lParam;
	if (nCode >= 0 && (wParam == WM_MBUTTONDOWN))
	{
		Mposition = mouseStruct->pt;
		click = 1;
	}
	if (nCode >= 0 && (wParam == WM_MBUTTONUP)) 
	{
		click = 0;
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}