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
	static Painter *Create( Window *target, const bool &windowed = true, const bool &singleton = true );
	~Painter( );

	///<summary>
	///	Clears the target and Begins the scene.
	///</summary>
	bool ResetPainter( const ::dx::lib::Math::Vector2 &size, ::dx::lib::Graphics::Window *target );

	void BeginPaint( ) override;

	virtual void Paint( const ::dx::lib::Graphics::Text &text, const ::dx::lib::Graphics::Pen &pen ) override;

	virtual void Paint( const ::dx::lib::Graphics::Shape &shape ) override;

	virtual void Paint( const ::dx::lib::Graphics::Circle &circle ) override;

	virtual void PaintRect( const ::dx::lib::Math::Region &region, const ::dx::lib::Graphics::Pen &pen ) override;

	virtual void PaintRectOutlined( const ::dx::lib::Math::Region &region, const ::dx::lib::Graphics::Pen &inner, const ::dx::lib::Graphics::Pen &outer ) override;

	virtual void PaintLine( const ::dx::lib::Graphics::Line &line ) override;

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