#pragma once
#include "lib.h"
#include "../string.h"
#include "BasePainter.h"
#include "../Math/Vector2.h"

begin_GRAPHICS

struct FontContext
{
	///<summary>
	///	Empty constructor
	///</summary>
	FontContext( )
		: Height( 0 ), Width( 0 ), Weight( 0 ), MipLevels( 0 ), Italic( false ),
		  CharSet( DEFAULT_CHARSET ), OutputPrecision( OUT_DEFAULT_PRECIS), Quality( DEFAULT_QUALITY ),
		  PitchAndFamily( DEFAULT_PITCH | FF_DONTCARE )
	{}

	int Height;
	::dx::uint Width /* Can be ignored */, 
			  Weight, 
			  MipLevels /* Can be Ignored */;
	bool Italic;

	// Below can be ignored
	DWORD CharSet, OutputPrecision, Quality, PitchAndFamily;

};

class Font
{
public:
	static const ::dx::uint SPACE_CHARACTER_WIDTH = 10;

	~Font( );

	///<summary>
	///	Create font.
	///</summary>
	static std::shared_ptr<Font> Create( const String &fontName, 
									     const FontContext &context, 
									     BasePainter *painter = BasePainter::getSingleton( ) );

	///<summary>
	///	Release font.
	///</summary>
	void Release( );

	///<summary>
	///	Raw font data.
	///</summary>
	void* raw( );

	///<summary>
	///	The font context.
	///</summary>
	::dx::lib::Graphics::FontContext context( );

	///<summary>
	///	Calculate the size of '_Text' with this font.
	///</summary>
	::dx::lib::Math::Vector2 calculateMetrixOf( const String &text );
private:
	::dx::lib::Math::Vector2 strSize( const String &text );
	void* data_;
	::dx::lib::String name_;
	::dx::lib::Graphics::FontContext context_;
	Font();
};

end_GRAPHICS