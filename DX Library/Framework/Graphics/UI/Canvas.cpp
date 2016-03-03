#include "Canvas.h"
#include "Window.h"

namespace Graphics {
	namespace UI {


		Canvas::WindowSearch::WindowSearch(uint idx, std::vector<Iterator> iters)
			: _idx(idx), _iters(iters)
		{
		}

		const uint & Canvas::WindowSearch::getIndex()
		{
			return _idx;
		}

		const std::vector<Canvas::WindowSearch::Iterator>& Canvas::WindowSearch::getIters()
		{
			return _iters;
		}

		bool Canvas::WindowSearch::empty()
		{
			return _iters.empty();
		}

		uint Canvas::WindowSearch::size()
		{
			return _iters.size();
		}

		void Canvas::add(Window *window)
		{
			if ( _windows.empty( ) )
				window->setTopMost( true );
			_windows.push_back( window );
		}

		void Canvas::erase(const uint &idx)
		{
			_windows.erase( _windows.begin( ) + idx );
		}

		uint Canvas::Search(const std::function<bool(Window*)> &functor) noexcept
		{
			static uint idx = 0;
			idx = 0;
			for ( auto it = _windows.begin( ); it != _windows.end( ); ++it, ++idx)
				if ( functor( *it ) )
					return idx;
			return scast<uint>( -1 );
		}

		Window * Canvas::getWindow(const uint &idx)
		{
			return _windows[idx];
		}

		Window * Canvas::TopMost()
		{
			for ( auto&x : _windows )
				if ( x->TopMost( ) )
					return x;
			return nullptr;
		}

		void Canvas::Paint(Renderer::D9Renderer *r)
		{
			Window* top = nullptr;
			for ( auto it = _windows.rbegin( ); it < _windows.rend( ); ++it) {
				if ( (*it)->TopMost( ) )
				{
					top = *it;
					continue;
				}
				(*it)->Paint( r );
			}
			if ( top )
				top->Paint( r );
		}

		bool Canvas::OnMouseMove(Vector2 mouse)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnMouseMove( mouse );
		}

		bool Canvas::OnLeftMouseDown(Vector2 mouse)
		{
			auto top = TopMost( );
			for ( auto &it =  _windows.begin( ); it < _windows.end( ); ++it )
			{
				if ( top == nullptr )
				{
					(*it)->setTopMost( true );
					break;
				}

				auto& window = *it;
				if ( window == top )
					continue;

				if ( window->Collides( mouse ) && !top->Collides( mouse ) && window->isEnabled( ) )
				{
					top->setTopMost( false );
					window->setTopMost( true );
					break;
				}
			}

			if ( _windows.empty( ) )
				return false;
			return  TopMost( )->OnLeftMouseDown( mouse );
		}

		bool Canvas::OnLeftMouseUp(Vector2 mouse)
		{
			if ( _windows.empty( ) )
				return false;
			return  TopMost( )->OnLeftMouseUp( mouse );
		}

		bool Canvas::OnRightMouseDown(Vector2 mouse)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnRightMouseDown( mouse );
		}

		bool Canvas::OnRightMouseUp(Vector2 mouse)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnRightMouseUp( mouse );
		}

		bool Canvas::OnRightMouseDoubleClick(Vector2 mouse)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnRightMouseDoubleClick(mouse);
		}

		bool Canvas::OnLeftMouseDoubleClick(Vector2 mouse)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnLeftMouseDoubleClick( mouse );
		}

		bool Canvas::OnKeyDown(uint key)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnKeyDown( key );
		}

		bool Canvas::OnKeyUp(uint key)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnKeyUp( key );
		}

		bool Canvas::OnKeyDownChar(char key)
		{
			if ( _windows.empty( ) )
				return false;
			return TopMost( )->OnKeyDownChar( key );
		}

	}
}

