#pragma once
#include "lib.h"
#include "../dx.h"
#include "string.h"

begin_GRAPHICS class Window; end_GRAPHICS

begin_LIB

// Applicaiton class
class Application
{
private:
	Application( );

public:
	static Application *Create( );
	static bool isCreated( );
	static Application *get( );
	static void setLastError( const int &_Errc );
	static int getLastError( );

public:
	int run( );
	void exit( );
	void RegisterWindow( __GRAPHICS Window *_Window ); // Called by Window::Create
private:
	bool _running;
	std::vector<Graphics::Window*> _windows;
	static int _ilasterr;
};




end_LIB

