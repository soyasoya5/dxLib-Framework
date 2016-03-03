#include "BackgroundTask.h"

Graphics::UI::AsyncKeeper::AsyncKeeper()
{	
	_s[0] = false;
	*((int*)_s + 1) = 0; // [0]<State storage ([1][2][3][4])< Thread storage
}

void Graphics::UI::AsyncKeeper::Begin()
{
	// While it is already doing something, just delay it.
	while( *_s );

	auto thread = ccast<int*>( get( 0 ) );
	*thread = GetCurrentThreadId();
	*_s = true;
}

void Graphics::UI::AsyncKeeper::End()
{
	if ( *_s )
		return;
	auto thread = ccast<int*>( get( 0 ) );
	if ( *thread != GetCurrentThreadId( ) )
		return;
	*_s = false;

}

byte* Graphics::UI::AsyncKeeper::get(const uint &idx)
{
	return _s + idx;
}

Graphics::UI::BackgroundTask::BackgroundTask()
{
}

Graphics::UI::AsyncGuard::AsyncGuard(AsyncKeeper &kpr)
	: _kpr( kpr )
{
	_kpr.Begin( );
}

Graphics::UI::AsyncGuard::~AsyncGuard()
{
	_kpr.End( );
}
