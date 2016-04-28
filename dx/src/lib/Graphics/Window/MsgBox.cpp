#include "MsgBox.h"
#include "Window.h"

begin_GRAPHICS

MsgBox::MsgBox(const ::dx::lib::String & message, const ::dx::lib::String & title, const ::dx::uint & type)
	: MsgBox( nullptr, message, title, type )
{
}

MsgBox::MsgBox(::dx::lib::Graphics::Window * parent, const ::dx::lib::String & message, const ::dx::lib::String & title, const ::dx::uint & type)
: msg_( message ), title_( title ), type_( type ), parent_( parent )
{
}

MsgBox::DialogResult MsgBox::Show()
{
	return DialogResult( ::MessageBox( parent_ == nullptr ? nullptr : parent_->native_handle( ), 
									   msg_.c_str( ), 
									   title_.c_str( ), 
									   type_ ) );
}


end_GRAPHICS

