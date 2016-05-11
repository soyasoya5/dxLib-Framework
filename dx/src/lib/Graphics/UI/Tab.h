#pragma once
#include "Component.h"


begin_UI

class Tab : public Component
{
public:
	Tab( );
	~Tab( ) override;

	virtual void Paint( Window *sender, BasePainter *painter ) override;
	virtual void KeyDown( Window* sender, KeyDownArgs &args );
	virtual void KeyUp( Window* sender, KeyUpArgs &args );
	virtual void KeyDownChar( Window* sender, KeyDownCharArgs &args );
	virtual void MouseMoved( Window* sender, MouseMovedArgs &args );
	virtual void MouseClicked( Window* sender, MouseClickedArgs &args );
	virtual void MouseReleased( Window* sender, MouseReleasedArgs &args );
	virtual void MouseScrolled( Window* sender, ScrollArgs &args );
	virtual void MouseDoubleClicked( Window* sender, MouseClickedArgs &args );

	void addComponent( Component *component );

};

end_UI

