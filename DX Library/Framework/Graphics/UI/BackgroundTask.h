#pragma once
#include "../../dx.h"
#include "../../Event/EventHandler.h"

// Isn't actually a UI component, but is used for background tasks
namespace Graphics {
	namespace UI {

		class AsyncKeeper
		{
			std::mutex _mu;
		public:
			AsyncKeeper( );

			void Begin( );
			void End( );

		};

		class AsyncGuard
		{
			AsyncKeeper& _kpr;
		public:
			AsyncGuard( AsyncKeeper& );
			~AsyncGuard( );
		};

		class BackgroundTask
		{
		private:
			AsyncKeeper _kpr;
			std::function<void()> _stored;
			Event<bool, BackgroundTask*> _OnComplete;
			HANDLE _t;

			static DWORD _Thread( LPVOID lpData )
			{
				auto thisptr = (BackgroundTask*)(lpData);
				if ( thisptr->_stored ) 
					thisptr->_stored( );
				thisptr->OnComplete( ).Invoke( thisptr );
				return 0;
			}
		public:
			BackgroundTask( );

			void Start( const std::function<void(AsyncKeeper&)> &function )
			{
				_stored = [func = function, _kpr = &this->_kpr]( )mutable->void { if ( func ) func( *_kpr ); };
				_t = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)_Thread, this, 0, 0 );
			}

			void Halt( )
			{
				TerminateThread( _t, 0 );
			}


			Event<bool, BackgroundTask*>& OnComplete( );
		};

	}
}