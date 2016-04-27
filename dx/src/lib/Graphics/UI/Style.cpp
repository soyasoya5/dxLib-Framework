#include "Style.h"



begin_UI

StyleManager::StyleManager(const __UI Theme & theme, const __UI Style & style)
	: theme_( theme ), style_( style )
{
}

__UI Theme StyleManager::theme() const
{
	return theme_;
}

void StyleManager::theme(const __UI Theme & theme)
{
	theme_ = theme;
}

__UI Style StyleManager::style() const
{
	return style_;
}

void StyleManager::style(const __UI Style & style)
{
	style_ = style;
}


end_UI