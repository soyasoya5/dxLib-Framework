#pragma once
#include "Component.h"


begin_UI


class RichLabel : public Component
{
public:
	struct TextContainer
	{
		std::shared_ptr<Texture> texture;
		String text;
		uint color;
		std::shared_ptr<Font> font;
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
	RichLabel();

	virtual void Paint(Window *sender, BasePainter *painter) override;

	void appendText( String text, std::shared_ptr<Font> font, uint color );

	void appendText( String text, std::shared_ptr<Font> font );

	void appendText( String text, uint color );

	void appendText( String text );

	void appendText( std::shared_ptr<Texture> texture );

	void setText( const __LIB String &_Text ) override;

	RichText *textAt( const int &index );

	RichText *textFrom( const std::function<bool(RichText*)> &functor );

	RichText *textFromText( const String& text );

	RichText *textInRegion( const __MATH Region &region );

	void clearText( );

	AsyncKeeper &AquireMutex( );

private:
	void recalculate_text( );

	AsyncKeeper kpr_;
	std::vector<RichText> all_text_;
	std::vector<TextContainer> contrs_;
	bool changed_;

};


end_UI
