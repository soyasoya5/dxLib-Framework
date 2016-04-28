#include "Texture.h"
#include "../Math/Region.h"
#include <d3d9.h>
#include <d3dx9.h>

begin_GRAPHICS

std::shared_ptr<Texture> Texture::Create(const ::dx::lib::FileIO::Path & path, const ::dx::lib::Graphics::BasePainter *painter )
{
	std::ifstream stream( path.operator const char *( ), std::ios_base::binary );
	if ( !stream.is_open( ) )
		return nullptr;
	return Create( stream, painter );
}

std::shared_ptr<Texture> Texture::Create(std::istream & stream, const ::dx::lib::Graphics::BasePainter *painter)
{
	auto state = stream.rdstate( );
	auto pos = stream.tellg( );

	try {
		stream.seekg( 0, std::ios_base::end );
		auto size = stream.tellg( );
		stream.seekg( 0, std::ios_base::beg );
		auto buffer = std::make_unique<char*>( new char[size] );
		stream.read( *buffer, size );
		return Create( *buffer, size, painter );
	}
	catch( ... )
	{
		stream.setstate( state );
		stream.seekg( pos );
	}
	return nullptr;
}

std::shared_ptr<Texture> Texture::Create( char* _Buffer, const ::dx::uint &_Length, const ::dx::lib::Graphics::BasePainter *_Painter)
{
	auto ptr = std::shared_ptr<Texture>( new Texture( ) );
	auto device = (IDirect3DDevice9*)_Painter->native( );
	auto result = D3DXCreateTextureFromFileInMemory( device, _Buffer, _Length, (LPDIRECT3DTEXTURE9*)&ptr->texture_ );

	if ( FAILED( result ) )
		return nullptr;

	result = D3DXCreateSprite( device, (LPD3DXSPRITE*)&ptr->sprite_ );

	if ( FAILED( result ) )
	{
		((LPDIRECT3DTEXTURE9)ptr->texture_)->Release( );
		return nullptr;
	}

	((LPDIRECT3DTEXTURE9)ptr->texture_)->GetLevelDesc( 0, (D3DSURFACE_DESC*)ptr->desc_ );

	return ptr;
}

Texture::~Texture()
{
	if ( sprite_ )
		((LPD3DXSPRITE)sprite_)->Release( );
	
	if ( texture_ )
		((LPDIRECT3DTEXTURE9)texture_)->Release( );
}


::dx::lib::Math::Vector2 Texture::getSize() const
{
	return ::dx::lib::Math::Vector2{ static_cast<float>( ((D3DSURFACE_DESC*)desc_)->Width ), static_cast<float>( ((D3DSURFACE_DESC*)desc_)->Height ) };
}

void * Texture::native_sprite()
{
	return sprite_;
}

void *Texture::native_texture()
{
	return texture_;
}

void Texture::Paint( const ::dx::lib::Math::Vector2 & position, const ::dx::lib::Math::Vector2 & scaling)
{
	auto sprite = (LPD3DXSPRITE)sprite_;
	auto texture = (LPDIRECT3DTEXTURE9)texture_;
	if ( !sprite || !texture )
		return;

	// Begin
	sprite->Begin( D3DXSPRITE_ALPHABLEND );

	// Store old matrix
	D3DXMATRIX oMatrix;
	sprite->GetTransform( &oMatrix );

	// Scale the matrix
	D3DXMATRIX Matrix;
	D3DXMatrixTransformation2D( &Matrix, nullptr, 0, (D3DXVECTOR2*)&scaling, nullptr, 0.0f, nullptr );
	sprite->SetTransform( &Matrix );

	// Fix the position
	D3DXVECTOR3 pos = { position.x * (1 / scaling.x), position.y * (1 / scaling.y), 0 };

	// Draw
	sprite->Draw( texture, nullptr, nullptr, &pos, 0xFFFFFFFF );

	// Reset back to old matrix
	sprite->SetTransform( &oMatrix );

	// End
	sprite->End( );
}

void Texture::Paint(const ::dx::lib::Math::Region & region)
{
	Paint( region.position, region.size );
}

Texture::Texture()
	: sprite_( nullptr ), texture_( nullptr )
{
}


end_GRAPHICS