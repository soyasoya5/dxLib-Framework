#pragma once
#include "lib.h"
#include "../FileIO/path.h"
#include "BasePainter.h"
#include "../Math/Vector2.h"

begin_GRAPHICS


class Texture
{
public:
	static Texture *Create( const __FILEIO Path &_Path, const __GRAPHICS BasePainter *_Painter = __GRAPHICS BasePainter::getSingleton( ) );
	static Texture *Create( std::ifstream &_Stream, const __GRAPHICS BasePainter *_Painter = __GRAPHICS BasePainter::getSingleton( ) );
	static Texture *Create( char* _Buffer, const __DX uint &_Length, const __GRAPHICS BasePainter *_Painter = __GRAPHICS BasePainter::getSingleton( ) );


	void* native_sprite( );
	void* native_texture( );
	void Paint( const __MATH Vector2 &_Position, const __MATH Vector2 &_Scaling );
	void Paint( const __MATH Region &_Region );
private:
	Texture( );
	void *_sprite, *_texture;
};


end_GRAPHICS