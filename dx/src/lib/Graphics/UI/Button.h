#pragma once
#include "Component.h"


begin_UI

class Button : public Component
{
public:
	Button( );
	
	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter ) override;
	
private:
	__MATH Vector2 determineText( __MATH Vector2 &pos, __MATH Vector2 &text_size );
};

end_UI