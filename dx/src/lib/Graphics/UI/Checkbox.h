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
	::dx::lib::Math::Vector2 determineText( ::dx::lib::Math::Vector2 &pos, ::dx::lib::Math::Vector2 &textSize );
	::dx::lib::Math::Vector2 determ_;
	bool changed_;

};

end_UI