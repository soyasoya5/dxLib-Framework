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

	auto slider = new dx::Slider( );
	slider->setLocalRegion( { { 25, 200 }, { 200, 30 } } );
	slider->setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );
	slider->setLayout( dx::Horizontal );
	
	window->HandleComponent( slider );

	return appl->run( );
}
