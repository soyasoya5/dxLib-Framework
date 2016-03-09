#include "Path.h"

using namespace dx;

FileIO::Path::Path()
	: _path( )
{
}

FileIO::Path::Path(const Utils::String & _Path)
	: _path( _Path )
{
}

FileIO::Path::Path(const char * _Path)
	: _path( _Path )
{
}

FileIO::Path::operator const char*() const
{
	return _path.c_str( );
}

Path FileIO::Path::Previous() const
{
	if ( !has_branches( ) )
		return *this;
	auto brs = Branches( );
	if ( brs.size( ) < 2 )
		return *this;
	return brs[ brs.size( ) - 2 ];
}

Path FileIO::Path::UptoPrevious() const
{
	return Path(*this).remove_filename( ).remove_extension( );
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
	auto pos = _path.find_last_of( "\\" );
	if ( pos == String::bad )
		return *this;
	return _path.substr( pos + 1 );
}

Path FileIO::Path::Extension() const
{
	if ( !has_extension( ) )
		return "";
	auto pos = _path.find_last_of( "." );
	return _path.substr( pos );
}

std::vector<Path> FileIO::Path::Branches() const
{
	std::vector<Path> ret;
	for ( auto &x : _path.split( "\\" ) )
		ret.push_back( Path( x ) );
	return ret;
}

Path & FileIO::Path::remove_extension()
{
	auto pos = _path.find_last_of( '.' );
	if ( pos == String::bad ) return *this; // return right away...
	_path = _path.substr( 0, pos );
	return *this;
}

Path & FileIO::Path::remove_filename()
{
	auto pos = _path.find_last_of( '\\' );
	if ( pos == String::bad ) return *this; // return right away...
	_path = _path.substr( 0, pos );
	return *this;
}

Path & FileIO::Path::remove_directories()
{
	auto last = _path.find_last_of( '\\' );
	if ( last == String::bad ) return *this;
	_path.erase( 0, last + 1 );
	return *this;
}

bool FileIO::Path::has_extension() const
{
	return _path.find( '.' ) != String::bad;
}

bool FileIO::Path::has_filename() const
{
	return has_extension( );
}

bool FileIO::Path::has_branches() const
{
	return _path.find( '\\' ) != String::bad;
}

bool FileIO::Path::is_directory() const
{
	return !has_extension( );
}

bool FileIO::DirectoryExists(const Path & _Path)
{
	auto attrib = GetFileAttributes( _Path );
	return !(attrib & INVALID_FILE_ATTRIBUTES) && attrib & FILE_ATTRIBUTE_DIRECTORY;
}

bool FileIO::exists(const Path & _Path)
{
	auto attrib = GetFileAttributes( _Path );
	return !(attrib & INVALID_FILE_ATTRIBUTES) && !(attrib & FILE_ATTRIBUTE_DIRECTORY);
}
