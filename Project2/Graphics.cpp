#include "Graphics.h"

Graphics::Graphics()
{
	// ������ ����������� ����� ��������������

	factory = NULL; 
	rendertarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	// ����������� ������ ����� ������ �������������

	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	// ��������� ������������� �������� � �������� ����������

	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (result != S_OK) return false;

	// �� windowHandle ������ ���������� �� ���� � ��������� � ��� rectangle

	RECT rect;
	GetClientRect(windowHandle, &rect);

	// ������������� ��������� ���� ������� � ��������� �� �� ��� ������ ��������. �������� ����������

	result = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
										  D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
										  &rendertarget);
	if (result != S_OK) return false;

	// ������ ������ ����� � ��������� ���������

	result = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0,0,0,1), &brush);
	if (result != S_OK) return false;
	return true;

}

void Graphics::ClearScreen(float r, float g, float b) 
{
	rendertarget->Clear(D2D1::ColorF(r, g, b)); // ��������� ���� ������ ������
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	
	brush->SetColor(D2D1::ColorF(r, g, b, a)); // ������ ���� �����
	ID2D1EllipseGeometry* ellipseGeom; // ������ ��������� �� ��������� �������
	HRESULT hr = factory->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), &ellipseGeom); // ������ ��� ���������
	rendertarget->FillGeometry(ellipseGeom, brush); // ������ ���� �� �������� ���������
	ellipseGeom->Release();
}

void Graphics::DrawRect(float x, float y, float a, float b, float red, float green, float blue)
{
	// ���������� �����. a b ����� � ������ ��������������

	brush->SetColor(D2D1::ColorF(red, green, blue, 1));
	ID2D1RectangleGeometry* rectGeom;
	HRESULT hr = factory->CreateRectangleGeometry(D2D1::Rect(x,y,x+a,y+b), &rectGeom);
	rendertarget->FillGeometry(rectGeom, brush);
	rectGeom->Release();
}

ID2D1RectangleGeometry* Graphics::GetRectGeometry(float x, float y, float a, float b)
{
	ID2D1RectangleGeometry* rect;
	prev.bottom = y + b;
	prev.top = y;
	prev.left = x;
	prev.right = x + a;
	HRESULT hr = factory->CreateRectangleGeometry(D2D1::Rect(x, y, x + a, y + b), &rect);
	return rect;
}

ID2D1RectangleGeometry* Graphics::MoveGeometry(float x, float y, ID2D1RectangleGeometry* rect)
{
	HRESULT hr = factory->CreateRectangleGeometry(D2D1::Rect(x, y, x + prev.right-prev.left, y + prev.bottom-prev.top), &rect);
	return rect;
}

void Graphics::DrawGeom(ID2D1Geometry* rect)
{
	brush->SetColor(D2D1::ColorF(0, 0, 1, 1));
	rendertarget->FillGeometry(rect, brush);
}