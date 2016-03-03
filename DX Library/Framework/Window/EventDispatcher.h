#pragma once

namespace Graphics {
	namespace UI { class Canvas; }
	namespace Renderer { class D9Renderer; }
}
namespace Graphics { class Form; }
#include "../dx.h"
#include "../Event/EventHandler.h"

struct WindowEventParams
{
	POINTS* lp;
	uint key; // WPARAM
	uint msg;
};


class EventDispatcher : public Object
{
private:
	Event<bool, WindowEventParams>	_OnEvent;
	Event<bool>						_OnMouseLeave;
	Event<bool, uint>				_OnKeyDown;
	Event<bool, uint>				_OnKeyUp;
	Event<bool, char>				_OnKeyDownChar;
	Event<bool, Vector2>			_OnMouseMove;
	Event<bool, Vector2>			_OnLeftMouseDown;
	Event<bool, Vector2>			_OnLeftMouseUp;
	Event<bool, Vector2>			_OnRightMouseDown;
	Event<bool, Vector2>			_OnRightMouseUp;
	Event<bool, Vector2>			_OnLeftMouseDoubleClick;
	Event<bool, Vector2>			_OnRightMouseDoubleClick;
	EventDispatcher* _overridden;

public:
	virtual bool PollEvents( );

	virtual Event<bool, WindowEventParams>& OnEvent( );
	virtual Event<bool>& OnMouseLeave( );
	virtual Event<bool, uint>& OnKeyDown( );
	virtual Event<bool, uint>& OnKeyUp( );
	virtual Event<bool, char>& OnKeyDownChar( );
	virtual Event<bool, Vector2>& OnMouseMove( );
	virtual Event<bool, Vector2>& OnLeftMouseDown( );
	virtual Event<bool, Vector2>& OnLeftMouseUp( );
	virtual Event<bool, Vector2>& OnLeftMouseDoubleClick( );
	virtual Event<bool, Vector2>& OnRightMouseDoubleClick( );
	virtual Event<bool, Vector2>& OnRightMouseDown( );
	virtual Event<bool, Vector2>& OnRightMouseUp( );

	void OverrideDispatcher( EventDispatcher *dispatcher );
};

