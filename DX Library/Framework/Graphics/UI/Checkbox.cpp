#include "Checkbox.h"
#include "../Renderer/Renderer.h"

namespace Graphics {
	namespace UI {
		Checkbox::Checkbox()
		{
			setMin(0);
			setMax(1);
		}
		void Checkbox::Paint(Renderer::D9Renderer *r)
		{
			if ( !isVisible( ) )
				return;
			OnPrePaint( ).Invoke( this, r );

			auto stylesheet = getStylesheet( );
			auto pos = getAbsolutePosition( ) + getPadding( );
			auto size = getSize( );

			if ( isFocused( ) )
			{
				auto foreground = stylesheet.get_argb( "ui_checkbox_focus", Style::Style_foreground );
				auto line = stylesheet.get_argb( "ui_checkbox_focus", Style::Style_line );
				auto text = stylesheet.get_argb( "ui_checkbox_focus", Style::Style_text );
				auto ex = stylesheet.get_argb( "ui_checkbox_focus", Style::Style_extra );

				r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
				if ( isChecked( ) )
					r->Rect( pos.x + 2, pos.y + 2, size.x - 4, size.y - 4, ex );
				r->String( pos.x + size.x + 15, pos.y, getFont( ), text, getText( ) );
			}
			else if ( isHovered( ) )
			{
				auto foreground = stylesheet.get_argb("ui_checkbox_hover", Style::Style_foreground);
				auto line = stylesheet.get_argb("ui_checkbox_hover", Style::Style_line);
				auto text = stylesheet.get_argb("ui_checkbox_hover", Style::Style_text);
				auto ex = stylesheet.get_argb( "ui_checkbox_hover", Style::Style_extra );

				r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
				if ( isChecked( ) )
					r->Rect( pos.x + 2, pos.y + 2, size.x - 4, size.y - 4, ex );
				r->String( pos.x + size.x + 15, pos.y, getFont( ), text, getText( ) );
			}
			else
			{
				auto foreground = stylesheet.get_argb("ui_checkbox", Style::Style_foreground );
				auto line = stylesheet.get_argb( "ui_checkbox", Style::Style_line );
				auto text = stylesheet.get_argb( "ui_checkbox", Style::Style_text );
				auto ex = stylesheet.get_argb( "ui_checkbox", Style::Style_extra );
				

				r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
				if ( isChecked( ) )
					r->Rect( pos.x + 2, pos.y + 2, size.x - 4, size.y - 4, ex );
				r->String( pos.x + size.x + 15, pos.y, getFont( ), text, getText( ) );
			}

			OnPostPaint( ).Invoke( this, r );
		}

		bool Checkbox::OnMouseMove(Vector2 mouse)
		{
			if ( !isVisible( ) || !isEnabled( ) )
				return true;

			if ( Collides( mouse ) )
			{
				if ( !_hovered )
					OnMouseEnter( ).Invoke( this, mouse );
				_hovered = true;
			}
			else
			{
				if (_hovered)
					OnMouseLeave( ).Invoke( this, mouse );
				_hovered = false;
			}
			return __super::OnMouseMove( mouse );
		}

		bool Checkbox::OnLeftMouseDown(Vector2 mouse)
		{
			if ( !isVisible( ) || !isEnabled( ) )
				return true;

			if ( Collides( mouse ) )
			{
				_focusing = true;
			}
			else
				_focusing = false;

			return __super::OnLeftMouseDown( mouse );
		}

		bool Checkbox::OnLeftMouseUp(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;
			
			if ( Collides( mouse ) )
			{
				if (_focusing)
					setState( !static_cast<bool>( getState( ) ) );
				OnComponentClicked().Invoke(this, mouse);
			}

			_focusing = false;
			return __super::OnLeftMouseUp( mouse );
		}

		bool Checkbox::OnRightMouseDown(Vector2 mouse)
		{
			return __super::OnRightMouseDown( mouse );
		}

		bool Checkbox::OnRightMouseUp(Vector2 mouse)
		{
			return __super::OnRightMouseUp( mouse );
		}

		bool Checkbox::OnKeyDown(uint key)
		{
			return __super::OnKeyDown( key );
		}

		bool Checkbox::OnKeyUp(uint key)
		{
			return __super::OnKeyUp( key );
		}

	}
}
