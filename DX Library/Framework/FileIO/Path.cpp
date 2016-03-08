#include "Path.h"

using namespace dx;


Path FileIO::Path::Previous() const
{
	auto pos = _path.find_last_of( "\\" );
	if ( pos == String::bad )
		return "";
	return _path.substr( pos + 1 );
}

Path FileIO::Path::Root() const
{
	auto pos = _path.find( "\\" );
	if ( pos == String::bad )
		return "";
	return _path.substr( { 0, pos } );
}

Path FileIO::Path::Filename() const
{
	
}

std::vector<Path> FileIO::Path::Branches()
{
	std::vector<Path> ret;
	auto vec = _path.split( "\\" );
	for ( auto &x : vec )
		ret.push_back( Path( x ) );
	return ret;
}
