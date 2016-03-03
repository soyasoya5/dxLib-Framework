#pragma once
#include "../dx.h"
#include "string.h"


namespace Utils {


	enum Log_t : uint
	{
		None, /* Ignored */
		Info, /* Provide SHORT information */
		Verbose, /* A very lengthy information log. */
		Warning, /* Something wrong happened, doesn't really matter though. */
		Debug, /* Debug information */
		Error, /* Something wrong happened, slightly serious but the application can still run. */
		Fatal, /* Something wrong happened, the application may hault. */
	};


	// Loggers 'severity' level.
	enum Severity_t : uint
	{
		Debug_mode = 1, // Same as high but with debug
		High_mode, // Fatal/Error/Warnign/Verbose/Info
		Medium_mode, // Fatal/Error/Warning
		Low_mode, // Fatal/Error
	};

	class Logger
	{
	private:
		Utils::String _fileName;
		std::ofstream _file;
		bool _op;
		Severity_t _sev;

		bool checkLog( const Log_t &_Type );
	public:
		Logger( );
		Logger( const Utils::String &_Filename, const Severity_t &_Severity );

		void open( );
		bool is_open( ) const;
		void close( );
		bool Log( const Utils::String& _Msg, const Log_t& _Type );
		bool Log( const std::string& _Msg, const Log_t& _Type );
		bool Log( const char* _Msg, const Log_t& _Type );

	public:
		static Utils::String date( );
		static Utils::String SeverityToString( const Severity_t &_Severity );
		static Utils::String LogToString( const Log_t &_Type );

	public:
		void setFile( const Utils::String &_Filename );
		void setSeverity( const Severity_t &_Severity );

		Utils::String getFile( ) const;
		Utils::Severity_t getSeverity( ) const;
	};

}