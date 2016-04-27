#include "Line.h"
#include "Pen.h"


begin_GRAPHICS

Line::Line()
	: pen_( ), pos_( ), target_( )
{
}

Line::Line(const __MATH Vector2 & position, const __MATH Vector2 & target, const __GRAPHICS Pen & pen)
	: pos_( position ), target_( target ), pen_( pen )
{
}

__GRAPHICS Pen Line::Pen() const
{
	return pen_;
}

__MATH Vector2 Line::Position() const
{
	return pos_;
}

__MATH Vector2 Line::Target() const
{
	return target_;
}

void Line::Pen(const __GRAPHICS Pen & pen)
{
	pen_ = pen;
}

void Line::Position(const __MATH Vector2 & position)
{
	pos_ = position;
}

void Line::Target(const __MATH Vector2 & target)
{
	target_ = target;
}

end_GRAPHICS


