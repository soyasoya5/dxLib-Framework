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
	StyleManager( const __UI Theme &theme, const __UI Style &style );

	__UI Theme theme( ) const;
	void theme( const __UI Theme &theme );

	__UI Style style( ) const;
	void style( const __UI Style &style );

private:
	__UI Theme theme_;
	__UI Style style_;
};


end_UI