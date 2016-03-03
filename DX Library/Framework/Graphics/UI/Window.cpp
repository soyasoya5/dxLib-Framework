#include "Window.h"
#include "../Renderer/Renderer.h"

Graphics::UI::Window::Window()
	: _top(false)
{
}

void Graphics::UI::Window::Paint(Renderer::D9Renderer *r)
{
	OnPrePaint( ).Invoke( this, r );
	auto style = getStylesheet();
	auto foreground = style.get_argb( "ui_window", Style::Style_foreground );
	auto line = style.get_argb( "ui_window", Style::Style_line );
	auto text = style.get_argb( "ui_window", Style::Style_text );
	auto pos = getAbsolutePosition() + getPadding();
	auto size = getSize( );

	r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
	if (getAllignment() == Left)
	{
		r->String( pos.x + 5, pos.y + 5, getFont( ), text, getText( ) );
	}
	else
	{
		auto textsz = r->StrSize( getFont( ), getText( ) );
		r->String(pos.x + size.x - textsz.x - 5, pos.y + 5, getFont(), text, getText());
	}

	for ( auto&x : getChildren( ) )
		x->Paint( r );
	OnPostPaint( ).Invoke( this, r );
}

bool Graphics::UI::Window::OnMouseMove(Vector2 mouse)
{
	if ( _focusing )
	{
		auto pos = getAbsolutePosition();
		if (_moved.x != 0 && _moved.y != 0)
		{
			Vector2 increment = (mouse - pos) - (_moved - pos);
			setAbsolutePosition( pos + increment );
		}
		_moved = mouse;
	}

	return __super::OnMouseMove( mouse );
}

bool Graphics::UI::Window::OnLeftMouseDown(Vector2 mouse)
{
	if ( Collides( mouse ) && !CollidesWithChildren( mouse ) )
	{
		_focusing = true;
	}
	else {
		_focusing = false;
		_moved = { 0, 0 };
	}
	return __super::OnLeftMouseDown( mouse );
}

bool Graphics::UI::Window::OnLeftMouseUp(Vector2 mouse)
{
	_focusing = false;
	_moved = { 0, 0 };
	return __super::OnLeftMouseUp( mouse );
}

void Graphics::UI::Window::setTopMost(const bool &top)
{
	_top = top;
}

bool Graphics::UI::Window::TopMost()
{
	return _top;
}


