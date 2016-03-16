#pragma once
#include "lib.h"
#include "../../dx.h"
	// Base class for renders



begin_MATH class Region; end_MATH

begin_GRAPHICS
class Shape;
class Text;
class Line;
class Pen;


class BasePainter
{
public:
		// Destructor
	virtual ~BasePainter( ) { };

	///<summary>
	///	Begins the painting process
	///</summary>
	virtual void BeginPaint( ) = 0;

	///<summary>
	///	Paint text onto the target buffer.
	///</summary>
	virtual void Paint( __GRAPHICS Text &_Text, const __GRAPHICS Pen &_Pen ) = 0;

	///<summary>
	///	Paint a shape onto the target buffer.
	///</summary>
	virtual void Paint( __GRAPHICS Shape &_Shape ) = 0;

	///<summary>
	///	Paint a rect onto the target buffer.
	///</sumamry>
	virtual void PaintRect( __MATH Region &_Region, const __GRAPHICS Pen &_Pen ) = 0;

	///<summary>
	///	Paint a outlined rect onto the target buffer.
	/// The outlines thickness is taken from the outer pen. (_PenOuter)
	///</sumamry>
	virtual void PaintRectOutlined( __MATH Region &_Region, const __GRAPHICS Pen &_PenInner, const __GRAPHICS Pen &_PenOuter ) = 0;

	///<summary>
	///	Paints a line onto the target buffer.
	///</summary>
	virtual void PaintLine( __GRAPHICS Line &_Line ) = 0;

	///<summary>
	/// 'Paint' the target buffer onto target screen.
	///</summary>
	virtual void PresentPaint( ) = 0;
};

end_GRAPHICS
