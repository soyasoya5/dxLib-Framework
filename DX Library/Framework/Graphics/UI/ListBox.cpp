#include "ListBox.h"
#include "RichLabel.h"
#include "Scrollbar.h"
#include "../Renderer/Renderer.h"

namespace Graphics {
	namespace UI {

		void ListBox::setMaxCount(Renderer::D9Renderer* r)
		{
			Vector2 offset{ 3, -15 };
			auto size = getSize( );
			for ( size_t i = 0; i < _items.size( ); ++i )
			{
				auto e = _items[i];
				auto txtSize = r->StrSize( getFont( ), e->getText( ) );

				if (offset.y + txtSize.y >= size.y)
					break; // break
				setState(i); // this was the last one.
				offset.y += txtSize.y;
			}
		}

		bool ListBox::ReOrder(Renderer::D9Renderer* r)
		{
			if ( _items.size( ) <= getState( ) )
				_count = 0;
			else {
				float scroll = _bar->getScroll( );
				float max = _bar->getMax( );
				float state = getState( );
				auto res =  ( scroll / max ) * _items.size( );
				_count = res;
			}

			ReOrderNext( r );
			return true;
		}

		bool ListBox::ReOrderNext(Renderer::D9Renderer* r)
		{
			Vector2 offset{ 3, 5 };

			for ( auto it = _items.begin( ); it != _items.end( ); ++it )
				(*it)->setVisible( false );

			bool first = true;
			size_t count = 0;
			for ( auto it = (_items.begin( ) + _count); it != _items.end( ); ++it, ++count )
			{
				// If count == the last available index
				if ( count > getState( ) )
					break;

				if ( first ) // If its the frist one, always set it to visible.
				{
					auto txtSize = r->StrSize( getFont( ), (*it)->getText( ) );
					(*it)->setAbsolutePosition( getAbsolutePosition( ) + getPadding( ) );
					(*it)->setAbsolutePosition( (*it)->getAbsolutePosition( ) + offset );
					(*it)->setVisible( true );
					first = false;
					continue;
				}

				auto txtSize = (*it)->getSize( );

				(*it)->setAbsolutePosition( (*(it - 1))->getAbsolutePosition( ) );

				(*it)->setAbsolutePosition( (*it)->getAbsolutePosition( ) + Vector2{ 0, txtSize.y } );
				(*it)->setVisible( true );
			}
			return true;
		}

		ListBox::ListBox()
		{
			_bar = new Scrollbar;
			_bar->setScroll( 0 );
			_bar->setMax( 100 );
			setMax( 100 );
			_bar->setType( Vertical );
			_bar->setVisible( true );
			_reCalc = true;

			_bar->OnStateChanged( ) += [&]( Component*, int ) { _reCalc = true; return true; };

			OnAbsolutePositionChanged( ) += [&]( Component *sender, Vector2 pos )->bool
			{ _reCalc = true; return true; };

			OnSizeChanged( ) += [&]( Component *sender, Vector2 size )->bool
			{ _reCalc = true; return true; };

			addChild( _bar );
		}

		ListBox::~ListBox()
		{
			_bar->Release( );
			delete _bar;
			for ( auto&x : _items ) {
				x->Release( );
				delete x;
			}
		}

		void ListBox::Paint( Renderer::D9Renderer* r)
		{
			if ( !isVisible( ) )
				return;
			OnPrePaint( ).Invoke( this, r );

			if ( _reCalc )
			{
				setMaxCount( r );
				ReOrder( r );
				_reCalc = false;
			}

			auto pos = getAbsolutePosition( ) + getPadding( );
			auto size = getSize( );
			auto style = getStylesheet( );
			auto foreground = style.get_argb( "ui_scrollbar", Style::Style_foreground );
			auto line = style.get_argb( "ui_scrollbar", Style::Style_line );

			r->RectOutlined(pos.x, pos.y, size.x, size.y, 1, foreground, line);

			for ( auto e : _items )
				e->Paint( r );


			_bar->Paint( r );
			OnPostPaint( ).Invoke( this, r );
		}

		void ListBox::Tick()
		{
			_can = false;
			for ( auto&x : _todos )
				addItem( x.first, x.second );
			_todos.clear( );
			_can = true;
		}

		bool ListBox::OnMouseMove(Vector2 mouse)
		{
			if ( !isVisible( ) || !isEnabled( ) )
				return false;

			_bar->OnMouseMove( mouse );

			for ( auto e : _items )
				if ( e->isVisible( ) )
					e->OnMouseMove( mouse );
			return true;
		}

		bool ListBox::OnLeftMouseDown(Vector2 mouse)
		{
			if ( !isVisible( ) || !isEnabled( ) )
				return false;

			_bar->OnLeftMouseDown( mouse );

			for ( auto e : _items )
				if ( e->isVisible( ) )
					e->OnLeftMouseDown( mouse );
			return true;
		}

		bool ListBox::OnLeftMouseUp( Vector2 mouse )
		{
			if ( !isVisible( ) || !isEnabled( ) )
				return false;
			_bar->OnLeftMouseUp( mouse );

			for ( auto e : _items )
				if ( e->isVisible( ) )
					e->OnLeftMouseUp( mouse );
			return true;
		}

		bool ListBox::OnKeyDown(uint)
		{
			return true;
		}

		bool ListBox::OnKeyUp(uint)
		{
			return true;
		}

		void ListBox::setStylesheet(const Style::Stylesheet & sheet)
		{
			__super::setStylesheet( sheet );
			for ( auto&x : _items )
				x->setStylesheet( sheet );
		}

		void ListBox::setSize(const Vector2 & vec)
		{
			__super::setSize( vec ); // Fire events
			_bar->setSize( { 15, getSize( ).y } );
			_bar->setPadding( { getSize( ).x + 2.f, 0.0f } );
			_bar->setBarSize( { 0.0f, 25.0f } );
			_reCalc = true;
		}

		void ListBox::removeItem(const Utils::String & str)
		{
			size_t count = 0;
			for ( auto it = _items.begin( ); it != _items.end( ); ++it, ++count )
			{
				if ( (*it)->getText( ) == str )
				{
					_items.erase( it );
					(*it)->Release( );
					delete (*it);
					break;
				}
			}
			_reCalc = true;
		}

		void ListBox::removeItem(const int & idx)
		{
			size_t count = 0;
			for ( auto it = _items.begin( ); it != _items.end( ); ++it, ++count )
			{
				if ( count == idx )
				{
					_items.erase( it );
					(*it)->Release( );
					delete (*it);
					break;
				}
			}
			_reCalc = true;
		}

		void ListBox::ClearItems()
		{
			auto vec = _items;
			_items.clear( );
			for ( auto&x : vec )
			{
				x->Release( );
				delete x;
			}
			_reCalc = true;
		}

		void ListBox::addItem(const Utils::String & name, const Utils::String & value)
		{
			addItem( name, value, Colors::White );
		}

		void ListBox::addItem(const Utils::String & _Text, const Utils::String &_Value, const Color & _Color)
		{
			auto item = new RichLabel( );
			item->appendText( _Text, _Color );
			item->setHiddenText( _Value );
			item->setFont( getFont( ) );
			item->setMax( 1 );

			item->OnComponentClicked( ) += [&]( Component* sender, Vector2 pressed )->bool
			{
				bool state = !(bool)sender->getState();
				for (auto e : _items)
					e->setState( 0 );
				sender->setState( state );
				return true;
			};

			item->OnPrePaint( ) += [&]( Component* sender, Renderer::D9Renderer* r )->bool
			{
				if ( sender->getState( ) ) 
				{
					auto myAbs = getAbsolutePosition( ) + getPadding( );
					auto sAbs = sender->getAbsolutePosition( );
					auto size = sender->getSize( );
					r->Rect( myAbs.x + 1, sAbs.y + 1, getSize( ).x, size.y, D3DCOLOR_ARGB(255, 40, 40, 40) );
				}
				return true;
			};

			_items.push_back(item);
			_reCalc = true;
		}

		void ListBox::addItem_safe(const Utils::String & name, const Utils::String & value)
		{
			while( !_can );
			_todos.push_back( { name, value } );
		}

		Event<bool, Component*>& ListBox::OnItemSelected()
		{
			return _myOnItemSelected;
		}


	}
}