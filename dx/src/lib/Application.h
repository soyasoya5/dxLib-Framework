#pragma once
#include "lib.h"
#include "../dx.h"
#include "string.h"
#include "event.h"
#include "async.h"

begin_GRAPHICS class Window; end_GRAPHICS

begin_LIB

// Applicaiton class
class Application
{
private:
	Application( );

public:
	///<summary>
	/// Create the application.
	///</summary>
	static Application *Create( );

	///<summary>
	/// Returns wether or not the application has been created.
	///</summary>
	static bool isCreated( );

	///<summary>
	/// Returns a pointer to the created application.
	///</summary>
	static Application *get( );

	///<summary>
	/// Sets the last error of the application.
	///</summary>
	static void setLastError( const int &errc );

	///<summary>
	/// Gets the last error of the application.
	///</summary>
	static int getLastError( );

public:

	///<summary>
	/// Run this application.
	///</summary>
	int run( );

	///</summary>
	/// Exit this application. (This is the good way to exit, this will release all necessary resources etc) 
	///</summary>
	void exit( );

	///<summary>
	/// Register a window to this application, this is automatically done by Window::Create.
	///</summary>
	void RegisterWindow( ::dx::lib::Graphics::Window *window );

	///<summary>
	/// Unregister a window, automatically called by destructor of Window
	///</summary>
	void UnregisterWindow( ::dx::lib::Graphics::Window *window );

	///<summary>
	/// Set the tick rate of this application, in milliseconds.
	///</summary>
	void setTickRate( const int &rate );

	///<summary>
	/// Sets the clipboard data
	///</summary>
	void setClipboard( const String &data );

	///<summary>
	/// Gets the clipboard data
	///</summary>
	String getClipboard( ) const;

	///<summary>
	/// Called every tick.
	///</summary>
	Event<void(Application*)> &OnTick( );

	template<typename _Callable>
	void BeginInvoke( _Callable&&callable )
	{
		AsyncGuard guard{ kpr_ };
		this->invokes_.emplace_back( callable );
	}

private:
	bool running_;
	int tick_;
	std::vector<Graphics::Window*> windows_;
	std::vector<function<void()>> invokes_;
	static int ilasterr_;
	Event<void(Application*)> _OnTick;
	AsyncKeeper kpr_;
};




end_LIB

