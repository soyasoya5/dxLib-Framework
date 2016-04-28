#pragma once
#include "Component.h"


begin_UI

class Button : public Component
{
public:
	Button( );
	
	void Paint( Window *sender, BasePainter *painter ) override;
	
private:
	::dx::lib::Math::Vector2 determineText( ::dx::lib::Math::Vector2 &pos, ::dx::lib::Math::Vector2 &textSize );
	::dx::lib::Math::Vector2 _determ;
	bool _changed;
};

end_UI