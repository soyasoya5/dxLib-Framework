#include "Font.h"
#include "../Application.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

begin_GRAPHICS


Font::Font()
	: data_( nullptr ), name_( )
{

}

Font::~Font( )
{
	Release( );
}

void * Font::raw()
{
	return data_;
}

__GRAPHICS FontContext Font::context()
{
	return context_;
}

__MATH Vector2 Font::calculateMetrixOf(const __LIB String & text)
{
	if ( text.contains( " " ) )
	{
		__MATH Vector2 size{ 0, 0 };
		auto strs = text.split( ' ' );
		for ( auto &x : strs )
		{
			auto sz = strSize( x );
			size.x += sz.x;
			if (sz.y > size.y)
				size.y = sz.y;
		}
		
		size.x += (this->SPACE_CHARACTER_WIDTH) * text.count( ' ' );

		return size;
	}
	return strSize( text );
}

__MATH Vector2 Font::strSize(const __LIB String & _Text)
{
	auto font = (ID3DXFont*)this->data_;
	if ( !font )
		return { 0, 0 };
	RECT rect_textSize;
	font->DrawTextA( NULL, _Text.c_str( ), -1, &rect_textSize, DT_CALCRECT, 0xFFFFFFFF );
	return { float(rect_textSize.right - rect_textSize.left), float(rect_textSize.bottom - rect_textSize.top) };
}

std::shared_ptr<Font> Font::Create( const __LIB String &fontName, const __GRAPHICS FontContext &context, BasePainter *painter )
{
	auto font = std::shared_ptr<Font>( new Font( ) );

	auto device = (IDirect3DDevice9*)painter->native( );
	auto result = D3DXCreateFontA( device, 
								  context.Height, 
								  context.Width, 
								  context.Weight, 
								  context.MipLevels, 
								  context.Italic, 
								  context.CharSet, 
								  context.OutputPrecision, 
								  context.Quality, 
								  context.PitchAndFamily, 
								  fontName.c_str( ), 
								  (ID3DXFont**)&font->data_ );
	font->context_ = context;
	font->name_ = std::move( fontName );
	Application::setLastError( result );
	return font;
}

void Font::Release( )
{
	if ( data_ )
		((ID3DXFont*)data_)->Release( );
	data_ = nullptr;
}


end_GRAPHICS
