#pragma once
#include "../../dx.h"


// Isn't actually a UI component, but is used for background tasks
namespace Graphics {
	namespace UI {

		class AsyncKeeper
		{
			byte _s[5];
		public:
			AsyncKeeper( );

			void Begin( );
			void End( );

			byte* get( const uint& );
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
			std::thread _thread;
			AsyncKeeper _kpr;

		public:
			BackgroundTask( );

			template<typename _Func>
			void Start( _Func&& function )
			{
				_thread = std::thread{ std::forward<_Func>( function ), _kpr };
			}

		};

	}
}