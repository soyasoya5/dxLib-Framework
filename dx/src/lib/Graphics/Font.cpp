#include "Font.h"
#include "../Application.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

begin_GRAPHICS


Font::Font()
	: _data( nullptr ), _name( )
{

}

Font::~Font( )
{
	Release( );
}

void * Font::raw()
{
	return _data;
}

__GRAPHICS FontContext Font::context()
{
	return _context;
}

__MATH Vector2 Font::calculateMetrixOf(const __LIB String & _Text)
{
	auto font = (ID3DXFont*)this->_data;
	if ( !font )
		return { 0, 0 };
	RECT rect_textSize;
	font->DrawTextA( NULL, _Text.c_str( ), -1, &rect_textSize, DT_CALCRECT, 0xFFFFFFFF );
	return { float(rect_textSize.right - rect_textSize.left), float(rect_textSize.bottom - rect_textSize.top) };
}

Font* Font::Create( const __LIB String &_FontName, const __GRAPHICS FontContext &_Context, BasePainter *_Painter )
{
	auto font = new Font( );

	auto device = (IDirect3DDevice9*)_Painter->native( );
	auto result = D3DXCreateFontA( device, 
								  _Context.Height, 
								  _Context.Width, 
								  _Context.Weight, 
								  _Context.MipLevels, 
								  _Context.Italic, 
								  _Context.CharSet, 
								  _Context.OutputPrecision, 
								  _Context.Quality, 
								  _Context.PitchAndFamily, 
								  _FontName.c_str( ), 
								  (ID3DXFont**)&font->_data );
	font->_context = _Context;
	font->_name = _FontName;
	Application::setLastError( result );
	return font;
}

void Font::Release( )
{
	if ( _data )
		((ID3DXFont*)_data)->Release( );
}


end_GRAPHICS
