#pragma once
#include "lib.h"
#include "../dx.h"

begin_LIB

class AsyncKeeper
{
private:
	std::mutex _mu;
public:
	///<summary>
	/// Lock the internal mutex.
	///</summary>
	void lock( );

	///<summary>
	/// Unlock the internal mutex.
	///</summary>
	void unlock( );
};


class AsyncGuard
{
private:
	AsyncKeeper &keeper_;
public:
	///<summary>
	/// Construct this guard.
	///</summary>
	AsyncGuard( AsyncKeeper &keeper_ );
	~AsyncGuard( );
};


class FlexibleGuard
{
private:
	AsyncKeeper &keeper_;
public:
	///<summary>
	/// Construct this guard.
	///</summary>
	FlexibleGuard( AsyncKeeper &keeper );
	~FlexibleGuard( );

	///<summary>
	/// Lock the internal Keeper.
	///</summary>
	void lock( );

	///<summary>
	/// Unlock the internal Keeper.
	///</summary>
	void unlock( );
};


end_LIB

