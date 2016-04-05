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
	Hotkey( const __DX uint &_Key, const __LIB String &_Name );

	///<summary>
	/// Construct this Hotkey with an amount of keys as the key and _Name as the Name.
	///</summary>
	Hotkey( const std::vector<__DX uint> &_Keys, const __LIB String &_Name );

	~Hotkey( );

	///<summary>
	///	Should be raised whenever the window managing the hotkey raises a KeyDown event
	///</summary>
	void OnKeyDown( Window *Sender, KeyDownArgs &_Args );

	///<summary>
	///	Should be raised whenever the window managing the hotkey raises a KeyUp event.
	///</summary>
	void OnKeyUp( Window *Sender, KeyUpArgs &_Args );

	///<summary>
	///	Should be raised whenever the window managing the hotkey raises a KeyUp event.
	///</summary>
	void addSubkey( const __DX uint &_Key );


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
	std::vector<std::pair<__DX uint, bool>> _subkeys;
	__LIB Event<void(Hotkey*, __LIB EventArgs&)> _OnHotkey;
	__LIB String _name;
};


end_GRAPHICS

