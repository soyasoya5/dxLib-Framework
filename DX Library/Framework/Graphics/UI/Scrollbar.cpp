#include "Scrollbar.h"
#include "../Renderer/Renderer.h"

float Graphics::UI::Scrollbar::CalculateScroll()
{
	if (getType() == Horizontal)
		return (_barPos.x / (getSize().x - _barSize.x)) * getMax();
	else
		return (_barPos.y / (getSize().y - _barSize.y)) * getMax();
}

float Graphics::UI::Scrollbar::CalculateBar()
{
	if (getType() == Horizontal)
		return ((float)getState() / getMax()) * (getSize().x - _barSize.x);
	else
		return ((float)getState() / getMax()) * (getSize().y - _barSize.y);
}

void Graphics::UI::Scrollbar::UpdateBar()
{
	if (getType() == Horizontal)
		_barPos.x = CalculateBar();
	else
		_barPos.y = CalculateBar();
}

void Graphics::UI::Scrollbar::UpdateScroll()
{
	setState(scast<int>(CalculateScroll()));
}

int Graphics::UI::Scrollbar::getScroll()
{
	return getState();
}

void Graphics::UI::Scrollbar::setScroll(const int & id)
{
	setState( id );
	UpdateBar();
}

Vector2 Graphics::UI::Scrollbar::getBarPos()
{
	return _barPos;
}

void Graphics::UI::Scrollbar::setBarPos(const Vector2 &pos)
{
	if (pos.x < 0 || pos.y < 0)
		return;
	if (getType() == Horizontal)
	{
		if ( pos.x > (getSize().x - _barSize.x) )
			return;
		_barPos = pos;
		_barPos.y = 0;
	}
	else
	{
		if (pos.y >(getSize().y - _barSize.y))
			return;
		_barPos = pos;
		_barPos.x = 0;
	}

	UpdateScroll();
}

Vector2 Graphics::UI::Scrollbar::getBarSize()
{
	return _barSize;
}

void Graphics::UI::Scrollbar::setBarSize(const Vector2 &size)
{
	auto sz = getSize();
	_barSize = size;
	if (getType() == Horizontal)
		_barSize.y = sz.y;
	else
		_barSize.x = sz.x;
}

bool Graphics::UI::Scrollbar::BarCollides(const Vector2 &)
{
	return false;
}

void Graphics::UI::Scrollbar::Paint(Graphics::Renderer::D9Renderer *r)
{
	if ( !isVisible( ) )
		return;
	OnPrePaint().Invoke( this, r );


	auto pos = getAbsolutePosition() + getPadding();
	auto size = getSize();
	auto style = getStylesheet();
	auto foreground = style.get_argb( "ui_scrollbar", Style::Style_foreground );
	auto line = style.get_argb( "ui_scrollbar",  Style::Style_line );

	r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
	if (_barhover)
	{
		auto ex = style.get_argb( "ui_scrollbar_hover", 0 );
		r->Rect( pos.x + _barPos.x, pos.y + _barPos.y, _barSize.x, _barSize.y, ex );
	}
	else
	{
		auto ex = style.get_argb( "ui_scrollbar", Style::Style_extra );
		r->Rect( pos.x + _barPos.x, pos.y + _barPos.y, _barSize.x, _barSize.y, ex );
	}
	
	OnPostPaint().Invoke( this, r );
}

bool Graphics::UI::Scrollbar::OnMouseMove(Vector2 mouse)
{
	if ( !isVisible( ) || !isEnabled( ) )
		return true;

	if  ( _clicking )
	{ 
		auto pos = getAbsolutePosition() + getPadding();
		if (_moved.x != 0 && _moved.y != 0)
		{
			Vector2 increment = (mouse - pos) - (_moved - pos);
			setBarPos(_barPos + increment);
		}
		_moved = mouse;
	}

	if ( BarCollides( mouse ) )
	{
		_barhover = true;
	}
	else
		_barhover = false;

	if ( Collides( mouse ) )
	{
		OnMouseEnter().Invoke( this, mouse );
		_hovered = true;
	}
	else {
		if (_hovered)
			OnMouseLeave().Invoke( this, mouse );
		_hovered = false;
	}

	return __super::OnMouseMove( mouse );
}

bool Graphics::UI::Scrollbar::OnLeftMouseDown(Vector2 mouse)
{
	if ( !isVisible( ) || !isEnabled( ) )
		return true;

	if ( Collides( mouse ) )
	{
		OnComponentClicked().Invoke( this, mouse );
		_focusing = true;
		_clicking = true;
	}
	else {
		_focusing = false;
		_clicking = false;
		_moved = { 0.0f, 0.0f };
	}

	return __super::OnLeftMouseDown( mouse );
}

bool Graphics::UI::Scrollbar::OnLeftMouseUp(Vector2 mouse)
{
	if ( !isVisible( ) || !isEnabled( ) )
		return true;

	_clicking = false;
	if ( !Collides( mouse ) ) {
		_focusing = false;
		_moved = { 0.0f, 0.0f };
	}
	return __super::OnLeftMouseUp( mouse );
}

bool Graphics::UI::Scrollbar::OnRightMouseDown(Vector2 mouse)
{
	return __super::OnRightMouseDown( mouse );
}

bool Graphics::UI::Scrollbar::OnRightMouseUp(Vector2 mouse)
{
	return __super::OnRightMouseUp( mouse );
}

bool Graphics::UI::Scrollbar::OnKeyDown(uint key)
{
	return __super::OnKeyDown(key);

	if (getType() == Horizontal)
	{
		if ( key == key_left && isFocused( ) )
			setScroll( getScroll() - (getMax() / 10) );
		else if ( key == key_right && isFocused( ) )
			setScroll( getScroll( ) + (getMax() / 10) );
	}
	else {
		if ( key == key_up && isFocused( ) )
			setScroll( getScroll( ) - (getMax() / 10) );
		else if ( key == key_down && isFocused( ) )
			setScroll( getScroll( ) + (getMax() / 10) );
	}
}

bool Graphics::UI::Scrollbar::OnKeyUp(uint mouse)
{
	return __super::OnKeyUp( mouse );
}


