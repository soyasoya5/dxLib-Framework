#pragma once
#include "Component.h"

namespace Graphics {
	namespace UI {
		class Window;

		class Canvas
		{
		private:
			// Window @ index [0] = Topmost
			std::vector<Window*> _windows;
			bool _clicking, _hovering;

		public:

			class WindowSearch
			{
			private:
				friend class Canvas;
				typedef std::vector<Window*>::iterator Iterator;
				uint _idx;
				std::vector<Iterator> _iters;

				WindowSearch( uint idx, std::vector<Iterator> iters );
			public:
				const uint& getIndex( );
				const std::vector<Iterator>& getIters( );
				bool empty( );
				uint size( );
			};

		public:
			virtual void Paint( Renderer::D9Renderer* );

			virtual bool OnMouseMove( Vector2 );
			virtual bool OnLeftMouseDown( Vector2 );
			virtual bool OnLeftMouseUp( Vector2 );
			virtual bool OnRightMouseDown( Vector2 );
			virtual bool OnRightMouseUp( Vector2 );
			virtual bool OnRightMouseDoubleClick( Vector2 );
			virtual bool OnLeftMouseDoubleClick( Vector2 );
			virtual bool OnKeyDown( uint );
			virtual bool OnKeyUp( uint );
			virtual bool OnKeyDownChar( char );

		public:
			void add( Window* );
			void erase( const uint& );
			uint Search( const std::function<bool(Window*)>& ) noexcept;
			Window* getWindow( const uint& );
			Window* TopMost( );
			
		};

	}
}
