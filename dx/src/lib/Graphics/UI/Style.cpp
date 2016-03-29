#include "Style.h"



begin_UI

StyleManager::StyleManager(const __UI Theme & _Theme, const __UI Style & _Style)
	: _theme(_Theme), _style(_Style)
{
}

__UI Theme StyleManager::theme() const
{
	return _theme;
}

void StyleManager::theme(const __UI Theme & _Theme)
{
	_theme = _Theme;
}

__UI Style StyleManager::style() const
{
	return _style;
}

void StyleManager::style(const __UI Style & _Style)
{
	_style = _Style;
}


end_UI