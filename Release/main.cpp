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

void readBinaryFile( byte** _Buffer, uint &_Length, const dx::String &_File )
{
	auto dwAttrib = GetFileAttributes( _File.c_str( ) );

	if ( !(dwAttrib != INVALID_FILE_ATTRIBUTES &&
		 !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) )
	{
		std::cout << "Files are invalid.\n";
		std::cin.get( );
		exit( 1 );
	}
	
	std::ifstream file( _File.c_str( ) );
	file.seekg( 0, std::ios::end );
	auto size = file.tellg( );
	file.seekg( 0, std::ios::beg );

	*_Buffer = new byte[size];
	file.read( (char*)*_Buffer, size );
	file.close( );

	_Length = size;
}

dx::String to_hex( const int &_Byte )
{
	std::stringstream stream;
	stream << std::hex << _Byte;
	return stream.str( ).c_str( );
}

dx::Pattern ComposePattern( byte** _Ptr, dx::MemoryBase* _Mem, dx::Module* _Module, uint _Length )
{
	dx::String _pattern;
	for ( auto ptr = *_Ptr, max = (*_Ptr + _Length); ptr < max; ++ptr )
	{
		_pattern.append( to_hex( *ptr ) );
		if ( ptr + 1 < max )
			_pattern.append( " " );
	}
	*_Ptr += _Length - 1;
	return dx::Pattern( _pattern, _Module, _Mem );
}

std::string Line( unsigned l )
{
	int m = l-1; return "\r" + (m<0?"\33["+std::to_string(-m)+'A':std::string(m, '\0'));
}

void main( int argc, char** argv, char**envp )
{
	srand( 123456u );
	if ( argc < 3 ) {
		std::cout << "To few arguments.\n";
		std::cin.get( );
		return;
	}
	auto Reader = new dx::InternalImpl( );
	Reader->Setup( "CCompare" );

	std::cout << "File A: " << argv[1] << std::endl;
	std::cout << "File B: " << argv[2] << std::endl;
	std::cout << "Reading files into ram..." << std::endl;
	
	byte *a_ptr, *b_ptr;
	uint a_len, b_len;
	readBinaryFile( &a_ptr, a_len, argv[1] );
	readBinaryFile( &b_ptr, b_len, argv[2] );
	auto length = min( a_len, b_len );

	auto avgLen = a_len / b_len % 24;
	if ( avgLen == 0 )
		avgLen = 1;

	avgLen *= 16;
	std::cout << "Average pattern length: " << avgLen << ".\n";
	
	
	std::cout << "Compiling patterns...\n";
	std::vector<dx::Pattern> a_patterns;
	dx::Module aModule{ (ulong)a_ptr, a_len, "aModule" }, bModule{ (ulong)b_ptr, b_len, "bModule" };

	// Compile pattern for file A
	for ( auto ptr = a_ptr; (ptr + avgLen) < (a_ptr + length); ++ptr )
	{
		a_patterns.push_back( ComposePattern( &ptr, Reader, &bModule, avgLen ) );
	}

	std::cout << "Compiled " << a_patterns.size( ) << " amount of patterns for file A.\n";

	std::cout << "Testing them on file B...\n";
	int accuracyCount = 0, count = 0;
	float dt = 0.0f;
	std::thread thread{ 
		[ac = &count, constant = a_patterns.size( ), delta = &dt]() 
		{
			while (true) 
			{ 
				std::cout << Line(10) << "Progress : Time passed: " << (float)((float)*ac / (float)constant) * (float)100
				<< "%" << " | " << *delta << "s";
				Sleep(15); 
			}
		} };
	Timer timer;
	for ( auto &x : a_patterns )
	{
		++count;
		dt += timer.GetDeltaTime( );
		auto addr = x.Scan( );
		if ( addr.IsNullOrZero( ) )
			continue;
		++accuracyCount;
	}
	++count;
	TerminateThread( thread.native_handle( ), 0 );

	std::cout << "\n\nAmount of patterns found in file B: " << accuracyCount << std::endl;
	// (_barPos.x / (getSize().x - _barSize.x)) * getMax();
	std::cout << "Percentage: " << (float)( (float)accuracyCount / (float)a_patterns.size( ) ) * (float)100 << "% accurate.\n";
	delete[] a_ptr, b_ptr;
	std::cin.get( );
}
