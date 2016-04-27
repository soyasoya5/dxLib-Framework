#pragma once
#include "Component.h"

begin_GRAPHICS class Texture; end_GRAPHICS

begin_UI

class Checkbox : public Component
{
public:
	Checkbox( );

	void Paint( Window *sender, BasePainter *painter ) override;

private:
	__MATH Vector2 determineText( __MATH Vector2 &pos, __MATH Vector2 &textSize );
	__MATH Vector2 determ_;
	bool changed_;

};

end_UI