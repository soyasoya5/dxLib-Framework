#include "Application.h"
#include "Graphics\Window\Window.h"

begin_LIB
static Application* _Application = nullptr;
int Application::_ilasterr = 0;

Application::Application()
	: _windows( )
{
}

Application * Application::Create()
{
	if ( Application::isCreated( ) )
		return Application::get( );
	auto appl = new Application( );
	
	// Initalize stuff
	_Application = appl;

	return appl;
}

bool Application::isCreated()
{
	return _Application != nullptr;
}

Application * Application::get()
{
	return _Application;
}

void Application::setLastError(const int & _Errc)
{
	_ilasterr = _Errc;
}

int Application::getLastError()
{
	return _ilasterr;
}

int Application::run()
{
	_running = true;
	while( _running )
	{
		OnTick( ).Invoke( this );
		for ( auto&x : _windows )
		{
			x->PollEvents( );
			x->HandleTasks( );
			if ( x->PaintStyle( ) == __GRAPHICS Window::OnTick_t && x->has_painter( ) ) {
				auto painter = x->getPainter( );
				painter->BeginPaint( );
				x->OnPaint( ).Invoke( x, painter );
				painter->PresentPaint( );
			}
			std::this_thread::sleep_for( std::chrono::nanoseconds( 500 ) );
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( _tick ) );
	}

	for ( auto&x : _windows )
		delete x;

	return getLastError( );
}

void Application::exit()
{
	_running = false;
}

void Application::RegisterWindow(__GRAPHICS Window * _Window)
{
	_windows.push_back( _Window );
}

void Application::setTickRate(const int & _Rate)
{
	_tick = _Rate;
}

void Application::setClipboard(const __LIB String & _Data)
{
	if ( FAILED( OpenClipboard( nullptr ) ) )
		throw std::runtime_error( "'Application::setClipboard' Failed to open clipboard" );

	if ( FAILED( EmptyClipboard( ) ) )
		throw std::runtime_error( "'Application::setClipboard' Failed to empty clipboard" );

	auto length = _Data.capacity( );
	auto glob = GlobalAlloc( GMEM_MOVEABLE, length );
	
	if ( !glob )
	{
		CloseClipboard( );
		throw std::runtime_error( "'Application::setClipboard' Failed to Allocate glob" );
	}

	memcpy( GlobalLock( glob ), _Data.c_str( ), length );
	GlobalUnlock( glob );
	SetClipboardData( CF_TEXT, glob );
	CloseClipboard( );
	GlobalFree( glob );
}

__LIB String Application::getClipboard() const
{
	if ( FAILED( OpenClipboard( nullptr ) ) )
		throw std::runtime_error( "'Application::setClipboard' Failed to open clipboard" );
	auto glob = GetClipboardData( CF_TEXT );
	String string;
	string.reserve( GlobalSize( glob ) );
	memcpy( (char*)string.c_str( ), GlobalLock( glob ), GlobalSize( glob ) );
	GlobalUnlock( glob );
	return string;
}

__LIB Event<void(Application*)>& Application::OnTick()
{
	return _OnTick;
}

end_LIB