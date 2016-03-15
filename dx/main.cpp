#include "src\api"

int main( )
{
	auto application = dx::Application::Create( );

	auto window = dx::Window::Create( "TestWindow::D3D9",
									  "Test Window | dx", 
								      { { 300, 300 }, { 1280, 800 } } );
	window->ShowWindow( );
	window->UpdateWindow( );
	window->BringToTop( );

	window->OnWindowClosing( ) += []( dx::Window *sender, dx::WindowClosingArgs &args )
	{
		if ( args.handled ) // if already handled just return
			return;

		auto ids = dx::MsgBox( sender, "Are you sure you want to exit?", "Sure?", dx::YesNo | dx::IconQuestion ).Show( );

		if ( ids == dx::MsgBox::Yes )
			args.ShouldClose = true;
		else
			args.ShouldClose = false;
		args.handled = true;
	};


	window->OnWindowMinimize( ) += []( dx::Window *sender )
	{
		std::cout << "Window is not allowed to be minimized, restoring in 50 milliseconds.\n";
		sender->addTask( dx::Clock::now( ) + std::chrono::milliseconds( 50 ),
						 []( dx::Window *sender )
						 { sender->Restore( ); } 
					    ).Completed( ) += []( dx::TimedTask<void(dx::Window*)> * sender) { std::cout << "Restored\n"; };
	};

	window->OnWindowClosed( ) += []( dx::Window *sender )
	{
		auto appl = dx::Application::get( );
		// We want to exit the applicaiton when the main window is closed.
		appl->exit( );
	};

	return application->run( );
}




