#pragma once
#include "lib.h"
#include "Component.h"

begin_UI

class Checkbox : public Component
{
public:
	Checkbox( );

	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter ) override;

};

end_UI