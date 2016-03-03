#include "Textbox.h"
#include "../Renderer/Renderer.h"

namespace Graphics {
	namespace UI {

		void Textbox::Paint(Renderer::D9Renderer *r)
		{
			if ( !isVisible( ) )
				return;
			OnPrePaint( ).Invoke( this, r );

			auto stylesheet = getStylesheet( );
			auto pos = getAbsolutePosition( ) + getPadding( );
			auto size = getSize( );
			Utils::String szText = getText( );

			if ( isPassword( ) )
			{
				for ( auto&x : szText )
					x = _passC;
			} 

			Vector2 text{ r->StrSize( getFont( ), szText ) }, mid{ 0, 0 };

			if ( text.x == 0 || text.y == 0 )
				text = r->StrSize( getFont( ), getHiddenText( ) );


			auto allign = getAllignment( );
			if ( allign == Middle ) {
				mid.x = (size.x / 2 - text.x / 2) + pos.x;
				mid.y = (size.y / 2 - text.y / 2) + pos.y;
			}
			else if ( allign == Left )
			{
				mid.x = pos.x + 5;
				mid.y = (size.y / 2 - text.y / 2) + pos.y;
			}
			else
			{
				mid.x = pos.x + size.x - (text.x + 5);
				mid.y = (size.y / 2 - text.y / 2) + pos.y;
			}

			{
				auto foreground = stylesheet.get_argb( "ui_textbox", Style::Style_foreground );
				auto line = stylesheet.get_argb( "ui_textbox", Style::Style_line );
				auto text = stylesheet.get_argb( "ui_textbox", Style::Style_text );
				auto ex = stylesheet.get_argb( "ui_textbox", Style::Style_extra );

				r->Line( pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, line );

				if ( !szText.empty( ) || isFocused( ) )
					r->String( mid.x, mid.y, getFont( ), text, szText );
				else
					r->String( mid.x, mid.y, getFont( ), ex, getHiddenText( ) );
			}
			
			if ( isFocused( ) )
			{
				if ( GetTickCount( ) > _timeBuffer ) {
					_timeBuffer = GetTickCount( ) + 500;
					_blink = !_blink;
				}
				if ( _blink )
				{
					if ( !szText.empty( ) )
						r->Line( mid.x + 3 + text.x, mid.y, (mid.x + 3) + text.x, mid.y + text.y, D3DCOLOR_ARGB(255, 255, 255, 255) );
					else				
						r->Line( mid.x + 3, mid.y, mid.x + 3, mid.y + text.y, D3DCOLOR_ARGB(255, 255, 255, 255) );
				}
			}

			_textSize = text;
			OnPostPaint( ).Invoke( this, r );
		}

		void Textbox::Tick()
		{
			if ( (GetTickCount( ) - _time2) > 2000 && _time2 != 0 ) {
				OnStopWriting( ).Invoke( this );
				_time2 = 0;
			}
		}

		bool Textbox::OnMouseMove(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;

			if (Collides(mouse))
			{
				if (!_hovered)
					OnMouseEnter().Invoke(this, mouse);
				_hovered = true;
			}
			else
			{
				if (_hovered)
					OnMouseLeave().Invoke(this, mouse);
				_hovered = false;
			}
			return __super::OnMouseMove(mouse);
		}

		bool Textbox::OnLeftMouseDown(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;

			if (Collides(mouse))
			{
				_focusing = true;
			}
			else
				_focusing = false;

			return __super::OnLeftMouseDown(mouse);
		}

		bool Textbox::OnLeftMouseUp(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;

			if (Collides(mouse))
			{
				if (_focusing)
					setState(!static_cast<bool>(getState()));
				OnComponentClicked().Invoke(this, mouse);
			}
			else
				_focusing = false;

			return __super::OnLeftMouseUp(mouse);
		}

		bool Textbox::OnRightMouseDown(Vector2 mouse)
		{
			return __super::OnRightMouseDown(mouse);
		}

		bool Textbox::OnRightMouseUp(Vector2 mouse)
		{
			return __super::OnRightMouseUp(mouse);
		}

		bool Textbox::OnKeyDown(uint key)
		{
			return __super::OnKeyDown(key);
		}

		bool Textbox::OnKeyUp(uint key)
		{
			return __super::OnKeyUp(key);
		}

		bool Textbox::OnKeyDownChar(char key)
		{
			if ( !isVisible() || !isEnabled() )
				return true;
			if ( isFocused( ) )
			{
				if (key == '\b')
				{
					auto text = getText( );
					if ( !text.empty( ) ) {
						if ( _time2 != 0 )
							_time2 = GetTickCount( );

						text.pop_back( );
						setText( text );
					}
				}
				else {
					auto size = getSize();
					if (_textSize.x + 5 >= size.x)
						return true;
					auto text = getText();
					text.push_back(key);
					setText(text);
					if ( _time2 == 0 )
						OnStartWriting( ).Invoke( this );
					_time2 = GetTickCount( );
					OnCharacterAdded( ).Invoke( this, key );
				}
			}
			return __super::OnKeyDownChar( key );
		}

		void Textbox::setPasswordChar(const char &c)
		{
			_passC = c;
		}

		char Textbox::getPasswordChar()
		{
			return _passC;
		}

		void Textbox::setPassword(const bool &b)
		{
			_password = b;
		}

		bool Textbox::isPassword()
		{
			return _password;
		}

		Event<bool, Component*, char>& Textbox::OnCharacterAdded()
		{
			return _OnCharacterAdded;
		}

		Event<bool, Component*>& Textbox::OnStartWriting()
		{
			return _OnStartWriting;
		}

		Event<bool, Component*>& Textbox::OnStopWriting()
		{
			return _OnStopWriting;
		}


	}
}
