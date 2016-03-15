#pragma once
#include "../lib.h"
#include "../../../dx.h"
#include "../../Math/Region.h"
#include "../../Task.h"
#include "../../async.h"

begin_GRAPHICS
#undef LoadIcon



/*******************************
	Window event arguments
 *******************************/

class WindowMovedArgs : public EventArgs
{
public:
	__MATH Region region;
};
using WindowResizeArgs = WindowMovedArgs;

class WindowClosingArgs : public EventArgs
{
public:
	bool ShouldClose;
};

class KeyDownArgs : public EventArgs
{
public:
	__DX uint key_code;
};

class KeyUpArgs : public EventArgs
{
public:
	__DX uint key_code;
};

class KeyDownCharArgs : public EventArgs
{
public:
	char key_char;
};

class MouseMovedArgs : public EventArgs
{
public:
	__MATH Vector2 position;
};

class MouseClickedArgs : public EventArgs
{
public:
	__DX uint key;
	__MATH Vector2 position;
};

class MouseReleasedArgs : public EventArgs
{
public:
	__DX uint key;
	__MATH Vector2 position;
};

class Window
{
public:
	typedef std::chrono::system_clock clock;
	typedef std::chrono::time_point<clock> time_point;


	static Window* Create( const __LIB String &_Class, 
						   const __LIB String &_Title,
						   const __MATH Region &_Region,
						   DWORD dwStyle = WS_OVERLAPPEDWINDOW,
						   DWORD dwExStyle = 0L );


public:
	~Window( );

public:
		// Wrappers

	///<summary>
	///	Retrieves the tile of this window.
	///</summary>
	__LIB String getTitle( );

	///<summary>
	///	Sets the title of this window.
	///</summary>
	void setTitle( const __LIB String &_Title );

	///<summary>
	///	Retrieves the class name of a window.
	///</summary>
	__LIB String getClass( );
	
	///<summary>
	///	Converts the client-area coordinates of a specified point to screen coordinates
	///</summary>
	bool ClientToScreen( __MATH Vector2 &_PointOut );
	
	///<summary>
	/// Converts the screen coordinates of a specified point on the screen to client-area coordinates
	///</summary>
	bool ScreenToClient( __MATH Vector2 &_PointOut );

	///<summary>
	///	Hides the widnow.
	///</summary>
	bool HideWindow( );

	///<summary>
	///	Shows the window.
	///</summary>
	bool ShowWindow( );

	///<summary>
	///	Brings the window to the top.
	///</summary>
	bool BringToTop( );

	///<summary>
	///	Minimizes the window to the taskbar.
	///</summary>
	bool Minimize( );

	///<summary>
	///	Maximizes the window.
	///</summary>
	bool Maximize( );

	///<summary>
	///	Restores the windows state.
	///</summary>
	bool Restore( );

	///<summary>
	/// Load the icon showed in taskbar (32x32). 
	/// Supports bitmaps and ico's.
	///</summary>
	bool LoadIcon( const __LIB String &_Path );

	///<summary>
	/// Load the icon showed in the top left corner of the window.
	/// Supports bitmaps and ico's.
	///</summary>
	bool LoadIconSm( const __LIB String &_Path );

	///<summary>
	/// Forces a closing of a window, this does NOT trigger OnWindowClosing event,
	/// this will DESTROY the window and call respective events.
	///</summary>
	void Close( );

	HWND native_handle( );

public: // Others
	__LIB TimedTask<void(Window*)> &addTask( const time_point &_When, const std::function<void(Window*)> &_Function );

	///<summary>
	///	This windows internal event loop, called from the respective WindowProc
	/// you can call this function yourself to inject messages into the loop
	///</summary>
	LRESULT HandleInput( HWND hWnd, __DX uint Msg, WPARAM wParam, LPARAM lParam );

	///<summary>
	///	Handle all tasks that has been put on the window.
	///</summary>
	void HandleTasks( );

	///<summary>
	/// Polls all windows events and fires WindowProc.
	///</summary>
	bool PollEvents( );
public:
		// Events

	///</summary>
	///	Called when the window is moved.
	///<summary>
	__LIB Event<void(Window*, WindowMovedArgs&)>& OnWindowMoved( );

	///<summary>
	///	Called when the window is resized
	///</summary>
	__LIB Event<void(Window*, WindowResizeArgs&)>& OnWindowResize( );
	
	///<summary>
	///	Called when the window is maximized
	///</summary>
	__LIB Event<void(Window*)>& OnWindowMaximize( );

	///<sumamry>
	/// Called when the window is restored from its minimized or maximized state.
	///</summary>
	__LIB Event<void(Window*)>& OnWindowRestored( );

	///<summary>
	///	Called when the window is minimized to the taskbar
	///</summary>
	__LIB Event<void(Window*)>& OnWindowMinimize( );

	///<summary>
	/// Called when the window is about to close, you can cancel
	/// the closing by setting WindowCloseArgs::ShouldClose to false.
	///</summary>
	__LIB Event<void(Window*, WindowClosingArgs&)>& OnWindowClosing( );

	///</summary>
	/// Called when the window is closed.
	///<summary>
	__LIB Event<void(Window*)>& OnWindowClosed( ); 

	///<summary>
	/// Called when the cursor moves
	///</summary>
	__LIB Event<void(Window*, MouseMovedArgs&)>& OnMouseMoved( );

	///<summary>
	///	Called when a mouse button is clicked once.
	///</summary>
	__LIB Event<void(Window*, MouseClickedArgs&)>& OnMouseClicked( );

	///<summary>
	///	Called when a mouse button is released from its previously clicked state.
	///</summary>
	__LIB Event<void(Window*, MouseReleasedArgs&)>& OnMouseReleased( );

	///<summary>
	///	Called when a mouse button is double clicked
	///</summary>
	__LIB Event<void(Window*, MouseClickedArgs&)>& OnMouseDoubleClicked( );

	///<summary>
	///	Called once for the first key stroke, then continuously called with a delay whilst held.
	///</summary>
	__LIB Event<void(Window*, KeyDownArgs&)>& OnKeyDown( );

	///<summary>
	///	Called when a key is released from its previously clicked state.
	///</summary>
	__LIB Event<void(Window*, KeyUpArgs&)>& OnKeyUp( );

	///<summary>
	/// Called after KeyDown has been called with the respective character represenation of the key pressed.
	///</summary>
	__LIB Event<void(Window*, KeyDownCharArgs&)>& OnKeyDownChar( );


private:
	using Task = __LIB TimedTask<void(Window*)>;

	Window( );
	std::vector<__LIB TimedTask<void(Window*)>*> _tasks;
	HWND _hwnd;
	__MATH Region _region;
	
private:
	__LIB Event<void(Window*, WindowMovedArgs&)> _OnWindowMoved;
	__LIB Event<void(Window*, WindowResizeArgs&)> _OnWindowResize;
	__LIB Event<void(Window*)> _OnWindowMaximize, _OnWindowRestored, _OnWindowMinimize, _OnWindowClosed;
	__LIB Event<void(Window*, WindowClosingArgs&)> _OnWindowClosing;
	__LIB Event<void(Window*, MouseMovedArgs&)> _OnMouseMoved;
	__LIB Event<void(Window*, MouseClickedArgs&)> _OnMouseClicked;
	__LIB Event<void(Window*, MouseReleasedArgs&)> _OnMouseReleased;
	__LIB Event<void(Window*, MouseClickedArgs&)> _OnMouseDoubleClicked;
	__LIB Event<void(Window*, KeyDownArgs&)> _OnKeyDown;
	__LIB Event<void(Window*, KeyUpArgs&)> _OnKeyUp;
	__LIB Event<void(Window*, KeyDownCharArgs&)> _OnKeyDownChar;

private:
	__LIB AsyncKeeper _ak_tasks;
	void push_task( Task *_Task );
	void remove_task( std::vector<Task*>::iterator _Where );
};




end_GRAPHICS