#include "src\api"

int main( )
{
	auto application = dx::Application::Create( );
	auto window = dx::Window::Create( "TestWindow::D3D9",
									  "Test Window | dx", 
								      { { 300, 300 }, { 1280, 800 } } );

	dx::Painter::Create( window );

	// Disable main window whilst 'sub_window' is open
	window->Show( );
	window->BringToTop( );
	window->SpecializePaint( dx::Window::OnEvent ); // Can also be dx::Window::OnTick

	window->LoadIcon( "icon.ico" );
	window->LoadIconSm( "icon.ico" );


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
		std::cout << "Window is not allowed to be minimized\n";
		sender->addTask( dx::Clock::now( ) + std::chrono::milliseconds( 1 ),
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
	

	std::once_flag flag;
	window->OnPaint( ) += [&flag]( dx::Window *sender, dx::BasePainter *painter )
	{
		dx::Pen pen, pen2;
		pen.Color( dx::Colors::Red );
		pen.Thickness( 1 );
		pen2.Color( dx::Colors::Black );
		pen2.Thickness( 5 );
		dx::Region region{ { 0, 0 },{ sender->Width( ), sender->Height( ) } };

		dx::Line line{ { 300, 300 }, { 600, 600 }, pen2 };
		painter->PaintRect( region, pen );
		painter->PaintLine( line );
	};

	return application->run( );
}
