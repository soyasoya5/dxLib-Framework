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
	StyleManager( const __UI Theme &_Theme, const __UI Style &_Style );

	__UI Theme theme( ) const;
	void theme( const __UI Theme &_Theme );

	__UI Style style( ) const;
	void style( const __UI Style &_Style );

private:
	__UI Theme _theme;
	__UI Style _style;
};


end_UI