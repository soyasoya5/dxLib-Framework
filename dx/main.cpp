//#define DONT_LINK_GRAPHICS
#include "src\api"
#include <iomanip>
#include <array>

#pragma warning( disable : 4996 )
int main( )
{
	//FreeConsole( );
	// Create application
	auto appl = dx::Application::Create( );

	// Set tick rate
	appl->setTickRate( 1 );

	dx::File file;
	file.loaded = false;
	file.name = "main.cpp";


	return appl->run( );
}
