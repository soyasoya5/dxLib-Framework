#include "Hotkey.h"
#include "Window.h"

begin_GRAPHICS

Hotkey::Hotkey()
	: name_( "unamed_hotkey" ), subkeys_( )
{
}

Hotkey::Hotkey(uint key, String name)
	: subkeys_( { std::move( key ) } ), name_( std::move( name ) )
{
}

Hotkey::Hotkey(std::vector<uint> keys, String name)
	: name_( name ), subkeys_( std::move( keys ) )
{
}

Hotkey::~Hotkey()
{
}

void Hotkey::OnKeyDown(Window* sender, KeyDownArgs & args)
{
	auto i = 0u;
	for ( auto &key : subkeys_ )
		if ( sender->isKeyDown( key ) )
			++i;

	// Raise event
	if ( i != 0 && i == subkeys_.size( ) )
		_OnHotkey.Invoke( this, EventArgs( ) );
}


void Hotkey::addSubkey(uint key)
{
	subkeys_.push_back( key );
}

__LIB String Hotkey::getName()
{
	return name_;
}

__LIB String Hotkey::sequence_as_string()
{
	String res;
	for ( auto& key : subkeys_ )
		res += __LIB to_string( key ) + ", ";
	if ( !res.empty( ) )
		res.pop_back( ), res.pop_back( );
	return res;
}

__LIB Event<void(Hotkey*, __LIB EventArgs&)>& Hotkey::OnHotkey()
{
	return _OnHotkey;
}


end_GRAPHICS