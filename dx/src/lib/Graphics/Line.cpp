#include "Line.h"
#include "Pen.h"


begin_GRAPHICS

Line::Line()
	: pen_( ), pos_( ), target_( )
{
}

Line::Line(const ::dx::lib::Math::Vector2 & position, const ::dx::lib::Math::Vector2 & target, const ::dx::lib::Graphics::Pen & pen)
	: pos_( position ), target_( target ), pen_( pen )
{
}

::dx::lib::Graphics::Pen Line::Pen() const
{
	return pen_;
}

::dx::lib::Math::Vector2 Line::Position() const
{
	return pos_;
}

::dx::lib::Math::Vector2 Line::Target() const
{
	return target_;
}

void Line::Pen(const ::dx::lib::Graphics::Pen & pen)
{
	pen_ = pen;
}

void Line::Position(const ::dx::lib::Math::Vector2 & position)
{
	pos_ = position;
}

void Line::Target(const ::dx::lib::Math::Vector2 & target)
{
	target_ = target;
}

end_GRAPHICS


