#include "src\api"


int main( )
{
	auto application = dx::Application::Create( );
	auto window = dx::Window::Create( "TestWindow::D3D9",
									  "Test Window | dx", 
								      { { 300, 300 }, { 1280, 800 } } );

	dx::Painter::Create( window );
	std::cout << "State: " << dx::Application::getLastError( ) << std::endl;

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

	(window->OnScroll( ) += []( dx::Window *sender, dx::ScrollArgs &args )
	{
		if ( args.handled )
			return;
		std::cout << "Wheel Delta: " << args.delta << std::endl;
		auto painter = (dx::Painter*)sender->getPainter( );

		if ( args.up( ) )
		{
			auto context = painter->defaultFont( )->context( );
			context.Height += 5;
			auto putr = dx::Font::Create( "Arial", context, (dx::BasePainter*)painter );
			painter->setDefaultFont( putr );
		}
		else
		{
			auto context = painter->defaultFont( )->context( );
			context.Height -= 5;
			auto putr = dx::Font::Create( "Arial", context, (dx::BasePainter*)painter );
			painter->setDefaultFont( putr );
		}

		// Repaint : )
		sender->ForcePaint( );
	}).Every( std::chrono::milliseconds( 0 ) );


	window->OnPaint( ) += []( dx::Window *sender, dx::BasePainter *painter )
	{
		dx::Pen gray{ 0xFF252828, 1 }, blue{ 0xFF009DDE, 1 };
		painter->PaintRect( { { 0, 0 }, { sender->Width( ), sender->Height( ) } }, gray );
		
		dx::Text text;
		text.setFont( ((dx::Painter*)painter)->defaultFont( ) );
		text.setText( "Hello there" );
		text.setPosition( { 15, 15 } );
		text.setMaxClip( { sender->Width( ), sender->Height( ) } );
		painter->Paint( text, blue );
	};


	return application->run( );
}
