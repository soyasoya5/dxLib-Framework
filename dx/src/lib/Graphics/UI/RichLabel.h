#pragma once
#include "Component.h"


begin_UI


class RichLabel : public Component
{
public:
	struct TextContainer
	{
		__GRAPHICS Texture *texture;
		__LIB String text;
		__DX uint color;
		__GRAPHICS Font *font;
		bool new_line; // If a new line is to be placed after this
		bool is_texture; // If a tab is to be placed after this (8 spaces)
		bool is_selected;
		float orig_tex_y;
	};

	struct RichText
	{
		TextContainer container;
		__MATH Vector2 size; // Size (Pre calculated)
		__MATH Vector2 position; // Position, calculated every time _all_Text is changed.
	};

	
public:
	RichLabel( );

	void Paint( __GRAPHICS Window *_Sender, __GRAPHICS BasePainter *_Painter );

	void appendText( const __LIB String &_Text, __GRAPHICS Font *font, const __DX uint &_Color );

	void appendText( const __LIB String &_Text, __GRAPHICS Font *font );

	void appendText( const __LIB String &_Text, const __DX uint &_Color );

	void appendText( const __LIB String &_Text );
	
	void appendText( __GRAPHICS Texture *_Texture );

	__LIB String getText( ) const override;

	void setText( const __LIB String &_Text ) override;

	RichText *textAt( const int &index );

	RichText *textFrom( const std::function<bool(RichText *text)> &_Functor );

	RichText *textFromText( const __LIB String &_Text );

	RichText *textInRegion( const __MATH Region &_Region );
	
	void clearText( );

private:
	void recalculate_text( );

	__LIB AsyncKeeper _kpr;
	std::vector<RichText> _all_text;
	std::vector<TextContainer> _contrs;
	__LIB String _mtext;
	bool _changed;

};


end_UI

