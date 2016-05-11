#include "Window.h"
#include "../../string.h"
#include "../../FileIO/path.h"
#include "../../Application.h"
#include "../Painter.h"
#include "../UI/Component.h"


begin_GRAPHICS



LRESULT CALLBACK WndProc( HWND hWnd, ::dx::uint Msg, WPARAM wParam, LPARAM lParam )
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


Window* Window::Create(const  String & Class, const  String & Title, const ::dx::lib::Math::Region & Region, DWORD dwStyle, DWORD dwExStyle)
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
	wc.lpszMenuName = Title.c_str();
	wc.lpszClassName = Class.c_str();
	wc.hInstance = NULL;

	if ( FAILED( RegisterClassExA( &wc ) ) )
		return nullptr;

	auto ptr = std::unique_ptr<Window>( new Window( ) );
	ptr->region_ = Region;
	ptr->hwnd_ = CreateWindowExA( dwExStyle, 
								  Class.c_str( ),
								  Title.c_str( ),
								  dwStyle,
								  Region.position.x,
								  Region.position.y,
								  Region.size.x,
								  Region.size.y,
								  nullptr, nullptr, NULL, ptr.get( ) );

	auto appl = Application::get( );
	appl->RegisterWindow( ptr.get( ) );
	return ptr.release( );
}

Window *Window::Create(Window * parent, const  String & Class, const  String & Title, const ::dx::lib::Math::Region & Region, DWORD dwStyle, DWORD dwExStyle)
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
	wc.lpszMenuName = Title.c_str();
	wc.lpszClassName = Class.c_str();
	wc.hInstance = NULL;

	if ( FAILED( RegisterClassExA( &wc ) ) )
		return nullptr;

	auto ptr = std::unique_ptr<Window>( new Window( ) );
	ptr->region_ = Region;
	ptr->hwnd_ = CreateWindowExA( dwExStyle, 
								  Class.c_str( ),
								  Title.c_str( ),
								  dwStyle,
								  Region.position.x,
								  Region.position.y,
								  Region.size.x,
								  Region.size.y,
								  parent->native_handle( ), 
								  NULL, NULL, ptr.get( ) );
	ptr->parent_ = parent;
	auto appl = Application::get( );
	appl->RegisterWindow( ptr.get( ) );
	return ptr.release( );
}

 Event<void(Window*, KeyDownCharArgs&)>& Window::OnKeyDownChar()
{
	return _OnKeyDownChar;
}

 Event<void(Window*, BasePainter*)>& Window::OnPaint()
{
	return _OnPaint;
}

 Event<void(Window*, MessageDataArgs&)>& Window::OnHandleMessage()
{
	return _OnHandleMessage;
}

 Event<void(Window*)>& Window::OnTick()
{
	return _OnTick;
}

Window::Window( )
	: hwnd_( nullptr )
{
	
}

Window::~Window( )
{
}

bool Window::ClientToScreen(::dx::lib::Math::Vector2 & point)
{
	return ::ClientToScreen( this->hwnd_, (LPPOINT)&point );
}

bool Window::ScreenToClient(::dx::lib::Math::Vector2 & point)
{
	return ::ScreenToClient( this->hwnd_, (LPPOINT)&point );
}

 String Window::getTitle()
{
	char _Title[255];
	::GetWindowTextA( this->hwnd_, _Title, 255 );
	return _Title;
}

void Window::setTitle(const  String & title)
{
	::SetWindowTextA( hwnd_, title.c_str( ) );
}

 String Window::getClass()
{
	thread_local char _Class[255];
	::RealGetWindowClassA( this->hwnd_, _Class, 255 );
	return _Class;
}

bool Window::Hide()
{
	return ::ShowWindow( hwnd_, SW_HIDE );
}

bool Window::Show()
{
	return ::ShowWindow( hwnd_, SW_SHOW );
}

bool Window::BringToTop()
{
	return ::BringWindowToTop( hwnd_ );
}


bool Window::Minimize()
{
	return ::ShowWindow( hwnd_, SW_MINIMIZE );
}

bool Window::Maximize( ) 
{
	return ::ShowWindow( hwnd_, SW_MAXIMIZE );
}

bool Window::Restore( )
{
	return ::ShowWindow( hwnd_, SW_RESTORE );
}

bool Window::ForcePaint()
{
	return ::SendMessageA( hwnd_, WM_PAINT, 0, 0 );
}

bool Window::Enable()
{
	return ::EnableWindow( hwnd_, true );
}

bool Window::Disable()
{
	return ::EnableWindow( hwnd_, false );
}

bool Window::LoadIcon(const ::dx::lib::FileIO::Path &path)
{
	DWORD type = path.extension_is(".ico") ? IMAGE_ICON : IMAGE_BITMAP;
	auto icon = LoadImageA( NULL,             
				 		    path,
				 		    type,       
				 		    32,                
				 			32,                
			  	 		    LR_LOADFROMFILE );
	return SUCCEEDED( ::SendMessageA( hwnd_, WM_SETICON, ICON_BIG, (LPARAM)icon ) );
}

bool Window::LoadIconSm(const ::dx::lib::FileIO::Path &path )
{
	DWORD type = path.extension_is(".ico") ? IMAGE_ICON : IMAGE_BITMAP;
	auto icon = LoadImageA( NULL,             
				 		    path,
				 		    type,       
				 		    16,                
				 			16,                
			  	 		    LR_LOADFROMFILE );
	return SUCCEEDED( ::SendMessageA( hwnd_, WM_SETICON, ICON_SMALL, (LPARAM)icon ) );
}


::dx::lib::Graphics::Window * Window::getParent()
{
	return parent_;
}

::dx::lib::Graphics::BasePainter * Window::getPainter()
{
	return painter_;
}

void Window::SpecializePaint(const PaintStyle_t & style)
{
	style_ = style;
}

Window::PaintStyle_t Window::PaintStyle() const
{
	return style_;
}

void Window::setPainter(::dx::lib::Graphics::BasePainter * painter, const bool &delete_old)
{
	if ( delete_old && painter_ )
		delete painter_;
	painter_ = painter;
}

bool Window::has_painter() const
{
	return painter_ != nullptr;
}

float Window::Width() const
{
	return this->region_.size.x;
}

float Window::Height() const
{
	return this->region_.size.y;
}

bool Window::isCtrlHeld() const
{
	return keys_[dx::key_control];
}

bool Window::isShiftHeld() const
{
	return keys_[dx::key_leftShift] || keys_[dx::key_shift];
}

bool Window::isKeyDown(uint key) const
{
	return keys_[key];
}

HWND Window::native_handle()
{
	return hwnd_;
}

void Window::Close()
{
	if ( hwnd_ )
	{
		::DestroyWindow( hwnd_ );
		hwnd_ = nullptr;
		OnWindowClosed( ).Invoke( this );
	}
}

Window::Task& Window::addTask( const time_point &when, const std::function<void(Window*)> &functor )
{
	tasks_.emplace_back( functor, when );
	return tasks_.back( );
}

LRESULT Window::HandleInput(HWND hWnd, ::dx::uint Msg, WPARAM wParam, LPARAM lParam)
{
	MessageDataArgs data;
	data.handled = false;
	data.Msg = Msg;
	data.wParam = wParam;
	data.lParam = lParam;
	OnHandleMessage( ).Invoke( this, data );

	if ( data.handled )
		return 0;

	POINTS p = MAKEPOINTS(lParam);
	
	switch (Msg)
	{
	case WM_PAINT:
	{
		if ( PaintStyle( ) == OnEvent_t && painter_ ) {
			painter_->BeginPaint( );
			this->OnPaint( ).Invoke( this, painter_ );
			painter_->PresentPaint( );
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
		keys_[args.key_code] = true;
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnKeyDown( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );

		return 0;
	}
		break;
	case WM_KEYUP:
	{
		KeyUpArgs args;
		args.handled = false;
		args.key_code = static_cast<uint>( wParam );
		keys_[args.key_code] = false;
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnKeyUp( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_MOUSEMOVE:
	{
		MouseMovedArgs args;
		args.handled = false;
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseMoved( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
	case WM_MOVE:
	{
		region_.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		WindowMovedArgs args;
		args.handled = false;
		args.region = region_;
		OnWindowMoved( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_SIZE:
	{
		region_.size = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		WindowResizeArgs args;
		args.handled = false;
		args.region = region_;

		if ( wParam == SIZE_MINIMIZED ) {
			OnWindowMinimize( ).Invoke( this );
			return 0;
		}
		else if ( wParam == SIZE_MAXIMIZED )
			OnWindowMaximize( ).Invoke( this );
		OnWindowRestored( ).Invoke( this );
		OnWindowResize( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_LBUTTONDOWN:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 1;
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseClicked( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_LBUTTONUP:
	{
		MouseReleasedArgs args;
		args.handled = false;
		args.key = 1;
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseReleased( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_RBUTTONDOWN:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 2;
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseClicked( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_RBUTTONUP:
	{
		MouseReleasedArgs args;
		args.handled = false;
		args.key = 2;
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseReleased( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_LBUTTONDBLCLK:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 1; 
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseDoubleClicked( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_RBUTTONDBLCLK:
	{
		MouseClickedArgs args;
		args.handled = false;
		args.key = 2;
		args.position = ::dx::lib::Math::Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) };
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnMouseDoubleClicked( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_MOUSEWHEEL:
	{
		ScrollArgs args;
		args.handled = false;
		args.delta = GET_WHEEL_DELTA_WPARAM( wParam );
		args.direction = args.delta > 0 ? ScrollArgs::Up : ScrollArgs::Down;
		args.ctrl = keys_[::dx::key_control];
		args.shift = keys_[::dx::key_leftShift] || keys_[::dx::key_shift];
		OnScroll( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
		return 0;
	}
		break;
	case WM_CHAR:
	{
		KeyDownCharArgs args;
		args.handled = false;
		args.key_char = static_cast<char>( wParam );
		OnKeyDownChar( ).Invoke( this, args );
		if ( args.handled )
			ForcePaint( );
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
	OnTick( ).Invoke( this );
	auto now = clock::now( );
	for ( auto it = tasks_.begin( ), end = tasks_.end( ); 
		  it < end; 
		  ++it )
	{
		if ( it->call_task_if_time( now, this ) )
		{
			tasks_.erase( it );
			break;
		}
		std::this_thread::sleep_for( std::chrono::nanoseconds( 500 ) );
	}
}

bool Window::PollEvents()
{
	static MSG msg{ 0 };
	if ( !hwnd_ )
		return false;

	if ( PeekMessageA( &msg, hwnd_, NULL, NULL, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessageA( &msg );
	}

	return true;
}

void Window::HandleComponent(::dx::lib::Graphics::UI::Component * _Comp)
{
	this->OnMouseMoved( ) += EventHandler<MouseMovedSig>( to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::MouseMoved, _Comp ) );
	this->OnMouseClicked() += EventHandler<MouseClickedSig>( to_string(_Comp->getUIID()) + "_component", BIND_METHOD_2(&UI::Component::MouseClicked , _Comp));
	this->OnMouseReleased( ) += EventHandler<MouseReleasedSig>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::MouseReleased, _Comp ) );
	this->OnScroll( ) += EventHandler<ScrollSig>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::MouseScrolled, _Comp ) );
	this->OnKeyDown( ) += EventHandler<KeyDownSig>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::KeyDown, _Comp ) );
	this->OnKeyUp( ) += EventHandler<KeyUpSig>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::KeyUp, _Comp ) );
	this->OnKeyDownChar( ) += EventHandler<KeyDownCharSig>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::KeyDownChar, _Comp ) );
	this->OnMouseDoubleClicked( ) += EventHandler<MouseClickedSig>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::MouseDoubleClicked, _Comp ) );
	this->OnPaint( ) += EventHandler<void(Window*, BasePainter*)>(  to_string( _Comp->getUIID( ) ) + "_component", BIND_METHOD_2( &UI::Component::Paint, _Comp ) );
}

void Window::StopHandlingComponent(::dx::lib::Graphics::UI::Component * _Comp)
{
	this->OnMouseMoved( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnMouseClicked( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnMouseReleased( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnScroll( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnKeyDown( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnKeyUp( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnKeyDownChar( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnMouseDoubleClicked( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
	this->OnPaint( ) -=  to_string( _Comp->getUIID( ) ) + "_component";
}

Event<void(Window*, WindowMovedArgs&)>& Window::OnWindowMoved()
{
	return _OnWindowMoved;
}

Event<void(Window*, WindowResizeArgs&)>& Window::OnWindowResize()
{
	return _OnWindowResize;
}

Event<void(Window*)>& Window::OnWindowMaximize()
{
	return _OnWindowMaximize;
}

Event<void(Window*)>& Window::OnWindowRestored()
{
	return _OnWindowRestored;
}

 Event<void(Window*)>& Window::OnWindowMinimize()
{
	return _OnWindowMinimize;
}

 Event<void(Window*, WindowClosingArgs&)>& Window::OnWindowClosing()
{
	return _OnWindowClosing;
}

 Event<void(Window*)>& Window::OnWindowClosed()
{
	return _OnWindowClosed;
}

 Event<void(Window*, MouseMovedArgs&)>& Window::OnMouseMoved()
{
	return _OnMouseMoved;
}

 Event<void(Window*, MouseClickedArgs&)>& Window::OnMouseClicked()
{
	return _OnMouseClicked;
}

 Event<void(Window*, MouseReleasedArgs&)>& Window::OnMouseReleased()
{
	return _OnMouseReleased;
}

 Event<void(Window*, MouseClickedArgs&)>& Window::OnMouseDoubleClicked()
{
	return _OnMouseDoubleClicked;
}

 Event<void(Window*, ScrollArgs&)>& Window::OnScroll()
{
	return _OnScroll;
}

 Event<void(Window*, KeyDownArgs&)>& Window::OnKeyDown()
{
	return _OnKeyDown;
}

 Event<void(Window*, KeyUpArgs&)>& Window::OnKeyUp()
{
	return _OnKeyUp;
}


end_GRAPHICS


