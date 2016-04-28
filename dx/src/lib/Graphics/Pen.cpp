#include "Pen.h"

begin_GRAPHICS

Pen::Pen()
	: color_( ::dx::Colors::White ), thickness_( 1 )
{
}

Pen::Pen(const ::dx::uint & color, const ::dx::uint & thickness)
	: color_( color ), thickness_( thickness )
{
}

::dx::uint Pen::Color() const
{
	return color_;
}

::dx::uint Pen::Thickness() const
{
	return thickness_;
}

void Pen::Color(const ::dx::uint & color)
{
	color_ = color;
}

void Pen::Thickness(const ::dx::uint & thickness)
{
	thickness_ = thickness;
}



end_GRAPHICS

