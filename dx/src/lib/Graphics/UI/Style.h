#pragma once
#include "lib.h"

begin_UI

enum Theme
{
	Light,
	Dark,
};

enum Style
{
	Blue,
	Green,
	Lime,
	Orange,
	Red,
};


class StyleManager
{
public:
	StyleManager( ) = default;

	__UI Theme theme( ) const;
	void theme( const __UI Theme &_Theme );

	__UI Style style( ) const;
	void style( const __UI Style &_Style );

private:
	__UI Theme _theme;
	__UI Style _style;
};


end_UI