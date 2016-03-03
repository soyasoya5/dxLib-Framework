#pragma once
#include "Types.h"


namespace Utils {
	namespace Memory {

		template<>
		class Handle<Destructor, static_cast<uint>(-1)>
		{
		private:
			HANDLE _handle;
			bool _api;
		public:
			Handle( ) = default;
			Handle( const Handle& ) = default;
			Handle( Handle&& ) = default;

			///<summary>
			///Constructs the handle by an existing
			///handle, note that this means 'Handle'
			///takes ownership of the handle, and
			///it will be closed when 'Handle' goes
			/// out of scope. (Only applies when _Lifetime is eq Destructor)
			///</summary>
			Handle( const HANDLE &_Handle );
			~Handle( );
			
			HANDLE& get( );
			bool isDestroyed( );
			bool &isWinapi( );
		};
		

		inline Handle<Destructor, static_cast<uint>(-1)>::Handle(const HANDLE &handle)
			: _handle( handle )
		{ }

		inline Handle<Destructor, static_cast<uint>(-1)>::~Handle()
		{
			if ( _handle != INVALID_HANDLE_VALUE && this->isWinapi( ) )
				CloseHandle( _handle );
		}

		inline HANDLE& Handle<Destructor, static_cast<uint>(-1)>::get()
		{
			return _handle;
		}

		inline bool Handle<Destructor, static_cast<uint>(-1)>::isDestroyed()
		{
			return false;
		}

		inline bool &Handle<Destructor, static_cast<uint>(-1)>::isWinapi()
		{
			return _api;
		}



	}
}