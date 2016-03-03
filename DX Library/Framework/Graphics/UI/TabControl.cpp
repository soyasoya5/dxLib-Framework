#include "TabControl.h"
#include "../Renderer/Renderer.h"

namespace Graphics {
	namespace UI {

		uint Graphics::UI::Tab::getIndex()
		{
			return _idx;
		}

		void Graphics::UI::Tab::setIndex(const uint &idx)
		{
			_idx = idx;
		}

		Vector2 Tab::getStrSize()
		{
			return getSize( );
		}

		void Tab::setStrSize(const Vector2 &strSize)
		{
			setSize( strSize );
		}

		void Graphics::UI::Tab::Paint(Renderer::D9Renderer *r)
		{
			for ( auto& x : getChildren( ) )
				x->Paint( r );
		}

		std::vector<Tab*> Graphics::UI::TabControl::getTabs()
		{
			return _tabs;
		}

		void Graphics::UI::TabControl::addTab(Tab *tab)
		{
			_tabs.push_back( tab );
			addChild( tab );
		}

		void TabControl::Paint(Renderer::D9Renderer *r)
		{
			OnPrePaint().Invoke( this, r );
			auto pos = getAbsolutePosition( ) + getPadding( );
			auto size = getSize( );
			auto style = getStylesheet( );
			auto foreground = style.get_argb( "ui_tabcontrol", Style::Style_foreground );
			auto text = style.get_argb( "ui_tabcontrol", Style::Style_text );
			auto ex = style.get_argb( "ui_tabcontrol", Style::Style_extra );

			if ( getType( ) == Horizontal )
			{
				auto length = _tabs.size( ) * size.x;

				r->Rect( pos.x, pos.y + size.y, length, 3, foreground );

				for ( uint i = 0; i < _tabs.size( ); ++i )
				{
					Vector2 pos_pad = { pos.x + (i * size.x), pos.y };
					if ( i == _selected )
						r->Rect( pos_pad.x, pos.y + size.y, size.x, 3, ex );
					auto strsize = r->StrSize( getFont( ), _tabs[i]->getText( ) );
					_tabs[i]->setSize( strsize );
					r->String( pos_pad.x, pos_pad.y, getFont( ), text, _tabs[i]->getText( ) );
				}
			} 
			else
			{
				auto length = _tabs.size( ) * size.y;
				
				r->Rect( pos.x, pos.y, 3, length, foreground );

				for ( uint i = 0; i < _tabs.size( ); ++i )
				{
					Vector2 pos_pad = { pos.x + 10, pos.y + (i * size.y) };
					if ( i == _selected )
						r->Rect( pos.x, pos_pad.y, 3, size.y, ex );
					auto strsize = r->StrSize( getFont( ), _tabs[i]->getText( ) );
					_tabs[i]->setSize( strsize );
					r->String( pos_pad.x, pos_pad.y, getFont( ), text, _tabs[i]->getText( ) );
				}
			}


			_tabs[_selected]->Paint( r );
			OnPostPaint( ).Invoke( this, r );
		}

		bool TabControl::OnMouseMove(Vector2 mouse)
		{
			return _tabs[_selected]->OnMouseMove( mouse );
		}

		bool TabControl::OnLeftMouseDown(Vector2 mouse)
		{
			for ( uint i = 0; i < _tabs.size( ); ++i )
			{
				if ( TabCollides( i, mouse ) )
				{
					OnSelectedTabChanged().Invoke( this, i );
					_selected = i;
				}
			}
			return  _tabs[_selected]->OnLeftMouseDown( mouse );
		}

		bool TabControl::OnLeftMouseUp(Vector2 mouse)
		{
			return _tabs[_selected]->OnLeftMouseUp( mouse );
		}

		bool TabControl::OnRightMouseDown(Vector2 mouse)
		{
			return _tabs[_selected]->OnRightMouseDown( mouse );
		}

		bool TabControl::OnRightMouseUp(Vector2 mouse)
		{
			return _tabs[_selected]->OnRightMouseUp( mouse );
		}

		bool TabControl::OnLeftMouseDoubleClick(Vector2 mouse)
		{
			return _tabs[_selected]->OnLeftMouseDoubleClick( mouse );
		}

		bool TabControl::OnRightMouseDoubleClick(Vector2 mouse)
		{
			return _tabs[_selected]->OnRightMouseDoubleClick( mouse );
		}

		bool TabControl::OnKeyDown(uint key)
		{
			return _tabs[_selected]->OnKeyDown( key );
		}

		bool TabControl::OnKeyUp(uint key)
		{
			return _tabs[_selected]->OnKeyUp( key );
		}

		bool TabControl::OnKeyDownChar(char key)
		{
			return _tabs[_selected]->OnKeyDownChar( key );
		}


		bool TabControl::TabCollides(const uint & idx, const Vector2 &mouse)
		{
			if ( idx > _tabs.size( ) )
				return false;
			auto pos = getAbsolutePosition( ) + getPadding( );
			auto size = getSize( );
			auto tab_size = _tabs[idx]->getStrSize();
			if ( getType( ) == Horizontal )
				tab_size = size;
			Vector2 tab_pos{ 0, 0 };

			if ( getType( ) == Horizontal )
				tab_pos = { pos.x + (idx * size.x), pos.y };
			else
				tab_pos = { pos.x + 10, pos.y + (idx * size.y) };

			return mouse.x >= tab_pos.x && mouse.x <= tab_pos.x + tab_size.x &&
				   mouse.y >= tab_pos.y && mouse.y <= tab_pos.y + tab_size.y;
		}

		bool TabControl::CollidesWithChildren(const Vector2 &mouse)
		{
			if ( __super::CollidesWithChildren( mouse ) )
				return true;
			for ( uint i = 0; i < _tabs.size( ); ++i)
				if ( TabCollides( i, mouse ) )
					return true;
			return false;
		}

		Event<bool, TabControl*, uint>& TabControl::OnSelectedTabChanged()
		{
			return _OnSelectedTabChanged;
		}

	}
}
