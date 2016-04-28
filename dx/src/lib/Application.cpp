#include "Application.h"
#include "Graphics\Window\Window.h"

begin_LIB
static Application* _Application = nullptr;
int Application::ilasterr_ = 0;

Application::Application()
	: windows_( )
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

void Application::setLastError(const int & errc )
{
	ilasterr_ = errc;
}

int Application::getLastError()
{
	return ilasterr_;
}

int Application::run()
{
	running_ = true;
	while( running_ )
	{
		OnTick( ).Invoke( this );
		for ( auto&x : windows_ )
		{
			x->PollEvents( );
			x->HandleTasks( );
			if ( x->PaintStyle( ) == ::dx::lib::Graphics::Window::OnTick_t && x->has_painter( ) ) {
				auto painter = x->getPainter( );
				painter->BeginPaint( );
				x->OnPaint( ).Invoke( x, painter );
				painter->PresentPaint( );
			}
			std::this_thread::sleep_for( std::chrono::nanoseconds( 500 ) );
		}

		for ( auto &x : invokes_ )
			x.invoke( );

		invokes_.clear( );
		std::this_thread::sleep_for( std::chrono::milliseconds( tick_ ) );
	}
	return getLastError( );
}

void Application::exit()
{
	running_ = false;
}

void Application::RegisterWindow(::dx::lib::Graphics::Window * window)
{
	windows_.push_back( window );
	window->OnWindowClosed( ) += [this]( ::dx::lib::Graphics::Window *window )
	{
		this->BeginInvoke( [this, window = window]() { this->UnregisterWindow( window ); } );
	};
}

void Application::UnregisterWindow(::dx::lib::Graphics::Window * window)
{
	for ( auto it = windows_.begin( ), end = windows_.end( );
		  it < end;
		  ++it )
	{
		if ( *it == window )
		{
			windows_.erase( it );
			break;
		}
	}
}

void Application::setTickRate(const int & rate)
{
	tick_ = rate;
}

void Application::setClipboard(const String & data)
{
	if ( FAILED( OpenClipboard( nullptr ) ) )
		throw std::runtime_error( "'Application::setClipboard' Failed to open clipboard" );

	if ( FAILED( EmptyClipboard( ) ) )
		throw std::runtime_error( "'Application::setClipboard' Failed to empty clipboard" );

	auto length = data.capacity( );
	auto glob = GlobalAlloc( GMEM_MOVEABLE, length );
	
	if ( !glob )
	{
		CloseClipboard( );
		throw std::runtime_error( "'Application::setClipboard' Failed to Allocate glob" );
	}

	memcpy( GlobalLock( glob ), data.c_str( ), length );
	GlobalUnlock( glob );
	SetClipboardData( CF_TEXT, glob );
	CloseClipboard( );
	GlobalFree( glob );
}

::dx::lib::String Application::getClipboard() const
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

::dx::lib::Event<void(Application*)>& Application::OnTick()
{
	return _OnTick;
}

end_LIB