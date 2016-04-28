#include "Style.h"



begin_UI

StyleManager::StyleManager(const ::dx::lib::Graphics::UI::Theme & theme, const ::dx::lib::Graphics::UI::Style & style)
	: theme_( theme ), style_( style )
{
}

::dx::lib::Graphics::UI::Theme StyleManager::theme() const
{
	return theme_;
}

void StyleManager::theme(const ::dx::lib::Graphics::UI::Theme & theme)
{
	theme_ = theme;
}

::dx::lib::Graphics::UI::Style StyleManager::style() const
{
	return style_;
}

void StyleManager::style(const ::dx::lib::Graphics::UI::Style & style)
{
	style_ = style;
}


end_UI