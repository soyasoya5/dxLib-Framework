#pragma once
#include "Component.h"

begin_GRAPHICS class Texture; end_GRAPHICS

begin_UI

class Checkbox : public Component
{
public:
	Checkbox( );

	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter ) override;

private:
	__MATH Vector2 determineText( __MATH Vector2 &_Pos, __MATH Vector2 &_TextSize );
	__MATH Vector2 _determ;
	bool _changed;

};

end_UI