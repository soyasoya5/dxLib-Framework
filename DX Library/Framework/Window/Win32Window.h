#pragma once
namespace Graphics { 
	namespace UI { class Canvas; }
	namespace Renderer { class D9Renderer; } }
namespace Graphics { class Form; }
#include <memory>
#include "../Event/EventHandler.h"
#include "../dx.h"
#include "EventDispatcher.h"


struct WindowParams
{
	std::string szTitle, szClass;
	Vector2 pos, size;
	enum : uint
	{
		type_overlay, // Meaning it is an overlay
		type_standard, // Meaning Windowed
	};
	uint type;
	Color transparency_key;
};



class Win32Window : public EventDispatcher
{
private:
	friend class Graphics::Renderer::D9Renderer;
	Event<bool, Vector2>			_OnWindowMove;
	Event<bool, Vector2, HWND>		_OnWindowResize;
	Event<bool>						_OnWindowMinimize;
	Event<bool>						_OnWindowMaximize;
	Event<bool>						_OnWindowClose;

	Graphics::Renderer::D9Renderer* _render;
	Graphics::UI::Canvas* _canvas;
	std::vector<Graphics::Form*> _forms;
	WindowParams _params;
	bool _created, _quit, _min;
	HWND _hwnd;
	uint _prevState;

	Win32Window( const Win32Window& ) = delete;
	Win32Window( Win32Window&& ) = delete;

	bool _success( );
	bool _error( );

public:
	Win32Window( );
	~Win32Window( ) override;
	bool Create( WindowParams* );
	void Quit();
	void Release( ) override;
	LRESULT HandleInput(HWND, uint, WPARAM, LPARAM);
	bool PollEvents( ) override;
public: // Accessors
	bool isMinimized( );
	bool isCreated( );
	WindowParams getParams( ) { return _params; }
	Graphics::Renderer::D9Renderer* getRenderer( ) { return _render; }
	HWND getHWND( ) { return _hwnd; }


	void LaunchForm( Graphics::Form* );
	bool PaintForms( );
	bool TickForms( );
public: // Events

	Event<bool, Vector2>& OnWindowMove( );
	Event<bool, Vector2, HWND>& OnWindowResize( );
	Event<bool>& OnWindowMinimize( );
	Event<bool>& OnWindowMaximize( );
	Event<bool>& OnWindowClose( );

};
