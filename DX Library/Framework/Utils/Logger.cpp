#include "Logger.h"

#pragma warning(push)
#pragma warning( disable : 4996 )


bool Utils::Logger::checkLog(const Log_t &type)
{
	if ( _sev == Severity_t::High_mode )
		return type == Fatal || type == Error || type == Warning || type == Verbose || type == Info;
	else if ( _sev == Debug_mode )
		return true;
	else if ( _sev == Medium_mode )
		return type == Fatal || type == Error || type == Warning;
	else if ( _sev == Low_mode )
		return type == Fatal || type == Error;
	return false;
}

Utils::Logger::Logger()
	: _fileName(""), _op(false), _sev(Debug_mode)
{
}

Utils::Logger::Logger(const Utils::String &f, const Severity_t &s)
	: _fileName(f), _op(true), _sev(s)
{
}

void Utils::Logger::open()
{
	_op = true;
}

bool Utils::Logger::is_open() const
{
	return _op;
}

void Utils::Logger::close()
{
	_op = false;
}

bool Utils::Logger::Log(const Utils::String &msg, const Log_t &type)
{
	return Log( msg.c_str( ), type );
}

bool Utils::Logger::Log(const std::string &msg, const Log_t &type)
{
	return Log( msg.c_str( ), type );
}

bool Utils::Logger::Log(const char *msg, const Log_t &type)
{
	if ( !_op )
		return false;
	
	if ( !checkLog( type ) )
		return false;

	_file.open( _fileName.c_str( ), std::ios::app );
	if ( !_file.is_open( ) )
		return false;
	_file << "[" << LogToString(type) << "]" << date( ) << " " << msg << std::endl;
	_file.close( );
	return true;
}

Utils::String Utils::Logger::date()
{
	time_t rawtime = 0;
	char buffer[80];
	std::time(&rawtime);
	auto timeinfo = std::localtime(&rawtime);
	std::strftime(buffer, 80, "[%d-%m-%Y %I:%M:%S]", timeinfo);
	return buffer;
}

Utils::String Utils::Logger::SeverityToString(const Severity_t &sev)
{
	switch (sev)
	{
	case Debug_mode:
		return "Debug";
	case High_mode:
		return "High";
	case Medium_mode:
		return "Medium";
	case Low_mode:
		return "Low";
	default:
		return "none";
	}
}

Utils::String Utils::Logger::LogToString(const Log_t &log)
{
	switch (log)
	{
	case Info:
		return "Info";
	case Verbose:
		return "Verbose";
	case Warning:
		return "Warning";
	case Debug:
		return "Debug";
	case Error:
		return "Error";
	case Fatal:
		return "Fatal";
	default:
		return "none";
	}
}

void Utils::Logger::setFile(const Utils::String &fs)
{
	_fileName = fs;
}

void Utils::Logger::setSeverity(const Severity_t &s)
{
	_sev = s;
}


Utils::String Utils::Logger::getFile() const
{
	return _fileName;
}

Utils::Severity_t Utils::Logger::getSeverity() const
{
	return _sev;
}


#pragma warning(pop)