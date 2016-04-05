#pragma once
#include "lib.h"
#include "../dx.h"
#include "string.h"
#include "event.h"

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
	static void setLastError( const int &_Errc );

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
	void RegisterWindow( __GRAPHICS Window *_Window );

	///<summary>
	/// Set the tick rate of this application, in milliseconds.
	///</summary>
	void setTickRate( const int &_Rate );

	///<summary>
	/// Called every tick.
	///</summary>
	__LIB Event<void(Application*)> &OnTick( );
private:
	bool _running;
	int _tick;
	std::vector<Graphics::Window*> _windows;
	static int _ilasterr;
	__LIB Event<void(Application*)> _OnTick;
};




end_LIB

