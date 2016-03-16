#include "Window.h"
#include "../../string.h"
#include "../../FileIO/path.h"
#include "../../Application.h"
#include "../Painter.h"


begin_GRAPHICS



LRESULT CALLBACK WndProc( HWND hWnd, __DX uint Msg, WPARAM wParam, LPARAM lParam )
{
	switch (Msg)
	{
	case WM_NCCREATE:
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		break;
	}

	auto window = (Window*)GetWindowLongPtr( hWnd, GWL_USERDATA );
	if ( !window )
		return DefWindowProcA( hWnd, Msg, wParam, lParam );
	return window->HandleInput( hWnd, Msg, wParam, lParam );
}


Window * Window::Create(const __LIB String & _Class, const __LIB String & _Title, const __MATH Region & _Region, DWORD dwStyle, DWORD dwExStyle)
{

	WNDCLASSEX wc;
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = _Title.c_str();
	wc.lpszClassName = _Class.c_str();
	wc.hInstance = NULL;

	if ( FAILED( RegisterClassExA( &wc ) ) )
		return nullptr;

	Window* ptr = new Window( );
	ptr->_region = _Region;
	ptr->_hwnd = CreateWindowExA( dwExStyle, 
								  _Class.c_str( ),
								  _Title.c_str( ),
								  dwStyle,
								  _Region.position.x,
								  _Region.position.y,
								  _Region.size.x,
								  _Region.size.y,
								  NULL, NULL, NULL, ptr );

	auto appl = Application::get( );
	appl->RegisterWindow( ptr );
	return ptr;
}

Window * Window::Create(Window * _Parent, const __LIB String & _Class, const __LIB String & _Title, const __MATH Region & _Region, DWORD dwStyle, DWORD dwExStyle)
{
	WNDCLASSEX wc;
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIconA(NULL, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = _Title.c_str();
	wc.lpszClassName = _Class.c_str();
	wc.hInstance = NULL;

	if ( FAILED( RegisterClassExA( &wc ) ) )
		return nullptr;

	Window* ptr = new Window( );
	ptr->_region = _Region;
	ptr->_hwnd = CreateWindowExA( dwExStyle, 
								  _Class.c_str( ),
								  _Title.c_str( ),
								  dwStyle,
								  _Region.position.x,
								  _Region.position.y,
								  _Region.size.x,
								  _Region.size.y,
								  _Parent->native_handle( ), 
								  NULL, NULL, ptr );
	ptr->_parent = _Parent;
	auto appl = Application::get( );
	appl->RegisterWindow( ptr );
	return ptr;
}

__LIB Event<void(Window*, KeyDownCharArgs&)>& Window::OnKeyDownChar()
{
	return _OnKeyDownChar;
}

__LIB Event<void(Window*, BasePainter*)>& Window::OnPaint()
{
	return _OnPaint;
}

Window::Window( )
	: _hwnd( nullptr )
{
	
}

void Window::push_task(Task * _Task)
{
	AsyncGuard guard{ _ak_tasks };
	_tasks.push_back( _Task );
}

void Window::remove_task(std::vector<Task*>::iterator _Where)
{
	AsyncGuard guard{ _ak_tasks };
	_tasks.erase( _Where );
}

Window::~Window( )
{	// Force the closing of window, no matter what -
	this->OnWindowClosing( ).getF( ).clear( );
	Close( );
}

bool Window::ClientToScreen(__MATH Vector2 & _Point)
{
	return ::ClientToScreen( this->_hwnd, (LPPOINT)&_Point );
}

bool Window::ScreenToClient(__MATH Vector2 & _Point)
{
	return ::ScreenToClient( this->_hwnd, (LPPOINT)&_Point );
}

__LIB String Window::getTitle()
{
	char _Title[255];
	::GetWindowTextA( this->_hwnd, _Title, 255 );
	return _Title;
}

void Window::setTitle(const __LIB String & _Title)
{
	::SetWindowTextA( _hwnd, _Title.c_str( ) );
}

__LIB String Window::getClass()
{
	char _Class[255];
	::RealGetWindowClassA( this->_hwnd, _Class, 255 );
	return _Class;
}

bool Window::Hide()
{
	return ::ShowWindow( _hwnd, SW_HIDE );
}

bool Window::Show()
{
	return ::ShowWindow( _hwnd, SW_SHOW );
}

bool Window::BringToTop()
{
	return ::BringWindowToTop( _hwnd );
}


bool Window::Minimize()
{
	return ::ShowWindow( _hwnd, SW_MINIMIZE );
}

bool Window::Maximize( ) 
{
	return ::ShowWindow( _hwnd, SW_MAXIMIZE );
}

bool Window::Restore( )
{
	return ::ShowWindow( _hwnd, SW_RESTORE );
}

bool Window::Enable()
{
	return ::EnableWindow( _hwnd, true );
}

bool Window::Disable()
{
	return ::EnableWindow( _hwnd, false );
}

bool Window::LoadIcon(const __FILEIO Path &_Path)
{
	DWORD type = _Path.extension_is(".ico") ? IMAGE_ICON : IMAGE_BITMAP;
	auto icon = LoadImageA( NULL,             
				 		    _Path,
				 		    type,       
				 		    32,                
				 			32,                
			  	 		    LR_LOADFROMFILE );
	return SUCCEEDED( ::SendMessageA( _hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon ) );
}

bool Window::LoadIconSm(const __FILEIO Path &_Path)
{
	DWORD type = _Path.extension_is(".ico") ? IMAGE_ICON : IMAGE_BITMAP;
	auto icon = LoadImageA( NULL,             
				 		    _Path,
				 		    type,       
				 		    16,                
				 			16,                
			  	 		    LR_LOADFROMFILE );
	return SUCCEEDED( ::SendMessageA( _hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon ) );
}


__GRAPHICS Window * Window::getParent()
{
	return _parent;
}

__GRAPHICS BasePainter * Window::getPainter()
{
	return _painter;
}

void Window::SpecializePaint(const PaintStyle_t & _Style)
{
	_style = _Style;
}

Window::PaintStyle_t Window::PaintStyle() const
{
	return _style;
}

void Window::setPainter(__GRAPHICS BasePainter * _Painter, const bool &_Delete_Old)
{
	if ( _Delete_Old && _painter )
		delete _painter;
	_painter = _Painter;
}

bool Window::has_painter() const
{
	return _painter;
}

float Window::Width() const
{
	return this->_region.size.x;
}

float Window::Height() const
{
	return this->_region.size.y;
}

HWND Window::native_handle()
{
	return _hwnd;
}

void Window::Close()
{
	::DestroyWindow( _hwnd );
	_hwnd = nullptr;
}

__LIB TimedTask<void(Window*)>& Window::addTask( const time_point &_When, const std::function<void(Window*)> &_Function )
{
	auto task = new __LIB TimedTask<void(Window*)>( _Function, _When );
	std::async( BIND_METHOD_1( &Window::push_task, this ), task );
	return *task;
}

LRESULT Window::HandleInput(HWND hWnd, __DX uint Msg, WPARAM wParam, LPARAM lParam)
{
	// Handle taskss
	//HandleTasks( );

	POINTS p = MAKEPOINTS(lParam);
	
	switch (Msg)
	{
	case WM_PAINT:
	{
		if ( PaintStyle( ) == OnEvent && _painter ) {
			_painter->BeginPaint( );
			this->OnPaint( ).Invoke( this, _painter );
			_painter->PresentPaint( );
		}
	}
	break;
	case WM_QUIT:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
	{
		KeyDownArgs args;
		args.handled = false;
		args.key_code = static_cast<uint>( wParam );
		OnKeyDown( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_KEYUP:
	{
		KeyUpArgs args;
		args.handled = false;
		args.key_code = static_cast<uint>( wParam );
		OnKeyUp( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_MOUSEMOVE:
	{
		MouseMovedArgs args;
		args.handled = false;
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseMoved( ).Invoke( this, args );
		return 0;
	}
	case WM_MOVE:
	{
		_region.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		WindowMovedArgs args;
		args.handled = false;
		args.region = _region;
		OnWindowMoved( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_SIZE:
	{
		if ( wParam == SIZE_MINIMIZED )
			OnWindowMinimize( ).Invoke( this );
		else if ( wParam == SIZE_RESTORED )
			OnWindowRestored( ).Invoke( this );
		else
		{
			_region.size = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
			WindowResizeArgs args;
			args.handled = false;
			args.region = _region;
			OnWindowResize( ).Invoke( this, args );
			return 0;
		}
	}
		break;
	case WM_LBUTTONDOWN:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 1;
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseClicked( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_LBUTTONUP:
	{
		MouseReleasedArgs args;
		args.handled = false;
		args.key = 1;
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseReleased( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_RBUTTONDOWN:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 2;
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseClicked( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_RBUTTONUP:
	{
		MouseReleasedArgs args;
		args.handled = false;
		args.key = 2;
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseReleased( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_LBUTTONDBLCLK:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 1; 
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseDoubleClicked( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_RBUTTONDBLCLK:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 2;
		args.position = __MATH Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		OnMouseDoubleClicked( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_CHAR:
	{
		KeyDownCharArgs args;
		args.handled = false;
		args.key_char = static_cast<char>( wParam );
		OnKeyDownChar( ).Invoke( this, args );
		return 0;
	}
		break;
	case WM_CLOSE:
	{
		WindowClosingArgs args;
		args.handled = false;
		args.ShouldClose = true;
		OnWindowClosing( ).Invoke( this, args );
		if ( args.ShouldClose )
			Close( );
		return 0;
	}
	case WM_DESTROY:
		OnWindowClosed( ).Invoke( this );
		return 0;
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void Window::HandleTasks()
{
	auto now = clock::now( );
	for ( auto it = _tasks.begin( ); it < _tasks.end( ); ++it )
	{
		auto&x = *it;
		if ( x->call_task_if_time( now, this ) )
		{
			remove_task( it );
			delete x;
			break;
		}
		std::this_thread::sleep_for( std::chrono::nanoseconds( 500 ) );
	}
}

bool Window::PollEvents()
{
	static MSG msg{ 0 };
	if ( !_hwnd )
		return false;

	if ( PeekMessageA( &msg, _hwnd, NULL, NULL, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessageA( &msg );
	}

	return true;
}

__LIB Event<void(Window*, WindowMovedArgs&)>& Window::OnWindowMoved()
{
	return _OnWindowMoved;
}

__LIB Event<void(Window*, WindowResizeArgs&)>& Window::OnWindowResize()
{
	return _OnWindowResize;
}

__LIB Event<void(Window*)>& Window::OnWindowMaximize()
{
	return _OnWindowMaximize;
}

__LIB Event<void(Window*)>& Window::OnWindowRestored()
{
	return _OnWindowRestored;
}

__LIB Event<void(Window*)>& Window::OnWindowMinimize()
{
	return _OnWindowMinimize;
}

__LIB Event<void(Window*, WindowClosingArgs&)>& Window::OnWindowClosing()
{
	return _OnWindowClosing;
}

__LIB Event<void(Window*)>& Window::OnWindowClosed()
{
	return _OnWindowClosed;
}

__LIB Event<void(Window*, MouseMovedArgs&)>& Window::OnMouseMoved()
{
	return _OnMouseMoved;
}

__LIB Event<void(Window*, MouseClickedArgs&)>& Window::OnMouseClicked()
{
	return _OnMouseClicked;
}

__LIB Event<void(Window*, MouseReleasedArgs&)>& Window::OnMouseReleased()
{
	return _OnMouseReleased;
}

__LIB Event<void(Window*, MouseClickedArgs&)>& Window::OnMouseDoubleClicked()
{
	return _OnMouseDoubleClicked;
}

__LIB Event<void(Window*, KeyDownArgs&)>& Window::OnKeyDown()
{
	return _OnKeyDown;
}

__LIB Event<void(Window*, KeyUpArgs&)>& Window::OnKeyUp()
{
	return _OnKeyUp;
}


end_GRAPHICS


