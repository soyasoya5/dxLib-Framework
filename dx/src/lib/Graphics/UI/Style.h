#pragma once
#include "lib.h"
#include "../../../dx.h"

begin_UI

enum Theme
{
	Light,
	Dark,
};

enum Style
{
	Blue = 0xFF009DDE,
	Green = Colors::Green,
	Lime = Colors::Lime,
	Orange = Colors::Orange,
	Red = Colors::MediumVioletRed,
};


class StyleManager
{
public:
	StyleManager( ) = default;
	StyleManager( const ::dx::lib::Graphics::UI::Theme &theme, const ::dx::lib::Graphics::UI::Style &style );

	::dx::lib::Graphics::UI::Theme theme( ) const;
	void theme( const ::dx::lib::Graphics::UI::Theme &theme );

	::dx::lib::Graphics::UI::Style style( ) const;
	void style( const ::dx::lib::Graphics::UI::Style &style );

private:
	::dx::lib::Graphics::UI::Theme theme_;
	::dx::lib::Graphics::UI::Style style_;
};


end_UI