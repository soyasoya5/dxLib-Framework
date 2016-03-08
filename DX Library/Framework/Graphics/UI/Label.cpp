#include "Label.h"
#include "../Renderer/Renderer.h"

namespace Graphics {
	namespace UI {



		Label::Label()
		{
			this->OnTextChanged() += [&](Component*, Utils::String)
			{
				this->_selected = false;
				return true;
			};
		}

		void Label::Paint(Renderer::D9Renderer *r)
		{
			if ( !isVisible( ) )
				return;
			OnPrePaint().Invoke( this, r );

			setSize( r->StrSize( getFont( ), getText( ) ) );
			auto size = getSize( );
			auto pos = getAbsolutePosition() + getPadding();
			auto style = getStylesheet();
			auto color = style.get_argb( "ui_label", 0 );

			if (_selected)
				r->Rect( pos.x, pos.y, size.x, size.y, D3DCOLOR_ARGB(255, 0, 50, 170));

			r->String( pos.x, pos.y, getFont(), color, getText() );

			OnPostPaint( ).Invoke( this, r );
		}

		bool Label::OnMouseMove(Vector2 mouse)
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
				if ( _hovered )
					OnMouseLeave( ).Invoke( this, mouse );
				_hovered = false;
			}
			return __super::OnMouseMove( mouse );
		}

		bool Label::OnLeftMouseDown(Vector2 mouse)
		{
			if ( !isVisible( ) || !isEnabled( ) )
				return true;

			if ( Collides( mouse ) )
				_focusing = true;
			else {
				_focusing = false;
				_selected = false;
			}
			return __super::OnLeftMouseDown( mouse );
		}

		bool Label::OnLeftMouseUp(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;

			if (Collides(mouse))
			{
				OnComponentClicked().Invoke(this, mouse);
			}

			_focusing = false;
			return __super::OnLeftMouseUp(mouse);
		}

		bool Label::OnLeftMouseDoubleClick(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;
			if ( Collides( mouse ) )
				_selected = true;
			return __super::OnLeftMouseDoubleClick( mouse );
		}




		void LinkedLabel::Paint(Renderer::D9Renderer *r)
		{
			if (!isVisible())
				return;
			OnPrePaint().Invoke( this, r );

			auto pos = getAbsolutePosition() + getPadding();
			_textSize = r->StrSize(getFont(), getText());
			setSize( _textSize );
			
			auto size = getSize();
			if (isFocused())
			{
				r->String(pos.x, pos.y, getFont(), D3DCOLOR_ARGB(255, 0, 50, 200), getText());
				r->Line(pos.x, pos.y + size.y, pos.x + getSize().x, pos.y + size.y, D3DCOLOR_ARGB(255, 0, 150, 200));
			}
			else if (isHovered())
			{
				r->String(pos.x, pos.y, getFont(), D3DCOLOR_ARGB(255, 0, 100, 200), getText());
				r->Line(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, D3DCOLOR_ARGB(255, 0, 150, 255));
			}
			else
			{
				r->String(pos.x, pos.y, getFont(), D3DCOLOR_ARGB(255, 0, 157, 222), getText());
				r->Line(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, D3DCOLOR_ARGB(255, 0, 157, 222));
			}
			
			OnPostPaint().Invoke( this, r );
		}

		bool LinkedLabel::OnMouseMove(Vector2 mouse)
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

		bool LinkedLabel::OnLeftMouseDown(Vector2 mouse)
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

		bool LinkedLabel::OnLeftMouseUp(Vector2 mouse)
		{
			if (!isVisible() || !isEnabled())
				return true;

			if (Collides(mouse)) {
				OnComponentClicked().Invoke(this, mouse);
				ShellExecute(NULL, "open", _link.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}

			_focusing = false;
			return __super::OnLeftMouseUp(mouse);
		}



		std::string LinkedLabel::getLink()
		{
			return _link;
		}

		void LinkedLabel::setLink(const std::string &link)
		{
			_link = link;
		}


	}
}
