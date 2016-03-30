//#define DONT_LINK_GRAPHICS
#include "src\api"


int main( )
{
	// Create application
	auto appl = dx::Application::Create( );

	// Set tick rate
	appl->setTickRate( 5 );

	// Create window & painter
	auto window = dx::Window::Create( "ClassName", "UI Test", { { 300, 300 }, { 600, 400 } } );
	auto painter = dx::Painter::Create( window );
	
	// Only paint on Event
	window->SpecializePaint( dx::Window::OnEvent_t );

	// Show
	window->Show( );

	// Bring to top
	window->BringToTop( );

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

	int guid = 0;

	// Create a button
	auto button = new dx::Button( );
	button->setUIID( ++guid ); // Set the ID of this component
	button->setText( "Light & Blue" ); // Text
	button->setLocalRegion( { { 15, 200 }, { 125, 30 } } ); // Position
	button->setAllignment( dx::Allignment::Center ); // Text allignment [	center	]
	button->setStyle( dx::StyleManager( dx::Theme::Light, dx::Style::Blue ) ); // Style

	auto button2 = new dx::Button( );
	button2->setUIID( ++guid ); // Set the ID of this component
	button2->setText( "Dark & Blue" ); // Text
	button2->setBottomOf( button ); // Now button2's y axis will be adjusted to be below button
	button2->setAllignedOf( button ); // Now button2's x axis will be adjusted to be alligned with button
	button2->setSize( { 125, 30 } ); // Size
	button2->setAllignment( dx::Allignment::Center ); // Text allignment [	center	]
	button2->setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) ); // Style

	auto button3 = new dx::Button( );
	button3->setUIID( ++guid ); // set the ID of this component
	button3->setText( "Light & Lime" ); // text
	button3->setRightOf( button ); // Now button3's x axis will be adjusted to be right of button
	button3->setAllignedOf( button ); // Now button3's y axis will be adjusted to be alligned with button
	button3->setSize( { 125, 30  } ); // Size
	button3->setAllignment( dx::Allignment::Right ); // Text allignment [	 center	]
	button3->setStyle( dx::StyleManager( dx::Theme::Light, dx::Style::Lime ) ); // Style

	auto button4 = new dx::Button( );
	button4->setUIID( ++guid ); // Set the ID of this component
	button4->setText( "Dark & Lime" ); // Text
	button4->setAllignedOf( button2 ); // Now button4's x axis will be adjusted to be alligned with button2
	button4->setBottomOf( button2 ); // Now button4's y axis will be adjusted to be bottom of button2.
	button4->setSize( { 125, 30  } ); // Size
	button4->setAllignment( dx::Allignment::Left ); // Text allignment [ center		]
	button4->setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Lime ) ); // Style


	// Do background
	window->OnPaint( ) += []( dx::Window *sender, dx::BasePainter *painter )
	{
		painter->PaintRect( { { 0, 0 }, { sender->Width( ), sender->Height( ) } }, dx::Pen( dx::Colors::DimGray, 1 ) );
	};

	window->HandleComponent( button );
	window->HandleComponent( button2 );
	window->HandleComponent( button3 );
	window->HandleComponent( button4 );
	
	return appl->run( );
}
