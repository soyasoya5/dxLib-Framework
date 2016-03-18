#pragma once
#include "lib.h"
#include "../string.h"
#include "BasePainter.h"

begin_GRAPHICS

struct FontContext
{
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
	~Font( );
	static Font* Create( const __LIB String &_FontName, 
						 const __GRAPHICS FontContext &_Context, 
						 __GRAPHICS BasePainter *_Painter = BasePainter::getSingleton( ) );

	void Release( );
	void* raw( );
	__GRAPHICS FontContext context( );
private:
	void* _data;
	__LIB String _name;
	__GRAPHICS FontContext _context;
	Font();
};

end_GRAPHICS