#pragma once
#include "lib.h"
#include "../dx.h"

begin_LIB

class AsyncKeeper
{
private:
	std::mutex _mu;
public:
	void lock( );
	void unlock( );
};



class AsyncGuard
{
private:
	AsyncKeeper &_keeper;
public:
	AsyncGuard(AsyncKeeper &_Keeper);
	~AsyncGuard( );
};


class FlexibleGuard
{
private:
	AsyncKeeper &_keeper;
public:
	FlexibleGuard(AsyncKeeper &_Keeper);
	~FlexibleGuard( );

	void lock( );
	void unlock( );
};


end_LIB

