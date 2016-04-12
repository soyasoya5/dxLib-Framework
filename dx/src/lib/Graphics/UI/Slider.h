#pragma once
#include "Component.h"

begin_UI
class Textbox;
class RichLabel;

class Slider : public Component
{
public:
	Slider( );

	~Slider( );

	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter ) override;

	void KeyDown( __GRAPHICS Window *_Sender, __GRAPHICS KeyDownArgs &_Args ) override;

	void KeyUp( __GRAPHICS Window *_Sender, __GRAPHICS KeyUpArgs &_Args ) override;

	void KeyDownChar( __GRAPHICS Window *_Sender, __GRAPHICS KeyDownCharArgs &_Args ) override;

	void MouseMoved( __GRAPHICS Window *_Sender, __GRAPHICS MouseMovedArgs &_Args ) override;

	void MouseClicked( __GRAPHICS Window *_Sender, __GRAPHICS MouseClickedArgs &_Args ) override;

	void MouseReleased( __GRAPHICS Window *_Sender, __GRAPHICS MouseReleasedArgs &_Args ) override;

	__MATH Vector2 getDelta( ) const;

	void setMaxDelta( const float &_Delta );

	float getMaxDelta( ) const;

	void setWheel( const float &_Delta );
	
	float getWheel( ) const;

	void setWheelSize( const __MATH Vector2 &_Size );

	__MATH Vector2 getWheelSize( ) const;


	bool CollidesWheel( const __MATH Vector2 &_Position );

	bool inScrollableRegion( const __MATH Vector2 &_Cursor ) const;

	const Textbox *getTextbox( ) const;


private:
	void moveWheelToDelta( );
	__MATH Vector2 _moved, _wheel, _wheelSize, _delta;
	Textbox *_textbox;
	bool _changed, _dragging;
	float _maxDelta;
};



end_UI




