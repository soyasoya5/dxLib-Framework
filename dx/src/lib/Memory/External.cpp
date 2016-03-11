#include "External.h"
#include "Handle.h"
#include "Module.h"
#include <TlHelp32.h>

begin_MEMORY

ExternalImpl::ExternalImpl()
{
	this->_handle = new Handle<>( );
	_handle->get( ) = INVALID_HANDLE_VALUE;
	_handle->isWinapi( ) = true;
}

ExternalImpl::~ExternalImpl()
{
	delete _handle;

}

bool ExternalImpl::Setup(const __LIB String & _Proc)
{
	Detach( );
	Handle<> snap;
	snap.isWinapi( ) = true;
	snap.get( ) = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	PROCESSENTRY32 *lppe = &PROCESSENTRY32();
	lppe->dwSize = sizeof( PROCESSENTRY32 );

	Process32First( snap.get( ), lppe );
	while( true )
	{
		if ( _Proc == lppe->szExeFile )
		{
			this->_pID = lppe->th32ProcessID;
			this->_can = true;
			this->_proc = _Proc;
			this->_handle->get( ) = OpenProcess( PROCESS_ALL_ACCESS, false, this->_pID );
			return true;
		}
		if ( !Process32Next( snap.get( ), lppe ) )
			break;
	}
	return false;
}

bool ExternalImpl::Detach()
{
	if ( _handle )
		delete _handle;
	this->_handle = new Handle<>( );
	_handle->get( ) = INVALID_HANDLE_VALUE;
	_handle->isWinapi( ) = true;
	return true;
}

bool ExternalImpl::SetupModules()
{
	if ( !_can )
		return false;
	DetachModules( );
	Handle<> snap;
	snap.isWinapi( ) = true;
	snap.get( ) = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, this->_pID );

	MODULEENTRY32 *lpme = &MODULEENTRY32( );
	lpme->dwSize = sizeof( MODULEENTRY32 );

	Module32First( snap.get( ), lpme );
	while( true )
	{
		Module module{ (ulong)( lpme->modBaseAddr ), lpme->modBaseSize, lpme->szModule };
		this->_modules.push_back( module );
		if ( !Module32Next( snap.get( ), lpme) )
			return false;
	}
	return true;
}

bool ExternalImpl::DetachModules()
{
	_modules.clear( );
	_modules.push_back( Module( 0x0, 0x0, "_Dummy" ) );
	return true;
}

bool ExternalImpl::read_bytes(const Module & _Module, const uint & _Offset, byte * _Buff, const uint & _Size)
{
	return ReadProcessMemory( this->_handle->get( ), (void*)( _Module + _Offset ), _Buff, _Size, nullptr );
}

bool ExternalImpl::write_bytes(const Module & _Module, const uint & _Offset, byte * _Buff, const uint & _Size)
{
	return WriteProcessMemory( this->_handle->get( ), (void*)( _Module + _Offset ), _Buff, _Size, nullptr );;
}


end_MEMORY