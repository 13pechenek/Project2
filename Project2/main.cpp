#include <Windows.h>
#include <d2d1.h>
#include <string>


LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0);  return 0; }
	DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow) 
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.lpszClassName = L"MainWindow";
	
	RegisterClassEx(&windowclass);

	HWND windowhandle = CreateWindow( L"MainWindow", L"Directx", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, 0);
	if (!windowhandle) return -1;
	ShowWindow(windowhandle, nCmdShow);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}
	return 0;
}