#include "Application.h"
#include "Graphics\Window\Window.h"

begin_LIB
static Application* _Application = nullptr;

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

int Application::run()
{
	_running = true;
	while( _running )
	{
		for ( auto&x : _windows )
		{
			x->PollEvents( );
			x->HandleTasks( );
			if ( x->PaintStyle( ) == __GRAPHICS Window::OnTick && x->has_painter( ) ) {
				auto painter = x->getPainter( );
				painter->BeginPaint( );
				x->OnPaint( ).Invoke( x, painter );
				painter->PresentPaint( );
			}
			std::this_thread::sleep_for( std::chrono::nanoseconds( 500 ) );
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
	}

	for ( auto&x : _windows )
		delete x;

	return 0;
}

void Application::exit()
{
	_running = false;
}

void Application::RegisterWindow(__GRAPHICS Window * _Window)
{
	_windows.push_back( _Window );
}


end_LIB