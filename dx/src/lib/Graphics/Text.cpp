#include "Text.h"

begin_GRAPHICS

Text::Text()
	: font_( nullptr ), text_( ), position_( ), max_( { 500, 200 } ), allign_(Top)
{
}

Text::Text(std::shared_ptr<Font> font, const ::dx::lib::String & text, const ::dx::lib::Math::Vector2 & position, const ::dx::lib::Math::Vector2 &clip, const ::dx::lib::Graphics::TextAlignment &allignment)
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

::dx::lib::Graphics::TextAlignment Text::getAlignment() const
{
	return allign_;
}

void Text::setAlignment(const ::dx::lib::Graphics::TextAlignment & allignment)
{
	allign_ = allignment;
}

const ::dx::lib::String &Text::getText() const
{
	return text_;
}

void Text::setText(const ::dx::lib::String & text) 
{
	text_ = text;
}

const ::dx::lib::Math::Vector2 &Text::getPosition() const
{
	return position_;
}

void Text::setPosition(const ::dx::lib::Math::Vector2 & position)
{
	position_ = position;
}

const ::dx::lib::Math::Vector2 &Text::getMaxClip() const
{
	return max_;
}

void Text::setMaxClip(const ::dx::lib::Math::Vector2 & clip)
{
	max_ = clip;
}


end_GRAPHICS