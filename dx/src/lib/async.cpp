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


AsyncGuard::AsyncGuard( AsyncKeeper &kpr )
	: keeper_( kpr )
{
	keeper_.lock( );
}

AsyncGuard::~AsyncGuard( )
{
	keeper_.unlock( );
}

FlexibleGuard::FlexibleGuard(AsyncKeeper & kpr)
	: keeper_( kpr )
{
	keeper_.lock( );
}

FlexibleGuard::~FlexibleGuard()
{
	keeper_.unlock( );
}

void FlexibleGuard::lock()
{
	keeper_.lock( );
}

void FlexibleGuard::unlock()
{
	keeper_.unlock( );
}


end_LIB

