#include "Line.h"
#include "Pen.h"


begin_GRAPHICS

Line::Line()
	: _pen( ), _pos( ), _target( )
{
}

Line::Line(const __MATH Vector2 & _Position, const __MATH Vector2 & _Target, const __GRAPHICS Pen & _Pen)
	: _pos( _Position ), _target( _Target ), _pen( _Pen )
{
}

__GRAPHICS Pen Line::Pen() const
{
	return _pen;
}

__MATH Vector2 Line::Position() const
{
	return _pos;
}

__MATH Vector2 Line::Target() const
{
	return _target;
}

void Line::Pen(const __GRAPHICS Pen & _Pen)
{
	_pen = _Pen;
}

void Line::Position(const __MATH Vector2 & _Position)
{
	_pos = _Position;
}

void Line::Target(const __MATH Vector2 & _Target)
{
	_target = _Target;
}

end_GRAPHICS


