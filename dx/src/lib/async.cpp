#include "async.h"

begin_LIB

void AsyncKeeper::lock()
{
	while( data_ )
		std::this_thread::sleep_for( std::chrono::nanoseconds( 5000 ) );
	t_ = GetCurrentThreadId( );
	data_ = true;
}

void AsyncKeeper::unlock()
{
	data_ = false;
	t_ = 0;
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

