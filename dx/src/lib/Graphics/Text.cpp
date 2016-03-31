#include "Text.h"

begin_GRAPHICS

Text::Text()
	: _font(nullptr), _text(), _position(), _max( { 500, 200 } ), _allign(Top)
{
}

Text::Text(__GRAPHICS Font * _Font, const __LIB String & _Text, const __MATH Vector2 & _Position, const __MATH Vector2 &_Clip, const __GRAPHICS TextAllignment &_Allignment)
	: _font( _Font ), _text( _Text ), _position( _Position ), _allign( _Allignment ), _max( _Clip )
{
}

__GRAPHICS Font * Text::getFont() const
{
	return _font;
}

void Text::setFont(__GRAPHICS Font * _Font)
{
	_font = _Font;
}

__GRAPHICS TextAllignment Text::getAllignment() const
{
	return _allign;
}

void Text::setAllignment(const __GRAPHICS TextAllignment & _Allignment)
{
	_allign = _Allignment;
}

__LIB String Text::getText() const
{
	return _text;
}

void Text::setText(const __LIB String & _Text) 
{
	_text = _Text;
}

__MATH Vector2 Text::getPosition() const
{
	return _position;
}

void Text::setPosition(const __MATH Vector2 & _Position)
{
	_position = _Position;
}

__MATH Vector2 Text::getMaxClip() const
{
	return _max;
}

void Text::setMaxClip(const __MATH Vector2 & _Clip)
{
	_max = _Clip;
}


end_GRAPHICS