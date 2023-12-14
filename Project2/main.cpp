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
	
	HWND windowhandle;
	MSG msg;
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"ahfbsidk";
	wc.lpszMenuName = L"ksjdvb";

	if (!RegisterClassEx(&wc))
		return 0;
	RECT rect{ 0,0,1920,1080 };
	windowhandle = CreateWindowEx(WS_EX_TOPMOST, L"ahfbsidk", L"ksjdvb", WS_VISIBLE | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, rect.right-rect.left, rect.bottom- rect.top, HWND_DESKTOP, NULL, hInstance, 0);

	if (!windowhandle)
		return 0;
	/*HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		L"MainWindow",
		L"Directx",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL,
		hInstance, 0);*/



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
	HDC hDC = ::GetWindowDC(NULL);
	::SetWindowPos(windowhandle, NULL, 0, 0, ::GetDeviceCaps(hDC, HORZRES), ::GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);
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
		graphics->BeginDraw();
		GameController::Render();
		graphics->DrawCircle(Mposition.x, Mposition.y, 5, 0, 0, 1, 1);
		graphics->EndDraw();
	}
	UnhookWindowsHookEx(keyboardHook);
	UnhookWindowsHookEx(mouseHook);
	delete graphics; // Освобождаем память
	return 0;
}