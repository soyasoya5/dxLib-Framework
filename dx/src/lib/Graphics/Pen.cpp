#include "Pen.h"

begin_GRAPHICS

Pen::Pen()
	: _color( __DX Colors::White ), _thickness( 1 )
{
}

Pen::Pen(const __DX uint & _Color, const __DX uint & _Thickness)
	: _color( _Color ), _thickness( _Thickness )
{
}

__DX uint Pen::Color() const
{
	return _color;
}

__DX uint Pen::Thickness() const
{
	return _thickness;
}

void Pen::Color(const __DX uint & _Color)
{
	_color = _Color;
}

void Pen::Thickness(const __DX uint & _Thickness)
{
	_thickness = _Thickness;
}



end_GRAPHICS

