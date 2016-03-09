#pragma once
#include "../Utils/string.h"

namespace FileIO {

	class Path
	{
	private:
		Utils::String _path;
	public:
		Path( );
		Path( const Utils::String &_Path );
		Path( const char *_Path );

		operator const char*( ) const;
	public: // Sub-paths
		Path Previous( ) const;
		Path Root( ) const;
		Path Filename( ) const;
		Path Extension( ) const;
		std::vector<Path> Branches( ) const;

	public: // Editors
		Path& remove_extension( );
		Path& remove_filename( );
		Path& remove_directories( );

	public: // booleans
		bool has_extension( ) const;
		bool has_filename( ) const;
		bool has_branches( ) const;
		bool is_directory( ) const;
	};

	bool DirectoryExists( const Path &_Path );
	bool exists( const Path &_Path );

}