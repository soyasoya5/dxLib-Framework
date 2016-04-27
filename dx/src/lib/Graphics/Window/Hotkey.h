#pragma once
#include "../lib.h"
#include "../../../dx.h"
#include "../../event.h"
#include "../../string.h"

begin_GRAPHICS

// TODO: Finish implementation

class Hotkey
{
public:

	///<summary>
	///	Empty constructor
	///</summary>
	Hotkey( );

	///<summary>
	/// Construct this Hotkey with _Key as the key and _Name as the Name.
	///</summary>
	Hotkey( __DX uint key, __LIB String name );

	///<summary>
	/// Construct this Hotkey with an amount of keys as the key and _Name as the Name.
	///</summary>
	Hotkey( std::vector<__DX uint> keys, __LIB String _Name );

	~Hotkey( );

	///<summary>
	///	Should be raised whenever the window managing the hotkey raises a KeyDown event
	///</summary>
	void OnKeyDown( Window* sender, KeyDownArgs &args );

	///<summary>
	///	Should be raised whenever the window managing the hotkey raises a KeyUp event.
	///</summary>
	void addSubkey( uint key );


	///<summary>
	///	Should be raised whenever the window managing the hotkey raises a KeyUp event.
	///</summary>
	__LIB String getName( );

	///<summary>
	///	Returns all _subkeys formated as such: ('KEY' ',')...
	///</summary>
	__LIB String sequence_as_string( );

	///<summary>
	///	Raised when the hotkey is pressed.
	///</summary>
	__LIB Event<void(Hotkey*, __LIB EventArgs&)> &OnHotkey( );
private:
	std::vector<uint> subkeys_;
	__LIB String name_;
	__LIB Event<void(Hotkey*, __LIB EventArgs&)> _OnHotkey;
};


end_GRAPHICS

