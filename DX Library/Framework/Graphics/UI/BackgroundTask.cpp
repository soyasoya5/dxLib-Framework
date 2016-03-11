#include "..\..\..\..\dx\src\lib\async.h"
#include "BackgroundTask.h"

Graphics::UI::AsyncKeeper::AsyncKeeper()
{}

void Graphics::UI::AsyncKeeper::Begin()
{
	_mu.lock( );
}

void Graphics::UI::AsyncKeeper::End()
{
	_mu.unlock();
}

Graphics::UI::BackgroundTask::BackgroundTask()
{
}

Event<bool, dx::BackgroundTask*>& Graphics::UI::BackgroundTask::OnComplete()
{
	return _OnComplete;
}



Graphics::UI::AsyncGuard::~AsyncGuard()
{
	_kpr.End( );
}
