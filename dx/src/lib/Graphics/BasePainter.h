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
class Font;
class Circle;


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
	virtual void Paint( const __GRAPHICS Text &text, const __GRAPHICS Pen &pen ) = 0;

	///<summary>
	///	Paint a shape onto the target buffer.
	///</summary>
	virtual void Paint( const __GRAPHICS Shape &shape ) = 0;

	///<summary>
	/// Paint a circle onto the target buffer.
	///</summary>
	virtual void Paint( const __GRAPHICS Circle &circle ) = 0;

	///<summary>
	///	Paint a rect onto the target buffer.
	///</sumamry>
	virtual void PaintRect( const __MATH Region &region, const __GRAPHICS Pen &pen ) = 0;

	///<summary>
	///	Paint a outlined rect onto the target buffer.
	/// The outlines thickness is taken from the outer pen. (_PenOuter)
	///</sumamry>
	virtual void PaintRectOutlined( const __MATH Region &region, const __GRAPHICS Pen &inner, const __GRAPHICS Pen &outer ) = 0;

	///<summary>
	///	Paints a line onto the target buffer.
	///</summary>
	virtual void PaintLine( const __GRAPHICS Line &line ) = 0;

	///<summary>
	/// 'Paint' the target buffer onto target screen.
	///</summary>
	virtual void PresentPaint( ) = 0;

	///<summary>
	/// get the default font
	///</summary>
	virtual std::shared_ptr<Font> defaultFont( ) const = 0;

	///<summary>
	/// set the default font.
	///</summary>
	virtual void setDefaultFont( std::shared_ptr<Font> font ) = 0;

	///<summary>
	///	A native-ish device, e.g a directx device.
	///</summary>
	virtual void* native( ) const = 0;

	///<summary>
	///	Get the BasePainter singleton pointer.
	///</summary>
	static BasePainter* getSingleton( );

	///<summary>
	///	Set the BasePainter Singleton pointer.
	///</summary>
	static void setSingleton( BasePainter *ptr );

private:
	static BasePainter* _Singleton;

};

end_GRAPHICS
