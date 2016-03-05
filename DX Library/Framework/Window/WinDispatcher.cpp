#include "WinDispatcher.h"
#include "../Utils/Utils.h"

WinDispatcher::WinDispatcher()
{
	Utils::zeromem( rcast<byte*>( this->_keys ), 255 );
	Utils::zeromem( rcast<byte*>( this->_lastKeyDown ), 255 );
	Utils::zeromem( rcast<byte*>( this->_timeBuffer ), 255 * sizeof( uint ) );
	_lastMouseL = 0;
	_lastMouseR = 0;
	_pos = _rPos = _lPos = { 0, 0 };
}

bool WinDispatcher::PollEvents()
{
	// mouse stuf...
	POINT point;
	GetCursorPos( &point );
	Vector2 pos = { scast<float>( point.x ), scast<float>( point.y ) };
	if ( pos != _pos )
		OnMouseMove( ).Invoke( pos );
	_pos = pos;

	// key stuff...
	for (size_t i = 3; i < 255; i++) {
		bool is_pressed = (GetAsyncKeyState( i ) & 0x1) != 0;
		ManipulateKeystate( GetTickCount( ), i, is_pressed );
	}

	for (size_t i = 0; i < 3; i++) {
		bool is_pressed = (GetAsyncKeyState( i ) & 0x8000) != 0;
		ManipulateKeystate( GetTickCount( ), i, is_pressed );
	}

	return true;
}

bool WinDispatcher::isKeyDown(const uint &key)
{
	return _keys[key];
}

bool WinDispatcher::isCapitalToggled()
{
	return (GetAsyncKeyState( key_caps ) & 0x1) ? true : false;;
}

bool WinDispatcher::isShiftHeld()
{
	return ( ( GetAsyncKeyState( key_shift ) & 0x1 ) ? true : false ) || ( ( GetAsyncKeyState( key_leftShift ) & 0x1 ) ? true : false );
}

void WinDispatcher::ManipulateKeystate(const uint &tick, const uint &key, const byte & state)
{
	_keys[key] = state;
	if ( !_lastKeyDown[key] && state )
	{
		// Left mouse button
		if ( key == 1 ) 
		{
			OnLeftMouseDown( ).Invoke( _pos );
			if ( tick - _lastMouseL < 500 && _pos == _lPos )
				OnLeftMouseDoubleClick( ).Invoke( _pos );
			
			_lastMouseL = tick;
			_lPos = _pos;
		}
		else if ( key == 2 ) 
		{
			OnRightMouseDown( ).Invoke( _pos );
			if ( tick - _lastMouseR < 500 && _pos == _rPos )
				OnRightMouseDoubleClick( ).Invoke( _pos );

			_lastMouseR = tick;
			_rPos = _pos;
		}
		else
		{
			_timeBuffer[key] = tick + 75;
			OnKeyDown( ).Invoke( key );
			if ( key == key_space )
				OnKeyDownChar( ).Invoke( ' ' );
			else if ( key == key_backspace )
				OnKeyDownChar( ).Invoke( '\b' );
			else {
				byte buffer[2];
				auto len = ToAscii( key, MapVirtualKeyA( key, 2 ), rcast<byte*>( _keys ), ccast<LPWORD>( buffer ), 0 );
				if ( len == 1 ) 
				{
					auto key = buffer[0];
					if (::isalnum((unsigned char)key) ||
						key == ' ' || key == '.' || key == ','
						|| key == '-' || key == '<' || key == '\''
						|| key == '+') {
						

						if ( isShiftHeld( ) )
							key = isCapitalToggled( ) ? tolower( key ) : toupper( key );
						else if ( isCapitalToggled( ) )
							key = toupper( key );
						OnKeyDownChar( ).Invoke( key );
					}
				}
			}
		}
	}
	else if ( state && _lastKeyDown[key] && key > 2 && tick > _timeBuffer[key])
	{
		OnKeyDown( ).Invoke( key );
		_timeBuffer[key] = tick + 75;
		if ( key == key_space )
			OnKeyDownChar( ).Invoke( ' ' );
		else if ( key == key_backspace )
			OnKeyDownChar( ).Invoke( '\b' );
		else {
			byte buffer[2];
			auto len = ToAscii(key, MapVirtualKeyA(key, 2), rcast<byte*>(_keys), rcast<LPWORD>(buffer), 0);
			if ( len == 1 ) 
			{
				auto key = buffer[0];
				if (::isalnum((unsigned char)key) ||
					key == ' ' || key == '.' || key == ','
					|| key == '-' || key == '<' || key == '\''
					|| key == '+') {
					if ( isShiftHeld( ) )
						key = isCapitalToggled( ) ? tolower( key ) : toupper( key );
					OnKeyDownChar( ).Invoke( key );
				}
			}
		}
	}
		

	if ( !_keys[key] && _lastKeyDown[key] )
	{
		if ( key == 1 )
			OnLeftMouseUp( ).Invoke( _pos );
		else if ( key == 2 )
			OnRightMouseUp( ).Invoke( _pos );
		else if ( key > 2 )
			OnKeyUp( ).Invoke( key );
	}


	_lastKeyDown[key] = state;
}
