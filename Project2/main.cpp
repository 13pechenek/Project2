#include <Windows.h>
#include <d2d1.h>
#include "Graphics.h" 
#include "Level1.h"
#include "GameController.h"
#include <chrono>
#include "CallbackF.h"






Graphics* graphics; // Глобальное объявление указателя на графический "движок"





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) // Основной скрипт
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
	// Объявление объекта окно, его параметры

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.lpszClassName = L"MainWindow";
	RegisterClassEx(&windowclass);

	// Строим прямоугольник, от которого строится окно

	RECT rect = {0, 0, 800, 600};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	// Создаём окно с нашими параметрами

	HWND windowhandle = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW,
		L"MainWindow",
		L"Directx",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL,
		hInstance, 0);
	if (!windowhandle) return -1; // Проверка на успешное создание


	// Создаём наш "движок" в куче

	graphics = new Graphics();
	if (!graphics->Init(windowhandle)) // Пробуем провести инициаллизацию нашего "движка". Если не получилось, его убиваем, затем выходим
	{
		delete graphics;
		return -1;
	}

	/*  Подгружаем наш "движок" в универсальную систему игровых уровней.
	Таким образом можно запускать любой из уровней на одном и том же движке без мусорного кода  */

	GameLevel::Init(graphics); 
	
	// Открываем наше окно

	ShowWindow(windowhandle, nCmdShow); 

	// Подготовка класса контроля хода игры

	GameController::Init();
	GameController::LoadInitialLevel(new Level1());

	// Выделяем память для ловли сообщений, затем, чтобы избежать ошибок, вручную вбиваем пустое сообщение

	MSG message;
	message.message = WM_NULL;

	// Создаем цикл с выходом через крестик

	while(message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message); // Отправляем сообщение в винпрок
		}
		// Обновление состояния игры и отрисовка текущего состояния игры
		GameController::Update(keyDirections, &Mposition);
		GameController::Update();
		graphics->BeginDraw();
		GameController::Render();
		graphics->EndDraw();
	}
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
	delete graphics; // Освобождаем память
	return 0;
}