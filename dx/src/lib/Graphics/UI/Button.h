#pragma once
#include "Component.h"


begin_UI

class Button : public Component
{
public:
	Button( );
	
	void Paint( Window *sender, BasePainter *painter ) override;
	
private:
	__MATH Vector2 determineText( __MATH Vector2 &pos, __MATH Vector2 &textSize );
	__MATH Vector2 _determ;
	bool _changed;
};

end_UI