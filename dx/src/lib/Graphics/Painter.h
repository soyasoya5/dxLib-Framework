#pragma once
#include "BasePainter.h"

begin_MATH class Vector2; end_MATH

begin_GRAPHICS
class Font;
class Window;

	// DirectX9 Painter

/// summaries in 'BasePainter'
class Painter : BasePainter
{
public:

	///<summary>
	/// Create a Painter for '_Target' window.
	///</summary>
	static Painter *Create( std::shared_ptr<Window> target, const bool &windowed = true, const bool &singleton = true );
	~Painter( );

	///<summary>
	///	Clears the target and Begins the scene.
	///</summary>
	bool ResetPainter( const __MATH Vector2 &size, __GRAPHICS Window *target );

	void BeginPaint( ) override;

	virtual void Paint( const __GRAPHICS Text &text, const __GRAPHICS Pen &pen ) override;

	virtual void Paint( const __GRAPHICS Shape &shape ) override;

	virtual void Paint( const __GRAPHICS Circle &circle ) override;

	virtual void PaintRect( const __MATH Region &region, const __GRAPHICS Pen &pen ) override;

	virtual void PaintRectOutlined( const __MATH Region &region, const __GRAPHICS Pen &inner, const __GRAPHICS Pen &outer ) override;

	virtual void PaintLine( const __GRAPHICS Line &line ) override;

	virtual void PresentPaint( ) override;

	virtual void* native( ) const override;

	std::shared_ptr<Font> defaultFont( ) const override;

	void setDefaultFont( std::shared_ptr<Font> font ) override;

private:
	void *device_, *d3dobj_, *line_;
	std::shared_ptr<Window> target_;
	std::shared_ptr<Font> default_;
	Painter( );
};



end_GRAPHICS