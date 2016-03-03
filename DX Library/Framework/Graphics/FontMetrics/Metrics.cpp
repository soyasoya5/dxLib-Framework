#include "Metrics.h"
#include "font.h"
#include "../Renderer/Renderer.h"

Graphics::FontMetrics::Metrics::Metrics(Font * font)
{
	_font = font;
}

float Graphics::FontMetrics::Metrics::MaxHeight()
{
	return _font->Metrics( )->tmHeight;
}

float Graphics::FontMetrics::Metrics::MaxWidth()
{
	return _font->Metrics( )->tmMaxCharWidth;
}

float Graphics::FontMetrics::Metrics::AvgWidth()
{
	return _font->Metrics( )->tmAveCharWidth;
}

Vector2 Graphics::FontMetrics::Metrics::SizeOfString(const Utils::String &string)
{
	auto render = _font->render( );
	if ( string.contains( " " ) )
	{
		Vector2 size{ 0,0 };
		auto strings = string.split( " " );
		if ( strings.empty( ) )
			return { 0, 0 };

		for ( auto&x : strings )
			size += render->StrSize( _font, x );
		
		size.x += 7 * strings.size( );
		size.y = _font->Metrics( )->tmHeight;
		return size;
	}
	return render->StrSize( _font, string );
}
