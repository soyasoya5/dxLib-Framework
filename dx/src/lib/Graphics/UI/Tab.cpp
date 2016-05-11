#include "Tab.h"

begin_UI

Tab::Tab()
	: Component( )
{
}

Tab::~Tab()
{
}

void Tab::Paint(::dx::lib::Graphics::Window * sender, ::dx::lib::Graphics::BasePainter * painter)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->Paint( sender, painter );
}

void Tab::KeyDown(Window * sender, KeyDownArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->KeyDown( sender, args );
}

void Tab::KeyUp(Window * sender, KeyUpArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->KeyUp( sender, args );
}

void Tab::KeyDownChar(Window * sender, KeyDownCharArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->KeyDownChar( sender, args );
}

void Tab::MouseMoved(Window * sender, MouseMovedArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->MouseMoved( sender, args );
}

void Tab::MouseClicked(Window * sender, MouseClickedArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->MouseClicked( sender, args );
}

void Tab::MouseReleased(Window * sender, MouseReleasedArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->MouseReleased( sender, args );
}

void Tab::MouseScrolled(Window * sender, ScrollArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->MouseScrolled( sender, args );
}

void Tab::MouseDoubleClicked(Window * sender, MouseClickedArgs & args)
{
	if ( !visible_ )
		return;

	for ( auto &x : children_ )
		x->MouseDoubleClicked( sender, args );
}

void Tab::addComponent(Component * component)
{
	Component::children_.push_back( component );
}




end_UI