#include "Texture.h"
#include "../Math/Region.h"
#include <d3d9.h>
#include <d3dx9.h>

begin_GRAPHICS

Texture * Texture::Create(const __FILEIO Path & _Path, const __GRAPHICS BasePainter *_Painter )
{
	std::ifstream stream( _Path.operator const char *( ), std::ios_base::binary );
	if ( !stream.is_open( ) )
		return nullptr;
	return Create( stream, _Painter );
}

Texture * Texture::Create(std::istream & _Stream, const __GRAPHICS BasePainter *_Painter)
{
	_Stream.seekg( 0, std::ios_base::end );
	auto size = _Stream.tellg( );
	_Stream.seekg( 0, std::ios_base::beg );
	auto buffer = std::make_unique<char*>( new char[size] );
	_Stream.read( *buffer, size );
	return Create( *buffer, size, _Painter );
}

Texture * Texture::Create( char* _Buffer, const __DX uint &_Length, const __GRAPHICS BasePainter *_Painter)
{
	auto ptr = new Texture( );
	auto device = (IDirect3DDevice9*)_Painter->native( );
	auto result = D3DXCreateTextureFromFileInMemory( device, _Buffer, _Length, (LPDIRECT3DTEXTURE9*)&ptr->_texture );

	if ( FAILED(result) )
	{
		delete ptr;
		return nullptr;
	}

	result = D3DXCreateSprite( device, (LPD3DXSPRITE*)&ptr->_sprite );

	if ( FAILED( result ) )
	{
		((LPDIRECT3DTEXTURE9)ptr->_texture)->Release( );
		delete ptr;
		return nullptr;
	}

	((LPDIRECT3DTEXTURE9)ptr->_texture)->GetLevelDesc( 0, (D3DSURFACE_DESC*)ptr->_desc );

	return ptr;
}


__MATH Vector2 Texture::getSize() const
{
	return __MATH Vector2{ static_cast<float>( ((D3DSURFACE_DESC*)_desc)->Width ), static_cast<float>( ((D3DSURFACE_DESC*)_desc)->Height ) };
}

void * Texture::native_sprite()
{
	return _sprite;
}

void *Texture::native_texture()
{
	return _texture;
}

void Texture::Paint( const __MATH Vector2 & _Position, const __MATH Vector2 & _Scaling)
{
	auto sprite = (LPD3DXSPRITE)_sprite;
	auto texture = (LPDIRECT3DTEXTURE9)_texture;
	if ( !sprite || !texture )
		return;

	// Begin
	sprite->Begin( D3DXSPRITE_ALPHABLEND );

	// Store old matrix
	D3DXMATRIX oMatrix;
	sprite->GetTransform( &oMatrix );

	// Scale the matrix
	D3DXMATRIX Matrix;
	D3DXMatrixTransformation2D( &Matrix, nullptr, 0, (D3DXVECTOR2*)&_Scaling, nullptr, 0.0f, nullptr );
	sprite->SetTransform( &Matrix );

	// Fix the position
	D3DXVECTOR3 pos = { _Position.x * (1 / _Scaling.x), _Position.y * (1 / _Scaling.y), 0 };

	// Draw
	sprite->Draw( texture, nullptr, nullptr, &pos, 0xFFFFFFFF );

	// Reset back to old matrix
	sprite->SetTransform( &oMatrix );

	// End
	sprite->End( );
}

void Texture::Paint(const __MATH Region & _Region)
{
	Paint( _Region.position, _Region.size );
}

Texture::Texture()
{
}


end_GRAPHICS