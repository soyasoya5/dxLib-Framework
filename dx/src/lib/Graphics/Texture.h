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
	static std::shared_ptr<Texture> Create( const __FILEIO Path &path, 
											const __GRAPHICS BasePainter *painter = __GRAPHICS BasePainter::getSingleton( ) );

	///<summary>
	/// Create the texture from stream.
	///</summary>
	static std::shared_ptr<Texture> Create( std::istream &stream, 
											const __GRAPHICS BasePainter *painter = __GRAPHICS BasePainter::getSingleton( ) );

	///<summary>
	/// Create the texture from buffer in memory.
	///</summary>
	static std::shared_ptr<Texture> Create( char* buffer, 
											const __DX uint &length, 
											const __GRAPHICS BasePainter *painter = __GRAPHICS BasePainter::getSingleton( ) );


public:
	~Texture( );

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
	void Paint( const __MATH Vector2 &position, const __MATH Vector2 &scaling );

	///<summary>
	/// Paint this texture to position with scaling. (1, 1) is no scaling.
	///</summary>
	void Paint( const __MATH Region &region );
private:
	Texture( );
	void *sprite_, *texture_;
	unsigned char desc_[32u];
};


end_GRAPHICS