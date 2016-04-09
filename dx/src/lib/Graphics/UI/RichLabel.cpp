#include "RichLabel.h"
#include "../Font.h"
#include "../Text.h"
#include "../Pen.h"
#include "../Texture.h"

begin_UI

RichLabel::RichLabel()
	: Component( )
{
	OnModified( ) += __LIB EventHandler<void(Component*)>( "Constructor_Watcher", 
														   [this]( Component *component ) { this->_changed = true; } );
	_changed = true;
}

void RichLabel::Paint(__GRAPHICS Window * _Sender, __GRAPHICS BasePainter * _Painter)
{
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, _Painter );

	// Just incase :P
	FlexibleGuard guard{ _kpr };

	auto pos = determineRegion( );


	for ( auto it = _all_text.begin( ), begin = _all_text.begin( ), end = _all_text.end( ); it < end; ++it )
	{
		// First lets check if we changed
		if ( _changed ) // If so recalculate everything
		{
			// Check font
			if ( !it->container.font )
				it->container.font = (getFont( ) ? getFont( ) : _Painter->defaultFont( ));

			// Recalculate position
			if ( it == begin ) // First...
				it->position = pos.position;
			else
			{
				auto prev = (it - 1);
				
				// did the previus node end on a new line
				if ( prev->container.new_line )
					it->position = { pos.position.x, prev->position.y + prev->size.y }; // kk then get original x pos and the prev y + its size
				else 
					it->position = prev->position + __MATH Vector2{ prev->size.x + (it->container.is_texture ? 5 : 0), (it->container.is_texture ? 2.0f : 0.0f) }; // Ok then get the vector of prev pos + prev size(x only)
			}

			// Size
			it->size = (it->container.is_texture ? it->container.texture->getSize( ) : it->container.font->calculateMetrixOf( it->container.text ));
		}

		// Right, lets draw
		if ( it->container.is_texture )
			it->container.texture->Paint( it->position, { 1, 1 } );
		else 
		{
			Text text;
			text.setPosition( it->position );
			text.setFont( it->container.font );
			text.setText( it->container.text );

			// Paintaronie
			_Painter->Paint( text, Pen( it->container.color, 1 ) );
		}
	}
	

	_changed = false;
	OnPostPaint( ).Invoke( this, _Painter );
}

void RichLabel::appendText(const __LIB String & _Text, __GRAPHICS Font * _Font, const __DX uint & _Color)
{
	_mtext.append( _Text );
	
	if ( _Text.contains( "\n" ) )
	{
		auto vecs = _Text.split( '\n' );
		for ( auto text : vecs )
		{
			TextContainer container;
			container.text = text;
			container.font = _Font;
			container.color = _Color;
			container.new_line = true;
			_contrs.push_back( std::move( container ) );
		}
	}
	else
	{
		TextContainer container;
		container.text = _Text;
		container.font = _Font;
		container.color = _Color;
		container.new_line = false;
		container.is_texture = false;
		_contrs.push_back( std::move( container ) );
	}

	OnModified( ).Invoke( this );
	recalculate_text( );
}

void RichLabel::appendText(const __LIB String & _Text, __GRAPHICS Font * _Font )
{
	appendText( _Text, _Font, __DX Colors::White );
}

void RichLabel::appendText(const __LIB String & _Text, const __DX uint & _Color)
{
	appendText( _Text, getFont( ), _Color );
}

void RichLabel::appendText(const __LIB String & _Text)
{
	appendText( _Text, getFont( ), __DX Colors::White );
}

void RichLabel::appendText(__GRAPHICS Texture * _Texture)
{
	if ( _Texture->getSize( ) > __MATH Vector2{ 64, 64 } )
		return;
	TextContainer container;
	container.text = "";
	container.font = nullptr;
	container.color = 0;
	container.new_line = false;
	container.is_texture = true;
	container.texture = _Texture;
	_contrs.push_back( std::move( container ) );
	OnModified( ).Invoke( this );
	recalculate_text( );
}

__LIB String RichLabel::getText() const
{
	return _mtext;
}

void RichLabel::setText(const __LIB String & _Text)
{
	_contrs.clear( );
	_contrs.push_back( TextContainer{ nullptr, _Text, __DX Colors::White, getFont( ), false, false  } );
	recalculate_text( );
}

void RichLabel::recalculate_text()
{
	// Setup ze mutex just incase some retard appends text in another thread :|
	AsyncGuard guard{ _kpr };

	// Clear text container
	_all_text.clear( );

	for ( auto cont : _contrs )
	{
		RichText text;
		text.container = cont;
		text.position = { -1, -1 };
		text.size = { -1, -1 };
		_all_text.push_back( text );
	}

}









end_UI