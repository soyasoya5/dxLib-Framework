//#define DONT_LINK_GRAPHICS
#include "src\api"
#include <iomanip>
#include <array>

#pragma warning( disable : 4996 )
int main( )
{
	//FreeConsole( );
	// Create application
	auto appl = dx::Application::Create( );

	// Set tick rate
	appl->setTickRate( 15 );

	// Create window & painter
	auto window = dx::Window::Create( "ClassName", "UI Test", { { 300, 300 }, { 930, 590 } } );
	auto painter = dx::Painter::Create( window );
	
	// Only paint on Event
	window->SpecializePaint( dx::Window::OnTick_t );

	// Show
	window->Show( );

	// Bring to top
	window->BringToTop( );

	window->LoadIcon( "res/icons/Icon.ico" );
	window->LoadIconSm( "res/icons/Icon.ico" );

	// Handle the closing of our window
	window->OnWindowClosed( ) += []( dx::Window *sender )
	{
		// Exit the application
		dx::Application::get( )->exit( );
	};
	
	// Lets change the current default font, we dont want the font to be Arial
	auto context = painter->defaultFont( )->context( );
	context.Height = 20;
	context.Weight = 75;
	painter->setDefaultFont( dx::Font::Create( "Consolas", context ) );


	// Do background
	auto texture = dx::Texture::Create( "res/icons/Icon.png" );
	window->OnPaint( ) += [&texture]( dx::Window *sender, dx::BasePainter *painter )
	{
		painter->PaintRect( { { 0, 0 }, { sender->Width( ), sender->Height( ) } }, dx::Pen( dx::Colors::DarkSlateGray, 1 ) );
		texture->Paint( { 15, 15 }, { 1, 1 } );
	};

	dx::Hotkey hotkey{ { dx::key_control, dx::key_shift, dx::key_up }, "Ctrl|Shift|KeyUp" };
	dx::Hotkey hotkey_down{ { dx::key_control, dx::key_shift, dx::key_down }, "Ctrl|Shift|KeyDown" };
	hotkey.OnHotkey( ) += []( dx::Hotkey *sender, dx::EventArgs &args )
	{
		std::cout << "Hotkey " + sender->getName( ) << " pressed, sequence: { " << sender->sequence_as_string( ) << " }" << std::endl;
	};

	hotkey_down.OnHotkey( ) += [&window]( dx::Hotkey *sender, dx::EventArgs &args )
	{
		std::cout << "Hotkey " + sender->getName( ) << " pressed, stopping the handling of hotkeys" << std::endl;
		window->OnKeyDown( ) -= "Hotkey_down";
		window->OnKeyUp( ) -= "Hotkey_up";
	};


	window->OnKeyDown( ) += dx::EventHandler<dx::Window::KeyDownSig>( "Hotkey_down", [&]( dx::Window *sender, dx::KeyDownArgs &args )
	{
		hotkey.OnKeyDown( sender, args );
		hotkey_down.OnKeyDown( sender, args );
	});

	window->OnKeyUp( ) += dx::EventHandler<dx::Window::KeyUpSig>( "Hotkey_up", [&]( dx::Window *sender, dx::KeyUpArgs &args )
	{
		hotkey.OnKeyUp( sender, args );
		hotkey_down.OnKeyUp( sender, args );
	});

	// Lets just unregister the 2 above to proove the next method also works
	window->OnKeyDown( ) -= "Hotkey_down";
	window->OnKeyUp( ) -= "Hotkey_up";

	// ^ The 2 above can also be done like this
	window->OnKeyDown( ) += dx::EventHandler<dx::Window::KeyDownSig>( hotkey.getName( ) + "_down", BIND_METHOD_2( &dx::Hotkey::OnKeyDown, &hotkey ) );
	window->OnKeyUp( ) += dx::EventHandler<dx::Window::KeyUpSig>( hotkey.getName( ) + "_up", BIND_METHOD_2( &dx::Hotkey::OnKeyUp, &hotkey ) );
	window->OnKeyDown( ) += dx::EventHandler<dx::Window::KeyDownSig>( hotkey_down.getName( ) + "_down", BIND_METHOD_2( &dx::Hotkey::OnKeyDown, &hotkey_down ) );
	window->OnKeyUp( ) += dx::EventHandler<dx::Window::KeyUpSig>( hotkey_down.getName( ) + "_up", BIND_METHOD_2( &dx::Hotkey::OnKeyUp, &hotkey_down) );


	return appl->run( );
}

