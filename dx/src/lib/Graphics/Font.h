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
	__DX uint Width /* Can be ignored */, 
			  Weight, 
			  MipLevels /* Can be Ignored */;
	bool Italic;

	// Below can be ignored
	DWORD CharSet, OutputPrecision, Quality, PitchAndFamily;

};

class Font
{
public:
	static const __DX uint SPACE_CHARACTER_WIDTH = 10;

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
	__GRAPHICS FontContext context( );

	///<summary>
	///	Calculate the size of '_Text' with this font.
	///</summary>
	__MATH Vector2 calculateMetrixOf( const String &text );
private:
	__MATH Vector2 strSize( const String &text );
	void* data_;
	__LIB String name_;
	__GRAPHICS FontContext context_;
	Font();
};

end_GRAPHICS