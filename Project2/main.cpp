#include <Windows.h>
#include <d2d1.h>
#include "Graphics.h" 
#include "Level1.h"
#include "GameController.h"
#include <chrono>
#include "CallbackF.h"






Graphics* graphics; // ���������� ���������� ��������� �� ����������� "������"





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) // �������� ������
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
	// ���������� ������� ����, ��� ���������

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.lpszClassName = L"MainWindow";
	RegisterClassEx(&windowclass);

	// ������ �������������, �� �������� �������� ����

	RECT rect = {0, 0, 800, 600};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	// ������ ���� � ������ �����������

	HWND windowhandle = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW,
		L"MainWindow",
		L"Directx",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL,
		hInstance, 0);
	if (!windowhandle) return -1; // �������� �� �������� ��������


	// ������ ��� "������" � ����

	graphics = new Graphics();
	if (!graphics->Init(windowhandle)) // ������� �������� �������������� ������ "������". ���� �� ����������, ��� �������, ����� �������
	{
		delete graphics;
		return -1;
	}

	/*  ���������� ��� "������" � ������������� ������� ������� �������.
	����� ������� ����� ��������� ����� �� ������� �� ����� � ��� �� ������ ��� ��������� ����  */

	GameLevel::Init(graphics); 
	
	// ��������� ���� ����

	ShowWindow(windowhandle, nCmdShow); 

	// ���������� ������ �������� ���� ����

	GameController::Init();
	GameController::LoadInitialLevel(new Level1());

	// �������� ������ ��� ����� ���������, �����, ����� �������� ������, ������� ������� ������ ���������

	MSG message;
	message.message = WM_NULL;

	// ������� ���� � ������� ����� �������

	while(message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message); // ���������� ��������� � �������
		}
		// ���������� ��������� ���� � ��������� �������� ��������� ����
		GameController::Update(keyDirections, &Mposition);
		GameController::Update();
		graphics->BeginDraw();
		GameController::Render();
		graphics->EndDraw();
	}
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
	delete graphics; // ����������� ������
	return 0;
}