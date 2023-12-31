#pragma once
#include <Windows.h>
#include <d2d1.h>

/*  ���� ���������, ���������� ���������� ������ ������� ������ � ��� �������.  */


class Graphics
{
	D2D_RECT_F prev;
	D2D1_ELLIPSE prevel;
	ID2D1Factory* factory; // ��������� �� ������� ������� ������� �������
	ID2D1HwndRenderTarget* rendertarget; // ��������� �� ������� ���� ������� ���������
	ID2D1SolidColorBrush* brush; // ��������� �� ����� ���������
public:
	Graphics(); // ����������� ������
	~Graphics(); // ���������� ������
	bool Init(HWND windowHandle); // ��������� ���������� ������
	ID2D1RenderTarget* GetRenderTarget() // ����� ����������� ����������������� � ����� �������
	{
		return rendertarget;
	}
	ID2D1EllipseGeometry* GetEllipseGeometry(float x, float y, float a, float b);
	ID2D1SolidColorBrush* SetBrush();
	void BeginDraw() // ���������� ������ ���������
	{ 
		rendertarget->BeginDraw();
	}
	void EndDraw() // ���������� ����� ���������
	{
		rendertarget->EndDraw();
	}
	ID2D1RectangleGeometry* GetRectGeometry(float x, float y, float a, float b);
	ID2D1RectangleGeometry* MoveGeometry(float x, float y, ID2D1RectangleGeometry* rect);
	ID2D1EllipseGeometry* MoveGeometry(float x, float y, ID2D1EllipseGeometry* ellipse);
	ID2D1TransformedGeometry* GetRay(float x, float y, POINT* point);
	void ClearScreen(float r, float g, float b); // ���������� ������ ����� ������
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a); // ��������� �����
	void DrawRect(float x, float y, float a, float b, float red, float green, float blue); // ��������� ��������������
	void DrawGeom(ID2D1Geometry* rect);

};