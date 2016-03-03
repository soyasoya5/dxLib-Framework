#pragma once
#include "EventDispatcher.h"


class WinDispatcher : public EventDispatcher
{
private:
	bool					_keys[255];
	bool					_lastKeyDown[255];
	uint					_timeBuffer[255];
	uint					_lastMouseL, _lastMouseR;
	Vector2					_pos, _rPos, _lPos;
public:
	WinDispatcher( );

	// this function always returns true.
	bool PollEvents( ) override;


	// This dispatcher also provides some simple functions
	// if you dont wanna do event based coding.
	bool isKeyDown( const uint& key );
	

	void ManipulateKeystate( const uint &tick, const uint &key, const byte& state );
};

