#pragma once
#include "lib.h"
#include "../string.h"

begin_FILEIO


class Path
{
private:
	__LIB String _path;
public:

	///<summary>
	/// Empty constructor
	///</summary>
	Path( );

	///<summary>
	/// Construct this Path with '_Path' as the internal path.
	///</summary>
	Path( const __LIB String &_Path );

	///<summary>
	/// Construct this Path with '_Path' as the internal path.
	///</summary>
	Path( const char *_Path );

	///<summary>
	/// Return a C null-terminated string.
	///</summary>
	operator const char*( ) const;

	///<summary>
	///	Return a DX String.
	///</summary>
	const __LIB String & string( );

	///<summary>
	/// Return a C null-terminated string.
	///</summary>
	const char *c_str( );
public: // Sub-paths
	///<summary>
	/// Get the Previous Branch, e.g A/B/C/D would return 'C'.
	///</summary>
	__FILEIO Path Previous( ) const;

	///<summary>
	/// Get all the branches upto the previous branch, e.g A/B/C/D would return 'A/B/C'.
	///</summary>
	__FILEIO Path UptoPrevious( ) const;

	///<summary>
	/// Get the Root branch. e.g A/B/C/D would return 'A'.
	///</summary>
	__FILEIO Path Root( ) const;

	///<summary>
	///	Get the file name. e.g A/B/C/D.ext would return 'D.ext'.
	///</summary>
	__FILEIO Path Filename( ) const;

	///<summary>
	/// Get the extension of the filename. e.g A/B/C/D.ext would return '.ext'
	///</summary>
	__FILEIO Path Extension( ) const;

	///<summary>
	///	Return all the branches INCLUDING the file name (If it has one)
	///</summary>
	std::vector<__FILEIO Path> Branches( ) const;
	
	
public: // Editors
	///<summary>
	///	Remove the extension if it has one.
	///</summary>
	__FILEIO Path& remove_extension( );

	///<summary>
	/// Remove the file name if it has one.
	///</summary>
	__FILEIO Path& remove_filename( );

	///<summary>
	/// Remove all branches if it has them.
	///</summary>
	__FILEIO Path& remove_directories( );

public: // booleans
	///<summary>
	/// Return true if extension is equal to '_Extension'.
	///</summary>
	bool extension_is( const __LIB String &_Extension ) const;

	///<summary>
	///	Returns true if this Path has an extension.
	///</summary>
	bool has_extension( ) const;

	///<summary>
	/// Returns true if this Path has a filename.
	///</summary>
	bool has_filename( ) const;

	///<summary>
	/// Returns true if this Path has branches.
	///</summary>
	bool has_branches( ) const;

	///<summary>
	/// Returns true if this is a directory.
	///</summary>
	bool is_directory( ) const;
};

///<summary>
/// Returns true if Directory '_Path' exists.
///</summary>
bool DirectoryExists( const __FILEIO Path &_Path );

///<summary>
/// Returns true if file '_Path' exists.
///</summary>
bool exists( const __FILEIO Path &_Path );




end_FILEIO