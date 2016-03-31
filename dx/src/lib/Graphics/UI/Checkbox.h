#pragma once
#include "Component.h"

begin_GRAPHICS class Texture; end_GRAPHICS

begin_UI

class Checkbox : public Component
{
public:
	Checkbox( );

	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter ) override;
};

end_UI