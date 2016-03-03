#include "EventDispatcher.h"

bool EventDispatcher::PollEvents()
{
	if ( _overridden )
		return _overridden->PollEvents( );
	return true;
}

Event<bool, WindowEventParams>& EventDispatcher::OnEvent()
{
	return _OnEvent;
}

Event<bool>& EventDispatcher::OnMouseLeave()
{
	return _OnMouseLeave;
}

Event<bool, uint>& EventDispatcher::OnKeyDown()
{
	return _OnKeyDown;
}

Event<bool, uint>& EventDispatcher::OnKeyUp()
{
	return _OnKeyUp;
}

Event<bool, char>& EventDispatcher::OnKeyDownChar()
{
	return _OnKeyDownChar;
}


Event<bool, Vector2>& EventDispatcher::OnMouseMove()
{
	return _OnMouseMove;
}

Event<bool, Vector2>& EventDispatcher::OnLeftMouseDown()
{
	return _OnLeftMouseDown;
}

Event<bool, Vector2>& EventDispatcher::OnLeftMouseUp()
{
	return _OnLeftMouseUp;
}

Event<bool, Vector2>& EventDispatcher::OnLeftMouseDoubleClick()
{
	return _OnLeftMouseDoubleClick;
}

Event<bool, Vector2>& EventDispatcher::OnRightMouseDoubleClick()
{
	return _OnRightMouseDoubleClick;
}

Event<bool, Vector2>& EventDispatcher::OnRightMouseDown()
{
	return _OnRightMouseDown;
}

Event<bool, Vector2>& EventDispatcher::OnRightMouseUp()
{
	return _OnRightMouseUp;
}

void EventDispatcher::OverrideDispatcher(EventDispatcher * dispatcher)
{
	_overridden = dispatcher;

	if (_overridden) {
		_overridden->_OnEvent = _OnEvent;
		_overridden->_OnMouseLeave = _OnMouseLeave;
		_overridden->_OnKeyDown = _OnKeyDown;
		_overridden->_OnKeyUp = _OnKeyUp;
		_overridden->_OnKeyDownChar = _OnKeyDownChar;
		_overridden->_OnMouseMove = _OnMouseMove;
		_overridden->_OnLeftMouseDown = _OnLeftMouseDown;
		_overridden->_OnLeftMouseUp = _OnLeftMouseUp;
		_overridden->_OnRightMouseDown = _OnRightMouseDown;
		_overridden->_OnRightMouseUp = _OnRightMouseUp;
		_overridden->_OnLeftMouseDoubleClick = _OnLeftMouseDoubleClick;
		_overridden->_OnRightMouseDoubleClick = _OnRightMouseDoubleClick;
	}
}