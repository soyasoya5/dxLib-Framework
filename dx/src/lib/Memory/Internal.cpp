#include "Internal.h"
#include "Handle.h"
#include "Module.h"
#include <Windows.h>
#include <TlHelp32.h>

begin_MEMORY

InternalImpl::InternalImpl()
{
	_handle = new Handle<>();
	_handle->isWinapi( ) = true;
	_handle->get( ) = INVALID_HANDLE_VALUE;
	_modules.push_back( Module( 0x0, 0x0, "_Dummy" ) );
}

InternalImpl::~InternalImpl()
{
	delete _handle;
}

bool InternalImpl::Setup(const __LIB String & _Proc)
{
	Detach( );
	_handle->get( ) = (void*)0x00CA;
	_handle->isWinapi( ) = false;
	_can = true;
	_pID = GetCurrentProcessId( );
	_proc = _Proc;
	return true;
}

bool InternalImpl::Detach()
{
	_handle->get( ) = INVALID_HANDLE_VALUE;
	_can = false;
	_pID = 0;
	_proc = "";
	return false;
}

bool InternalImpl::SetupModules()
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

bool InternalImpl::DetachModules()
{
	_modules.clear( );
	_modules.push_back( Module( 0x0, 0x0, "_Dummy" ) );
	return true;
}

bool InternalImpl::read_bytes(const Module & _Module, const uint & _Offset, byte * _Buff, const uint & _Size)
{
	if ( _Module.isDummy( ) )
		return false;
	try {
		for ( uint i = 0; i < _Size; ++i )
			*(_Buff + i) = *(byte*)( _Module + _Offset + i );
		return true;
	}
	catch ( std::exception e ) { };
	return false;
}

bool InternalImpl::write_bytes(const Module & _Module, const uint & _Offset, byte * _Buff, const uint & _Size)
{
	if ( _Module.isDummy( ) )
		return false;
	try {
		for ( uint i = 0; i < _Size; ++i )
			 *(byte*)( _Module + _Offset + _Size ) = *(_Buff + i);
		return true;
	}
	catch ( std::exception e ) { };
	return false;
}


end_MEMORY