#include "MsgBox.h"
#include "Window.h"

begin_GRAPHICS

MsgBox::MsgBox(const __LIB String & _Message, const __LIB String & _Title, const __DX uint & _Type)
	: _msg( _Message ), _title( _Title ), _type( _Type ), _parent( nullptr )
{
}

MsgBox::MsgBox(__GRAPHICS Window * _Parent, const __LIB String & _Message, const __LIB String & _Title, const __DX uint & _Type)
: _msg( _Message ), _title( _Title ), _type( _Type ), _parent( _Parent )
{
}

MsgBox::DialogResult MsgBox::Show()
{
	return DialogResult( ::MessageBox( _parent == nullptr ? nullptr : _parent->native_handle( ), 
									   _msg.c_str( ), 
									   _title.c_str( ), 
									   _type ) );
}


end_GRAPHICS

