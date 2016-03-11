#include "Form.h"
#include "Renderer\Renderer.h"
#include "UI\Canvas.h"
#include "UI\Component.h"
#include "UI\Window.h"
#include "UI\RichLabel.h"
#include "UI\Button.h"
#include "Stylesheet\Style.h"
#include "../Window/Win32Window.h"



namespace Graphics {

	void Form::DoTick()
	{
		dx::AsyncGuard guard{ _task_kpr };
		auto now = dx::Clock::now( );
		for ( auto it = _tasks.begin( ); it < _tasks.end( ); ++it )
		{
			if ( it->do_task_if_time( now ) )
			{
				_tasks.erase( it );
				break;
			}
		}
		Tick( );
	}
	void Form::Paint(Renderer::D9Renderer *r)
	{
		// PAINT CUSTOM THINGS.
	}

	void Form::PaintSafe( Renderer::D9Renderer *r )
	{
		if ( _win32window->isMinimized( ) )
			return;
		Paint( r );
	}

	bool Form::Event(WindowEventParams params)
	{
		return true;
	}

	void Form::Release()
	{
		if (_window)
			_window->Release( );
		delete _window, _canvas;
	}

	void Form::addTask(void * _Data, const std::chrono::time_point<std::chrono::high_resolution_clock>& _Time, const std::function<void(void*)>& _Task)
	{
		dx::AsyncGuard guard{ _task_kpr };
		_tasks.push_back( Task{ _Data, _Task, _Time } );
	}

	pointer<UI::Window> Form::Dialog(const DialogType &type, const std::initializer_list<UI::Text>& text, const Utils::String & title, const Utils::String & name, std::function<void(DialogResult, pointer<UI::Window>, pointer<UI::Canvas>)> event)
	{
		typedef std::function<void(DialogResult, pointer<UI::Window>, pointer<UI::Canvas>)> EventPf;

		auto render = _win32window->getRenderer( );
		auto window = new UI::Window( );
		window->setText( title );
		window->setName( name );
		window->setFont( "CaviarT" );
		window->setPadding( { 300, 300 } );
		
		///<ugly>
		auto __ignore = new EventPf( );
		__ignore->swap( event );
		window->setUserdata( (void*)__ignore );
		window->OnRelease( ) += []( UI::Component *sender ) { delete (sender->getUserdata( )); return true; };
		///</ugly>


		if ( !render->fontAt( "CaviarT" ) )
			render->PrepareFont( "CaviarT", "Caviar Dreams", 25, 75 );

		// Message 
		auto message = new UI::RichLabel( );
		for (auto &x : text)
			*message += x;
		message->setName( name + "_message" );
		message->setFont( "Caviar" );
		message->setPadding( { 25, 55 } );
		if ( !render->fontAt( "Caviar" ) )
			render->PrepareFont( "Caviar", "Caviar Dreams", 20, 75 );
		auto dummy = message->getTextSize_unsafe( render );
		window->setSize( message->getTextSize_unsafe( render ) + Vector2{ 150, 125 } );
		if ( window->getSize( ) < Vector2{ 300, 300 } )
			window->setSize( { 400, 400 } );

		// Dialog specials...
		if ( type == Dialog_continue )
		{
			// Continue button
			auto button = new UI::Button( );
			button->setName( name + "_continue" );
			button->setText( "Continue" );
			button->setFont( "Caviar" );
			button->setAllignment( UI::Middle );
			
			auto window_size = window->getSize( );
			button->setPadding( { window_size.x - 105, window_size.y - 35  } );
			button->setSize( { 100, 30 } );
			button->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if ( event )
					event(
						  Result_Continue,
						  ccast<UI::Window*>( sender->getParent( ) ),
						  canvas
						);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};

			window->addChild( button );
		}
		else if ( type == Dialog_ok )
		{
			// Ok button
			auto button = new UI::Button( );
			button->setName( name + "_ok" );
			button->setText( "Okay" );
			button->setFont( "Caviar" );
			button->setAllignment( UI::Middle );
			
			auto window_size = window->getSize( );
			button->setPadding( { window_size.x - 85, window_size.y - 35  } );
			button->setSize( { 80, 30 } );
			button->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if (event)
					event(
					  Result_Continue,
					  ccast<UI::Window*>( sender->getParent( ) ),
					  canvas
					);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};

			window->addChild( button );
		}
		else if ( type == Dialog_yes_no )
		{

			// YEs button
			auto yes = new UI::Button( );
			yes->setName( name + "_yes" );
			yes->setText( "Yes" );
			yes->setFont( "Caviar" );
			yes->setAllignment( UI::Middle );
			
			auto window_size = window->getSize( );
			yes->setPadding( { window_size.x - 70, window_size.y - 35  } );
			yes->setSize( { 65, 30 } );
			yes->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if ( event )
					event(
					  Result_Continue,
					  ccast<UI::Window*>( sender->getParent( ) ),
					  canvas
					);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};

			// No button
			auto no = new UI::Button( );
			no->setName( name + "_no" );
			no->setText( "No" );
			no->setFont( "Caviar" );
			no->setAllignment( UI::Middle );
			
			
			no->setPadding( yes->getPadding( ) - Vector2{ 70, 0 } );
			no->setSize( { 65, 30 } );
			no->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if ( event )
					event(
					  Result_Continue,
					  ccast<UI::Window*>( sender->getParent( ) ),
					  canvas
					);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};


			window->addChild( yes );
			window->addChild( no );
		}
		else if ( type == Dialog_yes_no_cancel )
		{

			// Cancel button
			auto cancel = new UI::Button( );
			cancel->setName( name + "_cancel" );
			cancel->setText( "Cancel" );
			cancel->setFont( "Caviar" );
			cancel->setAllignment( UI::Middle );

			auto window_size = window->getSize( );
			cancel->setPadding( { window_size.x - 105, window_size.y - 35 } );
			cancel->setSize( { 100, 30 } );
			cancel->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if ( event )
					event(
					  Result_Continue,
					  ccast<UI::Window*>( sender->getParent( ) ),
					  canvas
					);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};

			// Yes button
			auto yes = new UI::Button( );
			yes->setName( name + "_yes" );
			yes->setText( "Yes" );
			yes->setFont( "Caviar" );
			yes->setAllignment( UI::Middle );
			
			yes->setPadding( cancel->getPadding( ) - Vector2{ 105, 0 } );
			yes->setSize( { 65, 30 } );
			yes->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if ( event )
					event(
					  Result_Continue,
					  ccast<UI::Window*>( sender->getParent( ) ),
					  canvas
					);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};

			// No button
			auto no = new UI::Button( );
			no->setName( name + "_no" );
			no->setText( "No" );
			no->setFont( "Caviar" );
			no->setAllignment( UI::Middle );
			
			
			no->setPadding( yes->getPadding( ) - Vector2{ 70, 0 } );
			no->setSize( { 65, 30 } );
			no->OnComponentClicked( ) += [window = window, canvas = getCanvas( ), thisptr = this]( UI::Component *sender, Vector2 )mutable->bool
			{
				auto event = *ccast<EventPf*>( sender->getParent( )->getUserdata( ) );
				if ( event )
					event(
					  Result_Continue,
					  ccast<UI::Window*>( sender->getParent( ) ),
					  canvas
					);
				auto idx = canvas->Search(  [window = window](pointer<UI::Window> x)
										    {
												if ( x->getName( ) == window->getName( ) )
													return true;
												return false;
										    } );
				canvas->erase( idx );
				if ( canvas->getWindow( 0 ) != nullptr )
					canvas->getWindow( 0 )->setTopMost( true );

				thisptr->addTask( window, 
								  dx::Clock::now( ) + std::chrono::milliseconds( 500 ),
								  []( void* data ){ auto window = (UI::Window*)data; delete window; } );
				return true;
			};


			window->addChild( cancel );
			window->addChild( yes );
			window->addChild( no );
		}
		
		
		window->addChild( message );
		window->setStylesheet( Style::DEFAULT_STYLE );

		_canvas->add( window );

		if ( _canvas->TopMost( ) )
			_canvas->TopMost( )->setTopMost( false );
		window->setTopMost( true );
		return window;
	}

	pointer<UI::Window> Form::Dialog(const DialogType & _Type, const std::initializer_list<UI::Text>& _Text, const Utils::String & _Title, const Utils::String & _Name, std::function<void(DialogResult, pointer<UI::Window>, pointer<UI::Canvas>)> _Event, pointer<UI::Window> _Window)
	{
		auto dialog = Dialog( _Type, _Text, _Title, _Name, _Event );
		dialog->OnRelease( ) += [ window = _Window ]( UI::Component *sender )
		{
			if ( window )
				window->setEnabled( true );
			return true;
		};
		if ( _Window )
			_Window->setEnabled( false );
		return dialog;
	}

	Win32Window * Form::getWin32()
	{
		return _win32window;
	}

	UI::Window * Form::getWindow()
	{
		return _window;
	}

	UI::Canvas * Form::getCanvas()
	{
		return _canvas;
	}

	Task::Task(void * _Data, const function & _Func, const time_point & _Time)
		: _data( _Data ), _func( _Func ), _time( _Time )
	{
	}

	bool Task::do_task_if_time(const time_point & _Point)
	{
		if ( _Point.time_since_epoch( ) > _time.time_since_epoch( ) )
		{
			if ( _func )
				_func( _data );
			return true;
		}
		return false;
	}
}