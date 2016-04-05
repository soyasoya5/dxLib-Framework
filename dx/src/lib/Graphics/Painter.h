#pragma once
#include "BasePainter.h"

begin_MATH class Vector2; end_MATH

begin_GRAPHICS
class Window;
class Font;

	// DirectX9 Painter

/// summaries in 'BasePainter'
class Painter : BasePainter
{
public:

	///<summary>
	/// Create a Painter for '_Target' window.
	///</summary>
	static Painter *Create( __GRAPHICS Window *_Target, const bool &_Windowed = true, const bool &_Singleton = true );
	~Painter( );



	///<summary>
	///	Clears the target and Begins the scene.
	///</summary>
	bool ResetPainter( const __MATH Vector2 &_Size, __GRAPHICS Window *_Target );

	void BeginPaint( ) override;
	virtual void Paint( const __GRAPHICS Text &_Text, const __GRAPHICS Pen &_Pen ) override;
	virtual void Paint( const __GRAPHICS Shape &_Shape ) override;
	virtual void Paint( const __GRAPHICS Circle &_Circle ) override;
	virtual void PaintRect( const __MATH Region &_Region, const __GRAPHICS Pen &_Pen ) override;
	virtual void PaintRectOutlined( const __MATH Region &_Region, const __GRAPHICS Pen &_PenInner, const __GRAPHICS Pen &_PenOuter ) override;
	virtual void PaintLine( const __GRAPHICS Line &_Line ) override;
	virtual void PresentPaint( ) override;
	virtual void* native( ) const override;
	__GRAPHICS Font *defaultFont( ) const override;
	void setDefaultFont( __GRAPHICS Font *_Font ) override;

private:
	void *_device, *_d3dobj, *_line;
	__GRAPHICS Window *_target;
	__GRAPHICS Font *_default;
	Painter( );
};



end_GRAPHICS