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
#include "Framework\Graphics\UI\Scrollbar.h"
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



bool readBinaryFile( byte** _Buffer, uint &_Length, const dx::String &_File )
{
	std::ifstream file( _File.c_str( ) );
	if ( !file.good( ) )
		return false;
	file.seekg( 0, std::ios::end );
	auto size = file.tellg( );
	file.seekg( 0, std::ios::beg );

	*_Buffer = new byte[size];
	file.read( (char*)*_Buffer, size );
	file.close( );

	_Length = size;
	return true;
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
	dx::Label *_current;
	dx::Trackbar *_progress;
	dx::Label *_time;
	dx::Label *_state;

	dx::BackgroundTask *_task;
	bool _searching, _paused, _halted;
	uint _index;
	std::vector<dx::Pattern> _patterns;
	uint _avgLen;
	dx::Module *_fileA, *_fileB;
	dx::InternalImpl* _mem;
	float dt;
	
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

		// Misc
		_task = new dx::BackgroundTask( );
		_task->OnComplete( ) += BIND_METHOD_1( &PatternScanner::OnCompletedTask, this );


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
		_stop->setText( "Stop" );
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

		// 
		
		// Current
		_current = new dx::Label( );
		_current->setText( "Nothing" );
		_current->setFont( "Caviar" );
		_current->setPadding( { 0, 520 } );

		// Progress
		_progress = new dx::Trackbar( );
		_progress->setSize( { 200, 30 } );
		_progress->setBarSize( { 10, 0 } );
		_progress->setPadding( { 550, 55 } );
		_progress->setType( dx::Horizontal );
		_progress->setMax( 100 );
		_progress->setMin( 0 );
		_progress->setScroll( 0 );
		_progress->UpdateBar( );
		_progress->UpdateScroll( );
		_progress->setEnabled( false );
		
		// time
		_time = new dx::Label( );
		_time->setText( "Time: 0.0" );
		_time->setFont( "Caviar" );
		_time->setPadding( { 550, 90 } );


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
		_tab1->addChild( _current );
		_tab1->addChild( _progress );
		_tab1->addChild( _time );

		// Tab Two
		//_tab2->addChild( _errors );
		_tab2->addChild( _logs );

		_window->setStylesheet( Style::DEFAULT_STYLE );
	
	
		_mem = new dx::InternalImpl( );
		_mem->Setup( "" );

	}

	bool OnCompletedTask( dx::BackgroundTask *task )
	{
		auto cTask = _current->getName( );
		if ( cTask == "Compiling" )
		{
			_current->setText( "Performing analysis. THIS MAY TAKE A WHILE." );
			_current->setName( "Scanning" );
			_task->Start( BIND_METHOD_1( &PatternScanner::perform_analysis, this ) );
		}
		if ( cTask == "Scanning" )
		{
			//_state->setText( "Nothing" );
			_current->setText( "Nothing" );
			_current->setName( "Nothing" );
			_time->setText( "Time: 0.0" );
			_halted = true;
		}

		return true;
	}

	bool Scan( dx::Component *sender, Vector2 area )
	{
		dx::Path _A( _file1->getText( ) ), _B( _file2->getText( ) );
		if ( !_A.has_extension( ) || !_B.has_extension( ) )
			return	Dialog( 
							dx::Dialog_continue, 
							{ dx::Text( "Files must have extension (Be a folder)", Colors::Red ) }, 
							"Error", "scan_error",
							nullptr,
						    this->_window
							);
		_halted = false;
		start_scan_process( _A, _B );
		return true;
	}

	bool Pause( dx::Component *sender, Vector2 area )
	{
		static Utils::String str = "";
		if ( _paused )
		{
			_current->setText( str );
		} else
		{
			str = _current->getText( );
			_current->setText( "Paused" );
		}
		
		_paused = !_paused;
		return true;
	}

	bool Stop( dx::Component *sender, Vector2 area )
	{
		_halted = true;
		_task->Halt( );
		return true;
	}

	void start_scan_process( dx::Path &_A, dx::Path &_B )
	{
		if ( _fileA ) {
			delete[_fileA->Size( )] ( (void*)_fileA->Image( ) );
			delete _fileA; 
		}
		if ( _fileB ) {
			delete[_fileB->Size( )] ( (void*)_fileB->Image( ) );
			delete _fileB;
		}

		byte *aBuf, *bBuf;
		uint lenA, lenB;
		
		_current->setText( "Reading file A into memory" );
		if ( !readBinaryFile( &aBuf, lenA, _A.operator const char *( ) ) ) {
			this->Dialog( 
						 dx::Dialog_ok, 
						 { dx::Text( _file1->getText( ), Colors::White ),
						   dx::Text( " does not exist.", Colors::Red ) },
						 "Error",
						 "error",
						 nullptr,
						 this->_window );
			this->addTask( this->_current, dx::Clock::now( ), []( void* data ) { auto curr = (dx::Label*)data; curr->setText( "Nothing" ); curr->setName( "Nothing" ); } );
			return;
		}

		_current->setText( "Reading file B into memory" );
		if ( !readBinaryFile( &bBuf, lenB, _B.operator const char *( ) ) ) {
			this->Dialog( 
						 dx::Dialog_ok, 
						 { dx::Text( _file2->getText( ), Colors::White ),
						   dx::Text( " does not exist.", Colors::Red ) },
						 "Error",
						 "error",
						 nullptr,
						 this->_window );
			return;
		}
		
		_current->setText( "Computing average length" );
		_current->setName( "Computing" );
		_avgLen = ( (lenA + lenB / (lenB & lenA)) / 3541 ) % 55 + 5;
		_index = 0;

		_current->setText( "Indexing modules" );
		_current->setName( "Indexing" );
		_fileA = new dx::Module( (ulong)aBuf, lenA, _A.operator const char *( ) );
		_fileB = new dx::Module( (ulong)bBuf, lenB, _B.operator const char *( ) );

		_current->setText( "Compiling patterns, please wait" );
		_current->setName( "Compiling" );
		_task->Start( BIND_METHOD_1( &PatternScanner::compile_patterns_task, this ) );
	}

	void compile_patterns_task( dx::AsyncKeeper &_Kpr )
	{
		dx::AsyncGuard guard{ _Kpr };
		auto a_ptr = (byte*)_fileA->Image( );
		auto length = min( _fileA->Size( ), _fileB->Size( ) );

		for ( auto ptr = a_ptr; (ptr + _avgLen) < (a_ptr + length); ++ptr )
		{
			while( _paused ) std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
			this->_patterns.push_back( ComposePattern( &ptr, _mem, _fileB, _avgLen ) );
		}
	}

	void perform_analysis( dx::AsyncKeeper &_Kpr )
	{
		dx::AsyncGuard guard{ _Kpr };

		dx::Timer timer;
		uint count = 0, accuracy = 0;
		dt = 0.0f;
		float progress = 0;
		
		float last_dt = 0.0f;
		for ( auto &x : _patterns )
		{
			while( _paused ) std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );

			progress = (float)((float)accuracy / (float)_patterns.size( )) * 100.0f;
			
			if ( dt - last_dt > 0.1 )
				this->addTask(
						&progress,
						dx::Clock::now( ),
						BIND_METHOD_1( &PatternScanner::special_task_lemo, this ) );
			
			++count;
			dt += timer.GetDeltaTime( );
			auto addr = x.Scan( );
			if ( addr.IsNullOrZero( ) )
				continue;
			++accuracy;
		}


		float ac = (float)( (float)accuracy / (float)_patterns.size( ) ) * (float)100;
		Dialog( 
				dx::Dialog_ok, 
				{ dx::Text("Completed analysis\n"), 
				  dx::Text( "The files are ", Colors::Green ), 
				  dx::Text( dx::to_string( ((int)ac) + 1 ), Colors::Gold ),
				  dx::Text( "% accurate.\n", Colors::Green ),
				  dx::Text( "Test took ", Colors::Green ),
				  dx::Text( dx::to_string( dt ), Colors::Gold ),
				  dx::Text( " seconds to complete. (or ", Colors::Green ),
				  dx::Text( dx::to_string( std::chrono::duration_cast<std::chrono::minutes>( std::chrono::seconds( (int)dt ) ).count( ) ), Colors::Gold ),
				  dx::Text( " minutes)\n", Colors::Green ) },
				"Completed", 
				"scan_complete", 
				nullptr,
				this->_window );
	}

	void special_task_lemo( void *data )
	{
		if (_paused)
			return;
		if (_halted)
			return;
		float prog = *(float*)data;
		_progress->setScroll( ( prog ) );
		_progress->UpdateBar( );
		_progress->UpdateScroll( );
		_time->setText( "Time: " + dx::to_string( dt ) );
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
	std::cout << "Thread concurrency: " << std::thread::hardware_concurrency( ) << std::endl;
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
	}
	
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

