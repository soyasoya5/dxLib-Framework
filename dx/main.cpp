//#define DONT_LINK_GRAPHICS
#include "src\api"

class Test
{
public:


	void modify( double & val )
	{
		val = 5;
	}
};


int main( )
{
	auto appl = dx::Application::Create( );
	appl->setTickRate( 5 );
	auto window = dx::Window::Create( "ClassName", "UI Test", { { 300, 300 }, { 600, 400 } } );
	auto painter = dx::Painter::Create( window );
	
	window->SpecializePaint( dx::Window::OnTick_t );
	window->Show( );
	window->BringToTop( );
	window->OnWindowClosed( ) += []( dx::Window *sender )
	{
		dx::Application::get( )->exit( );
	};
	
	auto context = painter->defaultFont( )->context( );
	context.Height = 20;
	context.Weight = 75;
	painter->setDefaultFont( dx::Font::Create( "Caviar Dreams", context ) );

	int guid = 0;
	auto button = new dx::Button( );
	button->setUIID( ++guid );
	button->setText( "Light & Blue" );
	button->setFont( painter->defaultFont( ) );
	button->setLocalRegion( { { 15, 200 }, { 125, 30 } } );
	button->setAllignment( dx::Allignment::Center );
	button->setStyle( dx::StyleManager( dx::Theme::Light, dx::Style::Blue ) );
	button->setLayout( dx::Layout::Horizontal );
	button->setVisible( true );
	button->setEnabled( true );

	auto button2 = new dx::Button( );
	button2->setUIID( ++guid );
	button2->setText( "Dark & Blue" );
	button2->setFont( painter->defaultFont( ) );
	button2->setLocalRegion( { { 15, 235 }, { 125, 30 } } );
	button2->setAllignment( dx::Allignment::Center );
	button2->setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );
	button2->setLayout( dx::Layout::Horizontal );
	button2->setVisible( true );
	button2->setEnabled( true );

	auto button3 = new dx::Button( );
	button3->setUIID( ++guid );
	button3->setText( "Light & Lime" );
	button3->setFont( painter->defaultFont( ) );
	button3->setLocalRegion( { { 145, 200 }, { 125, 30 } } );
	button3->setAllignment( dx::Allignment::Center );
	button3->setStyle( dx::StyleManager( dx::Theme::Light, dx::Style::Lime ) );
	button3->setLayout( dx::Layout::Horizontal );
	button3->setVisible( true );
	button3->setEnabled( true );

	auto button4 = new dx::Button( );
	button4->setUIID( ++guid );
	button4->setText( "Dark & Lime" );
	button4->setFont( painter->defaultFont( ) );
	button4->setLocalRegion( { { 145, 235 }, { 125, 30 } } );
	button4->setAllignment( dx::Allignment::Center );
	button4->setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Lime ) );
	button4->setLayout( dx::Layout::Horizontal );
	button4->setVisible( true );
	button4->setEnabled( true );

	
	window->HandleComponent( button );
	window->HandleComponent( button2 );
	window->HandleComponent( button3 );
	window->HandleComponent( button4 );
	
	return appl->run( );
}
