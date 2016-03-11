#pragma once
#include "lib.h"
#include "../string.h"

begin_FILEIO


class Path
{
private:
	__LIB String _path;
public:
	Path( );
	Path( const __LIB String &_Path );
	Path( const char *_Path );

	operator const char*( ) const;
public: // Sub-paths
	__FILEIO Path Previous( ) const;
	__FILEIO Path UptoPrevious( ) const;
	__FILEIO Path Root( ) const;
	__FILEIO Path Filename( ) const;
	__FILEIO Path Extension( ) const;
	std::vector<__FILEIO Path> Branches( ) const;

public: // Editors
	__FILEIO Path& remove_extension( );
	__FILEIO Path& remove_filename( );
	__FILEIO Path& remove_directories( );

public: // booleans
	bool has_extension( ) const;
	bool has_filename( ) const;
	bool has_branches( ) const;
	bool is_directory( ) const;
};

bool DirectoryExists( const __FILEIO Path &_Path );
bool exists( const __FILEIO Path &_Path );




end_FILEIO