#include "Sprites.h"

Sprites::Sprites(const wchar_t* filename, Graphics* gfx)
{

	this->gfx = gfx;
	
	bmp = NULL;
	HRESULT hr;
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);
	hr = wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
	hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &bmp);
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicFrame) wicFrame->Release();
	if (wicConverter) wicConverter->Release();
	geometry = gfx->GetRectGeometry(0, 0, bmp->GetSize().width, bmp->GetSize().height);
}

Sprites::~Sprites() {
	if (bmp) bmp->Release();
}

void Sprites::Draw() 
{
	gfx->GetRenderTarget()->DrawBitmap(bmp, D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0f, 0.0f, bmp->GetPixelSize().width, bmp->GetSize().height));
}

void Sprites::DrawAtPlace(float x, float y) {
	geometry = gfx->MoveGeometry(x, y, geometry);
	gfx->GetRenderTarget()->DrawBitmap(bmp, D2D1::RectF(x, y, bmp->GetSize().width+x, bmp->GetSize().height+y), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0f, 0.0f, bmp->GetPixelSize().width, bmp->GetSize().height));
}

