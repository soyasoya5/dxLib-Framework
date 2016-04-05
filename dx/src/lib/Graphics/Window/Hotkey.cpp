#include "Hotkey.h"
#include "Window.h"

begin_GRAPHICS

Hotkey::Hotkey()
	: _name( "unamed_hotkey" ), _subkeys( )
{
}

Hotkey::Hotkey(const __DX uint & _Key, const __LIB String & _Name)
	: _subkeys( { _Key } ), _name( _Name )
{
}

Hotkey::Hotkey(const std::vector<__DX uint>& _Keys, const __LIB String & _Name)
	: _name( _Name ), _subkeys( )
{
	for ( auto &x : _Keys )
		addSubkey( x );
}

Hotkey::~Hotkey()
{
}

void Hotkey::OnKeyDown(Window * Sender, KeyDownArgs & _Args)
{
	for ( auto &key : _subkeys )
		if ( _Args.key_code == key.first )
			key.second = true;
	
	bool c = true;
	for ( auto &key : _subkeys )
		if ( !key.second )
			c = false;
	if ( c )
		OnHotkey( ).Invoke( this, EventArgs( ) );
}

void Hotkey::OnKeyUp(Window * Sender, KeyUpArgs & _Args)
{
	for ( auto &key : _subkeys )
		if ( _Args.key_code == key.first )
			key.second = false;
}

void Hotkey::addSubkey(const __DX uint & _Key)
{
	_subkeys.push_back( { _Key, false } );
}

__LIB String Hotkey::getName()
{
	return _name;
}

__LIB String Hotkey::sequence_as_string()
{
	String res;
	for ( auto& key : _subkeys )
		res += __LIB to_string( key.first ) + ", ";
	return res;
}

__LIB Event<void(Hotkey*, __LIB EventArgs&)>& Hotkey::OnHotkey()
{
	return _OnHotkey;
}


end_GRAPHICS