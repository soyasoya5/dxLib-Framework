#include "async.h"

begin_LIB

void AsyncKeeper::lock()
{
	_mu.lock( );
}

void AsyncKeeper::unlock()
{
	_mu.unlock( );
}


AsyncGuard::AsyncGuard( AsyncKeeper &_Keeper )
	: _keeper( _Keeper )
{
	_keeper.lock( );
}

AsyncGuard::~AsyncGuard( )
{
	_keeper.unlock( );
}

FlexibleGuard::FlexibleGuard(AsyncKeeper & _Keeper)
	: _keeper( _Keeper )
{
	_keeper.lock( );
}

FlexibleGuard::~FlexibleGuard()
{
	_keeper.unlock( );
}

void FlexibleGuard::lock()
{
	_keeper.lock( );
}

void FlexibleGuard::unlock()
{
	_keeper.unlock( );
}


end_LIB

