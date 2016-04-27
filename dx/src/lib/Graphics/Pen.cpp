#include "Pen.h"

begin_GRAPHICS

Pen::Pen()
	: color_( __DX Colors::White ), thickness_( 1 )
{
}

Pen::Pen(const __DX uint & color, const __DX uint & thickness)
	: color_( color ), thickness_( thickness )
{
}

__DX uint Pen::Color() const
{
	return color_;
}

__DX uint Pen::Thickness() const
{
	return thickness_;
}

void Pen::Color(const __DX uint & color)
{
	color_ = color;
}

void Pen::Thickness(const __DX uint & thickness)
{
	thickness_ = thickness;
}



end_GRAPHICS

