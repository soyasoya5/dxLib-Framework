#include "Font.h"
#include "../Renderer/Renderer.h"

Graphics::FontMetrics::Font::Font(Utils::String szSurfaceFontName, Utils::String szWinFontName, uint iSize, uint iWeight, void * device, uint iStyle, uint iOpt1, uint iOpt2, uint iOpt3, uint iOpt4)
{
	_name = szSurfaceFontName;
	_fontName = szWinFontName;
	this->iSize = iSize;
	this->iWeight = iWeight;
	this->iOpt1 = iOpt1;
	this->iOpt2 = iOpt2;
	this->iOpt3 = iOpt3;
	this->iOpt4 = iOpt4;
	_font = nullptr;
	_render = (Renderer::D9Renderer*)device;

	AddFontResourceEx(szWinFontName.c_str(), FR_PRIVATE, 0);

	if (FAILED(D3DXCreateFontA((LPDIRECT3DDEVICE9)_render->getDevice( ),
		this->iSize,
		(UINT)this->iOpt1,
		(UINT)this->iWeight,
		this->iOpt2,
		this->iOpt3,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		_fontName.c_str(),
		(LPD3DXFONT *)&_font)))
		return;
}

void Graphics::FontMetrics::Font::Release()
{
	
	if (_font)
		_font->Release();
}

TEXTMETRICA * Graphics::FontMetrics::Font::Metrics()
{
	_font->GetTextMetricsA( &this->metrics );
	return &this->metrics;
}

Graphics::Renderer::D9Renderer * Graphics::FontMetrics::Font::render()
{
	return _render;
}


