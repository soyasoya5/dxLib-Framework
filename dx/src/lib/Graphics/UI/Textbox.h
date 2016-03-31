#pragma once
#include "Component.h"


begin_UI

class Textbox : public Component
{
public:
	Textbox( );

	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter );

	void KeyDownChar( __GRAPHICS Window *_Sender, __GRAPHICS KeyDownCharArgs &_Args ) override;
	void MouseClicked( __GRAPHICS Window *_Sender, __GRAPHICS MouseClickedArgs &_Args ) override;
	void MouseReleased( __GRAPHICS Window *_Sender, __GRAPHICS MouseReleasedArgs &_Args ) override;

public:
	bool getCanWrite( ) const;
	bool isMultiline( ) const;
	__LIB String getPromptText( ) const;
	char getPasswordChar( ) const;
	bool getUsePasswordChar( ) const;

	void setCanWrite( const bool &_Can );
	void setPromptText( const __LIB String &_Text );
	void setPasswordChar( const char &_Char );
	void setUsePasswordChar( const bool &_Use );
	void setMultiline( const bool &_Can );
	
private:
	__MATH Vector2 determineText( __MATH Vector2 &_Pos, __MATH Vector2 &_TextSize );
	bool _canwrite;
	__LIB String _prompt;
	char _passwordChar;
	bool _usePasswordChar;
	bool _multiline, _blink;
	__DX uint _lblink;
};


end_UI