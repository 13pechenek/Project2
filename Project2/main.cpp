#include <Windows.h>
#include <d2d1.h>
#include "Graphics.h" 
#include "Level1.h"
#include "GameController.h"


Graphics* graphics; //глобальное объ€вление указател€ на графический "движок"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //обраюотка сообщений
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0);  return 0; } //выход на крестик
	/*if (uMsg == WM_PAINT)
	{
		graphics->BeginDraw();

		graphics->ClearScreen((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		for (int i = 0; i < 100; i++) graphics->DrawCircle(rand() % 800, rand() % 600, rand() % 100, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);

		graphics->EndDraw();
	}*/
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) // основной скрипт
{
	// объ€вление объекта окно, его параметры

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.lpszClassName = L"MainWindow";
	RegisterClassEx(&windowclass);

	// строим пр€моугольник, от которого строитс€ окно

	RECT rect = {0, 0, 800, 600};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	// создаЄм с нашими параметрами

	HWND windowhandle = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW,
		L"MainWindow",
		L"Directx",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL,
		hInstance, 0);
	if (!windowhandle) return -1; // проверка на успешное создание


	// теперь создаЄм наш "движок" в куче

	graphics = new Graphics();
	if (!graphics->Init(windowhandle))// пробуем провести инициаллизацию нашего "движка". ≈сли не получилось, его убиваем, затем выходим
	{
		delete graphics;
		return -1;
	}

	ShowWindow(windowhandle, nCmdShow);

	GameController::LoadInitialLevel(new Level1());
	// выдел€ем пам€ть дл€ ловли сообщений, затем, чтобы избежать ошибок, вручную вбиваем пустое сообщение

	MSG message;
	message.message = WM_NULL;

	//создаем цикл с выходом через крестик

	while(message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
		{
			DispatchMessage(&message); // отправл€ем сообщение в винпрок
		}
		else //сообщений нет
		{
			GameController::Update();
			graphics->BeginDraw();
			GameController::Render(graphics);
			graphics->EndDraw();
		}
	}
	/*
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}*/

	delete graphics;
	return 0;
}