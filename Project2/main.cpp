#include <Windows.h>
#include <d2d1.h>
#include "Graphics.h" 
#include "Level1.h"
#include "GameController.h"
#include <chrono>


Graphics* graphics; //���������� ���������� ��������� �� ����������� "������"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //����,���� ���������
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0);  return 0; } //����� �� �������
	if (uMsg == WM_PAINT)
	{
		graphics->BeginDraw();

		graphics->ClearScreen((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		for (int i = 0; i < 100; i++) graphics->DrawCircle(rand() % 800, rand() % 600, rand() % 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);

		graphics->EndDraw();
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) // �������� ������
{
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

	// ������ � ������ �����������

	HWND windowhandle = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW,
		L"MainWindow",
		L"Directx",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL,
		hInstance, 0);
	if (!windowhandle) return -1; // �������� �� �������� ��������


	// ������ ������ ��� "������" � ����

	graphics = new Graphics();
	if (!graphics->Init(windowhandle))// ������� �������� �������������� ������ "������". ���� �� ����������, ��� �������, ����� �������
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);

	ShowWindow(windowhandle, nCmdShow);

	GameController::Init();
	GameController::LoadInitialLevel(new Level1());
	// �������� ������ ��� ����� ���������, �����, ����� �������� ������, ������� ������� ������ ���������

	MSG message;
	message.message = WM_NULL;

	//������� ���� � ������� ����� �������
	bool paused = false;

	while(message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message); // ���������� ��������� � �������
		}
		if (!GetKeyState(VK_TAB)) GameController::Update();
		else GameController::TimerRefresh();
		graphics->BeginDraw();
		GameController::Render();
		graphics->EndDraw();
	}
	delete graphics;
	return 0;
}