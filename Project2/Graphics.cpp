#include "Graphics.h"
#include <cmath>

Graphics::Graphics()
{
	// Чистим инструменты перед использованием

	factory = NULL; 
	rendertarget = NULL;
	brush = NULL;
	prev = D2D1_RECT_F{0, 0, 0, 0};
}

Graphics::~Graphics()
{
	// Освобождаем память после сессии использования

	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	// Настройка однопоточного конвеера и проверка результата

	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (result != S_OK) return false;

	// Из windowHandle достаём информацию об окне и сохраняем её как rectangle

	RECT rect;
	GetClientRect(windowHandle, &rect);

	// Устанавливаем параметры цели рендера и указатель на неё при помощи конвеера. Проверка результата

	result = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
										  D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
										  &rendertarget);
	if (result != S_OK) return false;

	// Создаём чёрную кисть и проверяем результат

	result = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0,0,0,1), &brush);
	if (result != S_OK) return false;
	return true;

}




ID2D1SolidColorBrush* Graphics::SetBrush()
{
	brush->SetColor(D2D1::ColorF(0, 0, 1, 1));
	return brush;
}

void Graphics::ClearScreen(float r, float g, float b) 
{
	rendertarget->Clear(D2D1::ColorF(r, g, b)); // Заполняем цель единым цветом
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	
	brush->SetColor(D2D1::ColorF(r, g, b, a)); // Меняем цвет кисти
	ID2D1EllipseGeometry* ellipseGeom; // Создаём указатель на геометрию эллипса
	HRESULT hr = factory->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), &ellipseGeom); // Создаём эту геометрию
	rendertarget->FillGeometry(ellipseGeom, brush); // Рисуем круг по заданной геометрии
	ellipseGeom->Release();
}

void Graphics::DrawRect(float x, float y, float a, float b, float red, float green, float blue)
{
	// Аналогично кругу. a b длина и ширина прямоугольника

	brush->SetColor(D2D1::ColorF(red, green, blue, 1));
	ID2D1RectangleGeometry* rectGeom;
	HRESULT hr = factory->CreateRectangleGeometry(D2D1::Rect(x,y,x+a,y+b), &rectGeom);
	rendertarget->FillGeometry(rectGeom, brush);
	rectGeom->Release();
}

ID2D1RectangleGeometry* Graphics::GetRectGeometry(float x, float y, float a, float b)
{
	ID2D1RectangleGeometry* rect;
	HRESULT hr = factory->CreateRectangleGeometry(D2D1::Rect(x, y, x + a, y + b), &rect);
	return rect;
}

ID2D1EllipseGeometry* Graphics::GetEllipseGeometry(float x, float y, float a, float b)
{
	ID2D1EllipseGeometry* ellipse;
	HRESULT hr = factory->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(x,y), a, b), &ellipse);
	return ellipse;
}


ID2D1RectangleGeometry* Graphics::MoveGeometry(float x, float y, ID2D1RectangleGeometry* rect)
{
	rect->GetRect(&prev);
	HRESULT hr = factory->CreateRectangleGeometry(D2D1::Rect(x, y, x + prev.right-prev.left, y + prev.bottom-prev.top), &rect);
	return rect;
}
ID2D1EllipseGeometry* Graphics::MoveGeometry(float x, float y, ID2D1EllipseGeometry* ellipse)
{
	factory->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(x, y), 2.5, 2.5), &ellipse);
	return ellipse;
}


void Graphics::DrawGeom(ID2D1Geometry* rect)
{
	brush->SetColor(D2D1::ColorF(0, 0, 1, 1));
	rendertarget->FillGeometry(rect, brush);
}

ID2D1TransformedGeometry* Graphics::GetRay(float x, float y, POINT* point)
{
	double distance = sqrt(pow(x - point->x, 2) + pow(y - point->y, 2));
	double sinus = (y - point->y) / distance;
	double cosinus = (x - point->x) / distance;
	ID2D1RectangleGeometry* rectGeom;
	ID2D1TransformedGeometry* Tgeom;
	factory->CreateRectangleGeometry(D2D1::Rect(x + 0.0, y + 0.0, x + distance, y + 5.0), &rectGeom);
	float angle;
	if (sinus < 0 ) angle = -std::acosf(cosinus)*180/3.14 +180;
	else if (sinus >= 0) angle = std::acosf(cosinus)*180/3.14 +180;

	factory->CreateTransformedGeometry(rectGeom,D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(x,y)), &Tgeom);
	return Tgeom;
}

