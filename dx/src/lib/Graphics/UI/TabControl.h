#pragma once
#include "Component.h"

begin_UI
class Tab;

class TabControl : public Component
{
private:
	Tab *selected_;
	bool changed_;
	std::vector<bool> cache_;
	Math::Vector2 size_;
	std::vector<::dx::lib::Math::Vector2> cachedet_;
	std::vector<::dx::lib::Math::Vector2> sizecache_;
public:
	TabControl( );

	virtual void Paint( Window *sender, BasePainter *painter ) override;
	virtual void KeyDown( Window* sender, KeyDownArgs &args );
	virtual void KeyUp( Window* sender, KeyUpArgs &args );
	virtual void KeyDownChar( Window* sender, KeyDownCharArgs &args );
	virtual void MouseMoved( Window* sender, MouseMovedArgs &args );
	virtual void MouseClicked( Window* sender, MouseClickedArgs &args );
	virtual void MouseReleased( Window* sender, MouseReleasedArgs &args );
	virtual void MouseScrolled( Window* sender, ScrollArgs &args );
	virtual void MouseDoubleClicked( Window* sender, MouseClickedArgs &args );
	virtual void remove_child( Component *child ) override;
	void addTab( Tab *tab );
	void select( Tab *tab );
	Math::Vector2 get_tab_size( );
	Tab *selected( );

private:
	::dx::lib::Math::Vector2 determineText( ::dx::lib::Math::Vector2 & pos, ::dx::lib::Math::Vector2 & size, String text, std::shared_ptr<Font> font, ::dx::uint index );
};


end_UI