#include "Button.h"
#include "../Renderer/Renderer.h"

namespace Graphics {
	namespace UI {

		void Graphics::UI::Button::Paint(Renderer::D9Renderer *r)
		{
			if ( !isVisible( ) )
				return;
			OnPrePaint( ).Invoke( this, r );

			auto stylesheet = getStylesheet( );
			auto pos = getAbsolutePosition( ) + getPadding( );
			auto size = getSize( );

			Vector2 text{ r->StrSize( getFont( ), getText( ) ) }, mid{ 0, 0 };

			auto allign = getAllignment( );
			if (allign == Middle) {
				mid.x = ( size.x / 2 - text.x / 2 ) + pos.x;
				mid.y = ( size.y / 2 - text.y / 2 ) + pos.y;
			}
			else if (allign == Left)
			{
				mid.x = pos.x + 5;
				mid.y = ( size.y / 2 - text.y / 2 ) + pos.y;
			}
			else
			{
				mid.x = pos.x + size.x - (text.x + 5);
				mid.y = ( size.y / 2 - text.y / 2 ) + pos.y;
			}

			if ( isFocused( ) )
			{
				auto foreground = stylesheet.get_argb( "ui_button_focus", Style::Style_foreground );
				auto line = stylesheet.get_argb( "ui_button_focus", Style::Style_line );
				auto text = stylesheet.get_argb( "ui_button_focus", Style::Style_text );

				r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
				r->String( mid.x, mid.y, getFont( ), text, getText( ) );
			}
			else if ( isHovered( ) )
			{
				auto foreground = stylesheet.get_argb("ui_button_hover", Style::Style_foreground);
				auto line = stylesheet.get_argb("ui_button_hover", Style::Style_line);
				auto text = stylesheet.get_argb("ui_button_hover", Style::Style_text);

				r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
				r->String( mid.x, mid.y, getFont( ), text, getText( ) );
			}
			else
			{
				auto foreground = stylesheet.get_argb("ui_button", Style::Style_foreground );
				auto line = stylesheet.get_argb( "ui_button", Style::Style_line );
				auto text = stylesheet.get_argb( "ui_button", Style::Style_text );
				

				r->RectOutlined( pos.x, pos.y, size.x, size.y, 1, foreground, line );
				r->String( mid.x, mid.y, getFont( ), text, getText( ) );
			}

			OnPostPaint( ).Invoke( this, r );
		}

		bool Button::OnMouseMove(Vector2 mouse)
		{
			if ( !isVisible() || !isEnabled() )
				return true;

			if ( Collides( mouse ) )
			{
				if ( !_hovered )
					OnMouseEnter().Invoke( this, mouse );
				_hovered = true;
			}
			else
			{
				if (_hovered)
					OnMouseLeave().Invoke( this, mouse );
				_hovered = false;
			}
			return __super::OnMouseMove( mouse );
		}

		bool Button::OnLeftMouseDown(Vector2 mouse)
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

		bool Button::OnLeftMouseUp(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;
			
			if ( Collides( mouse ) )
			{
				OnComponentClicked( ).Invoke( this, mouse );
			}

			_focusing = false;
			return __super::OnLeftMouseUp( mouse );
		}

		bool Button::OnRightMouseDown(Vector2 mouse)
		{
			return __super::OnRightMouseDown( mouse );
		}

		bool Button::OnRightMouseUp(Vector2 mouse)
		{
			return __super::OnRightMouseUp( mouse );
		}

		bool Button::OnKeyDown(uint key)
		{
			return __super::OnKeyDown( key );
		}

		bool Button::OnKeyUp(uint key)
		{
			return __super::OnKeyUp( key );
		}



	}
}