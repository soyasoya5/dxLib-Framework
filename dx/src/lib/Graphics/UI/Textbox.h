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
	__LIB String getFilter( ) const;
	char getPasswordChar( ) const;
	bool getUsePasswordChar( ) const;
	char getLooseFocusKey( ) const;
	bool isInFilter( const char &_Key ) const;
	bool isWriting( ) const;

	void setLooseFocusKey( const char &_Key );
	void setCanWrite( const bool &_Can );
	void setPromptText( const __LIB String &_Text );
	void setPasswordChar( const char &_Char );
	void setUsePasswordChar( const bool &_Use );
	void setMultiline( const bool &_Can );
	void setFilter( const __LIB String &_Filter );
	void addFilterCharacter( const char &_Character );
	
	__LIB Event<void(Component*)> &OnLostFocus( );
	__LIB Event<void(Component*)> &OnGainFocus( );
	__LIB Event<void(Component*, const char&)> &OnCharacterAdded( );
private:
	__MATH Vector2 determineText( __MATH Vector2 &_Pos, __MATH Vector2 &_TextSize );
	__LIB String _prompt, _filter;
	bool _canwrite;
	char _passwordChar, _loose;
	bool _usePasswordChar;
	bool _multiline, _blink;
	__DX uint _lblink;
	__LIB Event<void(Component*)> _OnLostFocus;
	__LIB Event<void(Component*)> _OnGainFocus;
	__LIB Event<void(Component*, const char&)> _OnCharacterAdded;
};


end_UI