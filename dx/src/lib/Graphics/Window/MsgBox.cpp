#include "MsgBox.h"
#include "Window.h"

begin_GRAPHICS

MsgBox::MsgBox(const __LIB String & message, const __LIB String & title, const __DX uint & type)
	: MsgBox( nullptr, message, title, type )
{
}

MsgBox::MsgBox(__GRAPHICS Window * parent, const __LIB String & message, const __LIB String & title, const __DX uint & type)
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

