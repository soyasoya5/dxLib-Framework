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
	appl->setTickRate( 10 );

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

	dx::Checkbox checkbox;
	checkbox.setText( "Hello there" );
	checkbox.setUIID( 1337 );
	checkbox.setLocalRegion( { { 300, 300 }, { 25, 25 } } ); 
	checkbox.setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );
	checkbox.setLayout( dx::Layout::Horizontal );
	checkbox.setAllignment( dx::Allignment::Center );
	
	dx::Button button;
	button.setText( "(Text Left)" );
	button.setUIID( 10 );
	button.setLocalRegion( { { 15, 250 }, { 150, 30 } } );
	button.setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );
	button.setLayout( dx::Layout::Horizontal );
	button.setAllignment( dx::Allignment::Left );

	dx::Button button2;
	button2.setText( "(Text Center)" );
	button2.setUIID( 11 );
	button2.setBottomOf( &button );
	button2.setAllignedOf( &button );
	button2.setSize( { 150, 30 } );
	button2.setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );
	button2.setLayout( dx::Layout::Horizontal );
	button2.setAllignment( dx::Allignment::Center );

	dx::Button button3;
	button3.setText( "(Text Right)" );
	button3.setUIID( 12 );
	button3.setBottomOf( &button2 );
	button3.setAllignedOf( &button2 );
	button3.setSize( { 150, 30 } );
	button3.setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );
	button3.setLayout( dx::Layout::Horizontal );
	button3.setAllignment( dx::Allignment::Right );


	dx::RichLabel label;
	label.appendText( "Hi how are", dx::Colors::Green );
	auto tray = dx::Texture::Create( "tray.png" );
	label.appendText( tray );
	label.appendText( tray );
	label.appendText( " you?", dx::Colors::Red );
	label.setBottomOf( &button3 );
	label.setAllignedOf( &button3 );

	window->HandleComponent( &checkbox );
	window->HandleComponent( &button );
	window->HandleComponent( &button2 );
	window->HandleComponent( &button3 );
	window->HandleComponent( &label );

	return appl->run( );
}
