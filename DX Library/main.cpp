#include "Framework\Utils\Utils.h"
#include "Framework\Utils\Clock.h"
#include "Framework\Utils\string.h"
#include "Framework\FileIO\Config.h"
#include "Framework\Graphics\Stylesheet\Style.h"
#include "Framework\Graphics\Stylesheet\Stylesheet.h"
#include "Framework\Graphics\Renderer\Renderer.h"
#include "Framework\Window\Win32Window.h"
#include "Framework\Graphics\Form.h"
#include "Framework\Graphics\UI\Canvas.h"
#include "Framework\Graphics\UI\Component.h"
#include "Framework\Graphics\UI\Button.h"
#include "Framework\Graphics\UI\Checkbox.h"
#include "Framework\Graphics\UI\Label.h"
#include "Framework\Graphics\UI\Window.h"
#include "Framework\Graphics\UI\TabControl.h"
#include "Framework\Graphics\UI\UML\UML.h"
#include "Framework\Utils\Logger.h"
#include "Framework\Graphics\UI\Textbox.h"
#include "Framework\Graphics\UI\ListBox.h"
#include "Framework\Graphics\UI\BackgroundTask.h"
#include "Framework\Graphics\UI\RichLabel.h"
#include "Framework\Graphics\FontMetrics\Font.h"
#include "Framework\Graphics\FontMetrics\Metrics.h"
#include "Framework\Window\WinDispatcher.h"
#include <iostream>

#pragma warning ( disable : 4996 )

using namespace Graphics;
using namespace UI;
using namespace Style;
using namespace FileIO;
using namespace Utils;


class MainForm : public Form
{
private:
	RichLabel label;
	bool Completed = true;

public:

	void Initalize( )
	{
		this->_win32window->getRenderer( )->PrepareFont( "Caviar", "Caviar Dreams", 25, 75 );
		this->_win32window->getRenderer( )->PrepareFont( "CaviarS", "Caviar Dreams", 20, 75 );
		auto style = CreateStyleSheet( "Style_gray.ini" );

		this->_window = new Window( );
		_window->setText( "Find a File" );
		_window->setFont( "Caviar" );
		_window->setAllignment( Left );
		_window->setPadding( { 300, 300 } );
		_window->setSize( { 600, 400 } );
		_window->setTopMost( true );

		label += Text( "int ", D3DCOLOR_ARGB(255, 0, 157, 222) );
		label += Text( "var ", D3DCOLOR_ARGB(255, 222, 157, 0) );
		label += Text( "= " );
		label += Text( "0x25", D3DCOLOR_ARGB(255, 25, 65, 10) );
		label += Text( ";\n" );
		label += Text("int ", D3DCOLOR_ARGB(255, 0, 157, 222));
		label += Text("var ", D3DCOLOR_ARGB(255, 222, 157, 0));
		label += Text("= ");
		label += Text("0x25", D3DCOLOR_ARGB(255, 25, 65, 10));
		label += Text( ";\n" );

		label += Text("int ", D3DCOLOR_ARGB(255, 0, 157, 222));
		label += Text("var ", D3DCOLOR_ARGB(255, 222, 157, 0));
		label += Text("= ");
		label += Text("0x25", D3DCOLOR_ARGB(255, 25, 65, 10));
		label += Text(";\n");

		label += Text("int ", D3DCOLOR_ARGB(255, 0, 157, 222));
		label += Text("var ", D3DCOLOR_ARGB(255, 222, 157, 0));
		label += Text("= ");
		label += Text("0x25", D3DCOLOR_ARGB(255, 25, 65, 10));
		label += Text(";\n");

		label += Text( "Just a showcase of " );
		label += Text( "multi-colored\n", D3DCOLOR_ARGB(255, 150, 25, 25) );
		label += Text( "text rendering." );

	
		label.setFont( "CaviarS" );
		label.setPadding( { 15, 45 } );


		_window->addChild( &label );
		_canvas->add( _window );
		_window->setStylesheet( *style );
	}

	void Tick( )
	{
		_window->Tick( );
	} 


};


class LoginForm : public Form
{
private:
	pointer<Textbox> username, password;
	pointer<LinkedLabel> forgot_pass;
	pointer<Button> authenticate;
public:

	void Initalize( )
	{
		auto renderer = getWin32( )->getRenderer( );
		renderer->PrepareFont( "CaviarT", "Caviar Dreams", 25, 75 );
		renderer->PrepareFont( "CaviarS", "Caviar Dreams", 20, 100 );
		renderer->PrepareFont( "CaviarSmall", "Caviar Dreams", 15, 150 );
		auto style = CreateStyleSheet( "Style_gray.ini" );


		// Window
		_window = new Window( );
		_window->setName( "LoginForm::_window" );
		_window->setText( "Authenticate" );
		_window->setFont( "CaviarT" );
		_window->setSize( { 400, 200 } );
		_window->setAbsolutePosition( { 300, 300 } );

		// Username
		username = new Textbox( );
		username->setName( "LoginForm::username" );
		username->setHiddenText( "Username" );
		username->setFont( "CaviarS" );
		username->setAllignment( Left );
		username->setPadding( { 137, 55 } );
		username->setSize( { 150, 25 } );

		// Forgotten password
		forgot_pass = new LinkedLabel( );
		forgot_pass->setName( "LoginForm::forgot_pass" );
		forgot_pass->setText( "Forgotten password?" );
		forgot_pass->setLink( "www.google.com" );
		forgot_pass->setFont( "CaviarSmall" );
		forgot_pass->setPadding( { 25, 90 } );
		
		// Password
		password = new Textbox( );
		password->setName( "LoginForm::password" );
		password->setHiddenText( "Enter password" );
		password->setFont( "CaviarS" );
		password->setAllignment( Left );
		password->setPadding( { 137, 110 } );
		password->setSize( { 150, 25 } );
		password->setPassword( true );
		password->setPasswordChar( '*' );

		// Authenticate
		authenticate = new Button( );
		authenticate->setName( "LoginForm::authenticate" );
		authenticate->setText( "Sign In" );
		authenticate->setFont( "CaviarS" );
		authenticate->setAllignment( Middle );
		authenticate->setPadding( { 125, 150 } );
		authenticate->setSize( { 100, 30 } );
		authenticate->OnComponentClicked( ) += [&]( pointer<Component> sender, Vector2 v )mutable->bool
		{
			return this->Authenticate( sender, v );
		};


		_window->addChild( username );
		//_window->addChild( forgot_pass );
		_window->addChild( password );
		_window->addChild( authenticate );
		_window->setStylesheet( *style );
		_canvas->add( _window );
	}

	bool Authenticate( pointer<Component> sender, Vector2 )
	{
		auto text = username->getText( );
		if ( text.length( ) < 5 ) {
			this->Dialog(
						Dialog_ok,
						{ Text( "Username must be greater than 5 characters.", Colors::Red ) },
						"Error",
						"Error_dialog_username",
						[text, this]( DialogResult result, pointer<Window> window, pointer<Canvas> canvas )
						{
							std::cout << "'Error_dialog_username' clicked, result: " << (result == Result_Yes ? "Yes" : "No") << std::endl;
						},
				        this->_window );
			return false;
		}

		text = password->getText( );

		auto is_less = text.length( ) < 5;
		auto contains_numerical = text.hasNumerical( );
		auto contains_capital = text.hasCapital( );

		if ( is_less || 
			 !contains_numerical ||
			 !contains_capital )
		{
			this->Dialog(
						Dialog_ok,
						{ Text( "Password must meet these requirements:\n" ),
						  Text( "Longer than 5 characters.\n", is_less ? Colors::Red : Colors::Green ),
						  Text( "Contains a numerical character.\n", !contains_numerical ? Colors::Red : Colors::Green ),
						  Text( "Contains a captical character.\n", !contains_capital ? Colors::Red : Colors::Green )
						  },
						"Error",
						"Error_dialog_username",
						[text, this]( DialogResult result, pointer<Window> window, pointer<Canvas> canvas )
						{
							std::cout << "'Error_dialog_username' clicked, result: " << (result == Result_Yes ? "Yes" : "No") << std::endl;
						},
				        this->_window );
			return false;
		}
	}

	void Tick( )
	{
		this;
		_window->Tick( );
	}

};

#include "Framework\Utils\Memory\External.h"
#include "Framework\Utils\Memory\Internal.h"
#include "Framework\Utils\Memory\Module.h"
#include "Framework\Utils\Memory\Pattern.h"

void main( int argc, char** argv, char**envp )
{
	char* bytes = new char[1000];
	dx::memset( ccast<byte*>( bytes ), 0, 1000 );
	bytes[800] = 0xA;
	bytes[801] = 0xB;
	bytes[802] = 0xC;
	bytes[803] = 0xD;
	bytes[804] = rand( ) % 255 + 1;
	bytes[805] = rand( ) % 255 + 1;
	bytes[806] = rand( ) % 255 + 1;
	bytes[807] = rand( ) % 255 + 1;
	bytes[808] = 0xCA;

	auto mem = new dx::InternalImpl( );
	if ( !mem->Setup( "FindFile.exe" ) )
		std::cerr << "Failed to setup memory.\n";
	
	dx::Module base{ (uint)bytes, 1000, "Base" };
	
	dx::Pattern pattern{ "0A 0B 0C 0D ?? ?? ?? ?? CA" /* Pattern to be searched for */, 
					     &base /* The module or region in memory to search. */, 
					     mem /* The memory reader/writer being used. */ };

	dx::Clock clock;
	clock.Start( );
	auto addr = pattern.Scan( );
	clock.End( );
	if ( addr.getOffset( ) != 0 )
	{
		std::cout << "Found pattern correctly.\n";
		std::cout << "Module base: [0x"  << std::hex << base.Image( ) << "]" << std::endl;
		std::cout << "Offset from base: [" << std::dec << addr.getOffset( ) << "]" << std::endl;
		std::cout << "Exact address: [0x" << std::hex << addr.get_addr( ) << "]" << std::endl;
	}

	std::cout << "It took " << std::dec << clock.Nano( ) << " nanoseconds to scan 1000 bytes.";


	auto window = new Win32Window( );
	WindowParams params;
	params.type = WindowParams::type_standard; 
	params.size = { 1280, 800 };
	params.pos = { 0, 0 };
	params.szClass = "D9Overlay";
	params.szTitle = "D9Title";

	if ( !window->Create( &params ) )
	{
		::MessageBoxA( nullptr, "Failed to create a Win32 window.", "Error", MB_OK );
		return;
	}
	auto render = window->getRenderer( );
	auto dispatcher = std::make_unique<WinDispatcher>();

	window->OnWindowClose() += [&]()->bool
	{
		auto id = ::MessageBox(window->getHWND(), "Are you sure you want to exit?", "Sure?", MB_YESNO);
		if (id == IDYES)
			return false;
		return true;
	};

	window->OnWindowResize() += [&](Vector2 sz, HWND)->bool
	{
		render->Reset( sz );
		return true;
	};


	window->LaunchForm( new LoginForm( ) );
	render->Reset( { 1920, 1080 } );

	clock.Start( );
	int iFrameC = 0, iAvgFrames = 60;
	//window->OverrideDispatcher( dispatcher.get( ) );
	while( window->PollEvents( ) )
	{
		render->Begin( 0x0 );
		window->PaintForms( );
		render->String( 15, 15, "CaviarT", Colors::White, ("FPS: [" + std::to_string( iAvgFrames ) + "]").c_str( ) );
		render->Present( );

		if ( clock.Milli( ) > 1000)
		{ 
			iAvgFrames = iFrameC;
			iFrameC = 0;
			clock.Start( );
		}
		clock.End( );
		++iFrameC;

		window->TickForms( );
		Sleep( 1 );
	}

}