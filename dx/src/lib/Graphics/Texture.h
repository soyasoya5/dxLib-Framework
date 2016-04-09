#pragma once
#include "lib.h"
#include "../FileIO/path.h"
#include "BasePainter.h"
#include "../Math/Vector2.h"

begin_GRAPHICS


class Texture
{
public:
	///<summary>
	/// Create the texture from path.
	///</summary>
	static Texture *Create( const __FILEIO Path &_Path, const __GRAPHICS BasePainter *_Painter = __GRAPHICS BasePainter::getSingleton( ) );

	///<summary>
	/// Create the texture from stream.
	///</summary>
	static Texture *Create( std::istream &_Stream, const __GRAPHICS BasePainter *_Painter = __GRAPHICS BasePainter::getSingleton( ) );

	///<summary>
	/// Create the texture from buffer in memory.
	///</summary>
	static Texture *Create( char* _Buffer, const __DX uint &_Length, const __GRAPHICS BasePainter *_Painter = __GRAPHICS BasePainter::getSingleton( ) );


	///<summary>
	/// Get the size of this texture (NON SCALED)
	///</summary>
	__MATH Vector2 getSize( ) const;

	///<summary>
	///	Get the native sprite of this texture.
	///</summary>
	void* native_sprite( );

	///<summary>
	/// Gets the native texture of this texture.
	///</summary>
	void* native_texture( );

	///<summary>
	/// Paint this texture to position with scaling. (1, 1) is no scaling.
	///</summary>
	void Paint( const __MATH Vector2 &_Position, const __MATH Vector2 &_Scaling );

	///<summary>
	/// Paint this texture to position with scaling. (1, 1) is no scaling.
	///</summary>
	void Paint( const __MATH Region &_Region );
private:
	Texture( );
	void *_sprite, *_texture;
	unsigned char _desc[32u];
};


end_GRAPHICS