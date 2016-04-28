#include "Text.h"

begin_GRAPHICS

Text::Text()
	: font_( nullptr ), text_( ), position_( ), max_( { 500, 200 } ), allign_(Top)
{
}

Text::Text(std::shared_ptr<Font> font, const __LIB String & text, const __MATH Vector2 & position, const __MATH Vector2 &clip, const __GRAPHICS TextAlignment &allignment)
	: font_( font ), text_( text ), position_( position ), allign_( allignment ), max_( clip )
{
}

std::shared_ptr<Font> Text::getFont() const
{
	return font_;
}

void Text::setFont(std::shared_ptr<Font> _Font)
{
	font_ = _Font;
}

__GRAPHICS TextAlignment Text::getAlignment() const
{
	return allign_;
}

void Text::setAlignment(const __GRAPHICS TextAlignment & allignment)
{
	allign_ = allignment;
}

const __LIB String &Text::getText() const
{
	return text_;
}

void Text::setText(const __LIB String & text) 
{
	text_ = text;
}

const __MATH Vector2 &Text::getPosition() const
{
	return position_;
}

void Text::setPosition(const __MATH Vector2 & position)
{
	position_ = position;
}

const __MATH Vector2 &Text::getMaxClip() const
{
	return max_;
}

void Text::setMaxClip(const __MATH Vector2 & clip)
{
	max_ = clip;
}


end_GRAPHICS