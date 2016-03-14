#include "src\api"
#include "src\lib\Graphics\Window\Window.h"

int main( )
{
	auto window = __GRAPHICS Window::Create( "TestWindow::D3D9",
											 "Test Window | dx", 
											 { { 300, 300 }, { 1280, 800 } } );
	
	window->ShowWindow( );
	window->UpdateWindow( );
	window->BringToTop( );

	window->OnWindowClosing( ) += []( __GRAPHICS Window *sender,
									  __GRAPHICS WindowClosingArgs &args )
	{
		if ( args.handled )
			return;

		auto ids = ::MessageBox( sender->native_handle( ), "Are you sure you want to exit?", "Sure?", MB_YESNO );
		if ( ids == IDYES )
			args.ShouldClose = true;
		else
			args.ShouldClose = false;
		args.handled = true;
	};

	window->OnWindowMinimize() += []( __GRAPHICS Window *sender )
	{
		std::cout << "Window Minimized!\n";
	};

	window->OnWindowRestored() += []( __GRAPHICS Window *sender )
	{
		std::cout << "Window Restored!\n";
	};

	window->OnWindowClosed( ) += []( __GRAPHICS Window *sender )
	{
		std::cout << "Window closed!\n";
	};

	while( window->PollEvents( ) )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );
	}
	std::cin.get( );
}
