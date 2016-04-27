#pragma once
#include "Component.h"


begin_UI

class Textbox : public Component
{
public:
	Textbox( );

	void Paint( Window* sender, BasePainter *painter );

	void KeyDownChar( Window *sender, KeyDownCharArgs &args ) override;
	void MouseClicked( Window *sender, MouseClickedArgs &args ) override;
	void MouseReleased( Window *sender, MouseReleasedArgs &args ) override;

public:
	bool getCanWrite( ) const;
	bool isMultiline( ) const;
	__LIB String getPromptText( ) const;
	__LIB String getFilter( ) const;
	char getPasswordChar( ) const;
	bool getUsePasswordChar( ) const;
	char getLooseFocusKey( ) const;
	bool isInFilter( const char &key ) const;
	bool isWriting( ) const;

	void setLooseFocusKey( char key );
	void setCanWrite( bool can );
	void setPromptText( String text );
	void setPasswordChar( char character );
	void setUsePasswordChar( bool use );
	void setMultiline( bool can );
	void setFilter( String filter );
	void addFilterCharacter( char character );
	
	Event<void(Component*)> &OnLostFocus( );
	Event<void(Component*)> &OnGainFocus( );
	Event<void(Component*, const char&)> &OnCharacterAdded( );
private:
	__MATH Vector2 determineText( __MATH Vector2 &pos, __MATH Vector2 &textSize );
	String prompt_, filter_;
	bool canwrite_;
	char passwordChar_, loose_;
	bool usePasswordChar_;
	bool multiline_, blink_;
	uint lblink_;
	Event<void(Component*)> _OnLostFocus;
	Event<void(Component*)> _OnGainFocus;
	Event<void(Component*, const char&)> _OnCharacterAdded;
};


end_UI