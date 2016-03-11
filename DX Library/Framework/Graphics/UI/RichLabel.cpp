#include "RichLabel.h"
#include "../Renderer/Renderer.h"
#include "../FontMetrics/Font.h"
#include "../FontMetrics/Metrics.h"



void Graphics::UI::RichLabel::Paint(Renderer::D9Renderer *r)
{
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, r );


	Vector2 current_pos, o_pos{ getAbsolutePosition( ) + getPadding( ) };
	current_pos = o_pos;
	Vector2 size = { 0, 0 };
	FontMetrics::Metrics metrics( r->fontAt( getFont( ) ) );

	for ( auto& text : _texts )
	{
		auto in_size = metrics.SizeOfString( text.text );
		size.x += in_size.x;
		r->String( current_pos.x, current_pos.y, getFont( ), text.color, text.text );
		current_pos.x += in_size.x;
		if ( text.newline ) {
			size.y += in_size.y;
			current_pos.y += in_size.y;
			current_pos.x = o_pos.x;
		}

		if ( size.y == 0 )
			size.y = in_size.y;
	}

	setSize( size );
	OnPostPaint( ).Invoke( this, r );
}

bool Graphics::UI::RichLabel::OnMouseMove(Vector2 mouse)
{
	if ( !isVisible( ) || !isEnabled( ) )
		return true;

	if ( Collides( mouse ) )
	{
		if ( !_hovered )
			OnMouseEnter( ).Invoke( this, mouse );
		_hovered = true;
	}
	else
	{
		if ( _hovered )
			OnMouseLeave( ).Invoke( this, mouse );
		_hovered = false;
	}
	return __super::OnMouseMove( mouse );
}

bool Graphics::UI::RichLabel::OnLeftMouseDown(Vector2 mouse)
{
	if ( !isVisible( ) || !isEnabled( ) )
		return true;

	if ( Collides( mouse ) )
		_focusing = true;
	else
		_focusing = false;
	return __super::OnLeftMouseDown( mouse );
}

bool Graphics::UI::RichLabel::OnLeftMouseUp(Vector2 mouse)
{
	if ( !isVisible( ) || !isEnabled( ) )
		return true;

	if ( Collides( mouse ) )
	{
		OnComponentClicked( ).Invoke( this, mouse );
	}

	_focusing = false;
	return __super::OnLeftMouseUp( mouse );
}

void Graphics::UI::RichLabel::appendText(const Utils::String & text, const Color & color)
{
	if ( text.contains( "\n" ) )
	{
		auto each = text.split( "\n" );
		for ( auto&x : each )
		{
			RichText comp;
			comp.newline = true;
			comp.text = x;
			comp.color = color;
			_texts.push_back( comp );
		}
		return;
	}
	RichText comp;
	comp.newline = false;
	comp.text = text;
	comp.color = color;
	_texts.push_back( comp );
}

Vector2 Graphics::UI::RichLabel::getTextSize_unsafe( Renderer::D9Renderer *r )
{
	Vector2 size = { 0, 0 };
	FontMetrics::Metrics metrics( r->fontAt( getFont( ) ) );
	for (auto& text : _texts) {
		auto tsize = metrics.SizeOfString(text.text);
		if ( tsize.x > size.x )
			size.x += tsize.x;
		if ( text.newline )
			size.y += tsize.y;
	}
	return size;
}

void Graphics::UI::RichLabel::popLast()
{
	_texts.pop_back( );
}

Graphics::UI::RichLabel& Graphics::UI::RichLabel::operator+=( const Text& other )
{
	appendText( other.getText( ), other.getColor( ) );
	return *this;
}

Graphics::UI::Text::Text(const Utils::String & text, const Color & color)
	: text(text), color(color)
{
}

Utils::String Graphics::UI::Text::getText() const
{
	return text;
}

Color  Graphics::UI::Text::getColor() const
{
	return color;
}



