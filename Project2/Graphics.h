#pragma once
#include <Windows.h>
#include <d2d1.h>

/*  Файл заголовка, содержащий объявление класса игровой гафики и его методов.  */


class Graphics
{
	D2D_RECT_F prev;
	ID2D1Factory* factory; // Указатель на будущий конвеер игровой графики
	ID2D1HwndRenderTarget* rendertarget; // Указатель на будущую цель рендера конвеером
	ID2D1SolidColorBrush* brush; // Указатель на кисть отрисовки
public:
	Graphics(); // Конструктор класса
	~Graphics(); // Деструктор класса
	bool Init(HWND windowHandle); // Настройка параметров класса
	ID2D1RenderTarget* GetRenderTarget() // Метод позволяющий взаимодействовать с целью рендера
	{
		return rendertarget;
	}
	void BeginDraw() // Объявление начала отрисовки
	{ 
		rendertarget->BeginDraw();
	}
	void EndDraw() // Объявление конца отрисовки
	{
		rendertarget->EndDraw();
	}
	ID2D1RectangleGeometry* GetRectGeometry(float x, float y, float a, float b);
	ID2D1RectangleGeometry* MoveGeometry(float x, float y, ID2D1RectangleGeometry* rect);
	void ClearScreen(float r, float g, float b); // Заполнение экрана одним цветом
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a); // Отрисовка круга
	void DrawRect(float x, float y, float a, float b, float red, float green, float blue); // Отрисовка прямоугольника
	void DrawGeom(ID2D1Geometry* rect);

};