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
#include "Framework\Utils\Memory\External.h"
#include "Framework\Utils\Memory\Internal.h"
#include "Framework\Utils\Memory\Module.h"
#include "Framework\Utils\Memory\Pattern.h"
#include "Framework\FileIO\Path.h"
#include <iostream>

#pragma warning ( disable : 4996 )




class MainForm : public dx::Form
{
private:
	dx::RichLabel label;
	bool Completed = true;

public:

	void Initalize( )
	{
		this->_win32window->getRenderer( )->PrepareFont( "Caviar", "Caviar Dreams", 25, 75 );
		this->_win32window->getRenderer( )->PrepareFont( "CaviarS", "Caviar Dreams", 20, 75 );
		auto style = dx::CreateStyleSheet( "Style_gray.ini" );

		this->_window = new dx::Window( );
		_window->setText( "Find a File" );
		_window->setFont( "Caviar" );
		_window->setAllignment( dx::Left );
		_window->setPadding( { 300, 300 } );
		_window->setSize( { 600, 400 } );
		_window->setTopMost( true );

		label += dx::Text( "int ", D3DCOLOR_ARGB(255, 0, 157, 222) );
		label += dx::Text( "var ", D3DCOLOR_ARGB(255, 222, 157, 0) );
		label += dx::Text( "= " );
		label += dx::Text( "0x25", D3DCOLOR_ARGB(255, 25, 65, 10) );
		label += dx::Text( ";\n" );
		label += dx::Text("int ", D3DCOLOR_ARGB(255, 0, 157, 222));
		label += dx::Text("var ", D3DCOLOR_ARGB(255, 222, 157, 0));
		label += dx::Text("= ");
		label += dx::Text("0x25", D3DCOLOR_ARGB(255, 25, 65, 10));
		label += dx::Text( ";\n" );

		label += dx::Text("int ", D3DCOLOR_ARGB(255, 0, 157, 222));
		label += dx::Text("var ", D3DCOLOR_ARGB(255, 222, 157, 0));
		label += dx::Text("= ");
		label += dx::Text("0x25", D3DCOLOR_ARGB(255, 25, 65, 10));
		label += dx::Text(";\n");

		label += dx::Text("int ", D3DCOLOR_ARGB(255, 0, 157, 222));
		label += dx::Text("var ", D3DCOLOR_ARGB(255, 222, 157, 0));
		label += dx::Text("= ");
		label += dx::Text("0x25", D3DCOLOR_ARGB(255, 25, 65, 10));
		label += dx::Text(";\n");

		label += dx::Text( "Just a showcase of " );
		label += dx::Text( "multi-colored\n", D3DCOLOR_ARGB(255, 150, 25, 25) );
		label += dx::Text( "text rendering." );

	
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

class LoginForm : public dx::Form
{
private:
	pointer<dx::Textbox> username, password;
	pointer<dx::LinkedLabel> forgot_pass;
	pointer<dx::Button> authenticate;
public:

	void Initalize( )
	{
		using namespace dx;
		auto renderer = getWin32( )->getRenderer( );
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
		username->setFont( "Caviar" );
		username->setAllignment( Left );
		username->setPadding( { 137, 55 } );
		username->setSize( { 150, 25 } );

		// Forgotten password
		forgot_pass = new LinkedLabel( );
		forgot_pass->setName( "LoginForm::forgot_pass" );
		forgot_pass->setText( "Forgotten password?" );
		forgot_pass->setLink( "www.google.com" );
		forgot_pass->setFont( "Caviar" );
		forgot_pass->setPadding( { 187, 150 } );
		
		// Password
		password = new Textbox( );
		password->setName( "LoginForm::password" );
		password->setHiddenText( "Enter password" );
		password->setFont( "Caviar" );
		password->setAllignment( Left );
		password->setPadding( { 137, 110 } );
		password->setSize( { 150, 25 } );
		password->setPassword( true );
		password->setPasswordChar( '*' );

		// Authenticate
		authenticate = new Button( );
		authenticate->setName( "LoginForm::authenticate" );
		authenticate->setText( "Sign In" );
		authenticate->setFont( "Caviar" );
		authenticate->setAllignment( Middle );
		authenticate->setPadding( { 125 / 2, 150 } );
		authenticate->setSize( { 100, 30 } );
		authenticate->OnComponentClicked( ) += [&]( pointer<Component> sender, Vector2 v )mutable->bool
		{
			return this->Authenticate( sender, v );
		};


		_window->addChild( username );
		_window->addChild( forgot_pass );
		_window->addChild( password );
		_window->addChild( authenticate );
		_window->setStylesheet( *style );
		_canvas->add( _window );
	}

	bool Authenticate( pointer<dx::Component> sender, Vector2 )
	{
		using namespace dx;
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

class PatternScanner : public dx::Form
{
private:
	dx::Textbox *_file1, *_file2;
	dx::Button *_scan, *_stop, *_pause;
	dx::ListBox *_errors, *_logs;
	dx::TabControl *_control;
	dx::Tab *_tab1, *_tab2;
	
public:
	void Initalize( )
	{
		using namespace dx;
		auto render = this->getWin32( )->getRenderer( );
		auto canvas = this->getCanvas( );

		_file1 = new dx::Textbox( ), _file2 = new dx::Textbox( );
		_scan = new dx::Button( ), _stop = new dx::Button( ), _pause = new dx::Button( );
		_errors = new dx::ListBox( ), _logs = new dx::ListBox( );
		_control = new dx::TabControl( );
		_tab1 = new dx::Tab( ), _tab2 = new dx::Tab( );
		_window = new Window( );


		_window->setName( "PatternScanner::_window" );
		_window->setText( "Compare files" );
		_window->setFont( "CaviarT" );
		_window->setSize( { 800, 600 } );
		_window->setAbsolutePosition( { 300, 300 } );


		_control->setFont( "Caviar" );
		_control->setSize( { 100, 30 } );
		_control->setPadding( { 5, 55 } );
		_control->setType( Horizontal );
		

		// -----------------------------------------
		// TAB One
		// -----------------------------------------
		_tab1->setText( "Scanner" );
		
		
		// File
		_file1->setHiddenText( "File A" );
		_file1->setFont( "Caviar" );
		_file1->setSize( { 200, 30 } );
		_file1->setPadding( { 10, 55 } );
		_file1->setAllignment( Middle );

		// File2
		_file2->setHiddenText( "File B" );
		_file2->setFont( "Caviar" );
		_file2->setSize( { 200, 30 } );
		_file2->setPadding( { 10, 90 } );
		_file2->setAllignment( Middle );

		// Scan
		_scan->setText( "Scan" );
		_scan->setFont( "Caviar" );
		_scan->setAllignment( Middle );
		_scan->setSize( { 100, 30 } );
		_scan->setPadding( { 10, 125 } );
		_scan->OnComponentClicked( ) += BIND_METHOD_2( &PatternScanner::Scan, this );

		// Pause
		_pause->setText( "Pause" );
		_pause->setFont( "Caviar" );
		_pause->setAllignment( Middle );
		_pause->setSize( { 100, 30 } );
		_pause->setPadding( { 115, 125 } );
		_pause->OnComponentClicked( ) += BIND_METHOD_2( &PatternScanner::Pause, this );

		// Stop
		_stop->setText( "Pause" );
		_stop->setFont( "Caviar" );
		_stop->setAllignment( Middle );
		_stop->setSize( { 100, 30 } );
		_stop->setPadding( { 220, 125 } );
		_stop->OnComponentClicked( ) += BIND_METHOD_2( &PatternScanner::Stop, this );

		// Errors
		_errors->setText( "Errors" );
		_errors->setFont( "Caviar" );
		_errors->setAllignment( Left );
		_errors->setSize( { 300, 300 } );
		_errors->setPadding( { 15, 165 } );

		_errors->addItem( "Added 25 gold11!", "", Colors::White );
		_errors->addItem( "died 8[", "", Colors::Red );
		_errors->addItem( "w0wsers nullptr!!!", "", Colors::Orange );
		_errors->addItem( "Some log message smh", "", Colors::White );
		_errors->addItem( "rip logs very not creative!", "", Colors::Orange );


		// -----------------------------------------
		// TAB Two
		// -----------------------------------------
		_tab2->setText( "Error?" );


		// Winodw/control
		_canvas->add( _window );
		_window->addChild( _control );
		_control->addTab( _tab1 );
		_control->addTab( _tab2 );

		// Tab One
		_tab1->addChild( _file1 );
		_tab1->addChild( _file2 );
		_tab1->addChild( _scan );
		_tab1->addChild( _stop );
		_tab1->addChild( _pause );
		_tab1->addChild( _errors );

		// Tab Two
		//_tab2->addChild( _errors );
		_tab2->addChild( _logs );

		_window->setStylesheet( Style::DEFAULT_STYLE );
	}

	bool Scan( dx::Component *sender, Vector2 area )
	{
		std::cout << ( "Scan.\n" );
		return true;
	}

	bool Pause( dx::Component *sender, Vector2 area )
	{
		std::cout << ("Pause.\n");
		return true;
	}

	bool Stop( dx::Component *sender, Vector2 area )
	{
		std::cout << ("Stop.\n");
		return true;
	}

	void Tick( )
	{
		_window->Tick( );
	}

};

std::string tab( uint tabs = 0 )
{
	std::string ret = "";
	for ( uint i = 0; i < tabs; ++i )
		ret += "    ";
	return ret;
}

void main( int argc, char** argv, char**envp ) 
{
	dx::Path path{ "C:\\Program Files (x86)\\AviSynth 2.5\\Uninstall.exe" };
	std::cout << "Is directory: " << (path.is_directory( ) ? "true" : "false") << std::endl;
	std::cout << "Has extension: " << (path.has_extension( ) ? "true" : "false") << std::endl;
	std::cout << "Has filename: " << (path.has_filename( ) ? "true" : "false") << std::endl;
	std::cout << "Has branches: " << (path.has_branches( ) ? "true" : "false") << std::endl;
	std::cout << "Filename: \"" << path.Filename( ) << "\"" << std::endl;
	std::cout << "Previous: \"" << path.Previous( ) << "\"" << std::endl;
	std::cout << "Previous: \"" << path.UptoPrevious( ) << "\"" << std::endl;
	std::cout << "Extension: \"" << path.Extension( ) << "\"" << std::endl;
	std::cout << "Exists: " << dx::exists( path ) << std::endl;
	std::cout << "Branches ----------\n";
	auto branches = path.Branches( );
	for ( uint i = 0; i < branches.size( ); ++i )
	{
		auto branch = &branches[i];
		std::cout << tab( i + 1 ) << *branch << std::endl;
	}

	std::cin.get( );
	/*
	auto window = new Win32Window( );
	auto params = WindowParams( );
	params.pos = { 0, 0 };
	params.size = { 1280, 720 };
	params.szClass = "Overlayed_";
	params.szTitle = "Overlayed_";
	params.transparency_key = 0x0;
	params.type = WindowParams::type_standard;

	if ( !window->Create( &params ) )
	{
		std::cerr << "Failed creating window..\n";
		std::cin.get( );
		return;
	}

	window->OnWindowResize( ) += []( pointer<Win32Window> sender, Vector2 size, HWND native )->bool
	{
		auto render = sender->getRenderer( );
		return render->Reset( size );
	};

	auto render = window->getRenderer( );
	render->PrepareFont( "Caviar", "Caviar Dreams", 20, 75 );
	render->PrepareFont( "CaviarT", "Caviar Dreams", 25, 200 );
	render->PrepareFont( "CaviarS", "Caviar Dreams", 18, 50 );

	window->LaunchForm( new PatternScanner( ) );
	//window->LaunchForm( new LoginForm( ) );

	while( window->PollEvents( ) )
	{
		render->Begin( params.transparency_key );
		window->PaintForms( );
		render->Present( );
		window->TickForms( );
		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
	}*/
	
	// TODO:
	// Free resources... kekekke
	/*srand( 123456u );
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
	std::cin.get( );*/
}

