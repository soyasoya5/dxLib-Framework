#pragma once
#include "lib.h"
#include "../dx.h"

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

public:
	int run( );
	void exit( );

	void RegisterWindow( __GRAPHICS Window *_Window ); // Called by Window::Create
private:
	bool _running;
	std::vector<Graphics::Window*> _windows;
};




end_LIB

