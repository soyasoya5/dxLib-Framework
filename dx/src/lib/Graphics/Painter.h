#pragma once
#include "BasePainter.h"

begin_MATH class Vector2; end_MATH

begin_GRAPHICS
class Window;
class Font;

	// DirectX9 Painter
class Painter : BasePainter
{
public:
	static Painter *Create( __GRAPHICS Window *_Target, const bool &_Windowed = true, const bool &_Singleton = true );
	~Painter( );


	bool ResetPainter( const __MATH Vector2 &_Size, __GRAPHICS Window *_Target );
		// Summaries can be found in "BasePainter.h"
	void BeginPaint( ) override;
	virtual void Paint( const __GRAPHICS Text &_Text, const __GRAPHICS Pen &_Pen ) override;
	virtual void Paint( const __GRAPHICS Shape &_Shape ) override;
	virtual void PaintRect( const __MATH Region &_Region, const __GRAPHICS Pen &_Pen ) override;
	virtual void PaintRectOutlined( const __MATH Region &_Region, const __GRAPHICS Pen &_PenInner, const __GRAPHICS Pen &_PenOuter ) override;
	virtual void PaintLine( const __GRAPHICS Line &_Line ) override;
	virtual void PresentPaint( ) override;
	virtual void* native( ) override;

	__GRAPHICS Font *defaultFont( );
	void setDefaultFont( __GRAPHICS Font *_Font );
private:
	void *_device, *_d3dobj, *_line;
	__GRAPHICS Window *_target;
	__GRAPHICS Font *_default;
	Painter( );
};



end_GRAPHICS