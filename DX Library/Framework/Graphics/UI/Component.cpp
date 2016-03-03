#include "Component.h"

namespace Graphics {
	namespace UI {
		
		Component::Component()
			: _visible(true), _enabled(true)
		{
		}

		Component::~Component()
		{
			Release( );
		}

		Style::Stylesheet Component::getStylesheet()
		{
			return _style;
		}

		void Component::setStylesheet(const Style::Stylesheet &style)
		{
			_style = style;
			_OnStyleChanged.Invoke( this, _style );
			for ( auto& x : _children )
				x->setStylesheet( style );
		}

		Vector2 Component::getAbsolutePosition()
		{
			return _abs;
		}

		void Component::setAbsolutePosition(const Vector2 &abs)
		{
			_abs = abs;
			_OnAbsolutePositionChanged.Invoke( this, _abs );

			for (auto& x : _children)
				x->setAbsolutePosition(_abs + _pos);
		}

		Vector2 Component::getPadding()
		{
			return _pos;
		}

		void Component::setPadding(const Vector2 &pos)
		{
			_pos = pos;
			_OnPaddingChanged.Invoke( this, _pos );
		}

		Vector2 Component::getSize()
		{
			return _size;
		}

		void Component::setSize(const Vector2 &size)
		{
			_size = size;
			_OnSizeChanged.Invoke( this, _size );
		}

		Utils::String Component::getName()
		{
			return _name;
		}

		void Component::setName(const Utils::String &name)
		{
			_name = name;
			_OnNameChanged.Invoke( this, _name );
		}

		Utils::String Component::getText()
		{
			return _text;
		}

		void Component::setText(const Utils::String &text)
		{
			_text = text;
			_OnTextChanged.Invoke( this, _text );
		}

		Utils::String Component::getHiddenText()
		{
			return _hidden_text;
		}

		void Component::setHiddenText(const Utils::String &hidden_text)
		{
			_hidden_text = hidden_text;
			_OnHiddenTextChanged.Invoke( this, _hidden_text );
		}

		Utils::String Component::getFont()
		{
			return _font;
		}

		void Component::setFont(const Utils::String &font)
		{
			_font = font;
			_OnFontChanged.Invoke( this, _font );
		}

		int Component::getMin()
		{
			return _min;
		}

		void Component::setMin(const int &min)
		{
			_min = min;
			_OnMinChanged.Invoke( this, _min );
		}

		int Component::getMax()
		{
			return _max;
		}

		void Component::setMax(const int &max)
		{
			_max = max;
			_OnMaxChanged.Invoke( this, _max );
		}

		int Component::getState()
		{
			return _state;
		}

		void Component::setState(const int &state)
		{
			auto kek = state;
			if (state > _max)
				kek = _max;
			if (state < _min)
				kek = _min;

			_state = kek;
			_OnStateChanged.Invoke( this, _state );
		}

		Allignment Component::getAllignment()
		{
			return _allign;
		}

		void Component::setAllignment(const Allignment &allign)
		{
			_allign = allign;
			_OnAllignmentChanged.Invoke( this, _allign );
		}

		Type Component::getType()
		{
			return _type;
		}

		void Component::setType(const Type &type)
		{
			_type = type;
			_OnTypeChanged.Invoke( this, _type );
		}

		Component * Component::getParent()
		{
			return _parent;
		}

		void Component::setParent(Component *parent)
		{
			_parent = parent;
			_OnParentChanged.Invoke( this, _parent );
		}

		void * Component::getUserdata()
		{
			return _userdata;
		}

		void Component::setUserdata(void *data)
		{
			_userdata = data;
		}

		std::vector<Component*> Component::getChildren()
		{
			return _children;
		}

		void Component::addChild(Component *child)
		{
			_children.push_back(child);
			child->setAbsolutePosition( _pos + _abs );
			child->setParent(this);
			_OnChildAdded.Invoke( this, child );
		}

		void Component::removeChild(Component *c)
		{
			for ( auto it = _children.begin( ); it < _children.end( ); ++it )
			{
				if ( *it == c )
				{
					_children.erase( it );
					break;
				}
			}
		}

		void Component::removeChild(const Utils::String &name)
		{
			for ( auto it = _children.begin( ); it < _children.end( ); ++it )
			{
				if ( (*it)->getName( ) == name )
				{
					_children.erase( it );
					break;
				}
			}
		}

		void Component::addChildRaw(Component *child)
		{
			_children.push_back(child);
			_OnChildAdded.Invoke(this, child);
		}

		bool Component::isEnabled()
		{
			return _enabled;
		}

		void Component::setEnabled(const bool &enabled)
		{
			_enabled = enabled;
			_OnEnabledChanged.Invoke( this, _enabled );
			for (auto& x : _children)
				x->setEnabled(enabled);
		}

		bool Component::isVisible()
		{
			return _visible;
		}

		void Component::setVisible(const bool &visible)
		{
			_visible = visible;
			_OnVisibleChanged.Invoke( this, _visible );
			for (auto& x : _children)
				x->setVisible(visible);
		}

		bool Component::isFocused()
		{
			return _focusing;
		}

		bool Component::isHovered()
		{
			return _hovered;
		}

		void Component::setAnimationHandler(Anim::AnimationHandler *anim)
		{
			if ( _current_anim )
				delete _current_anim;
			_current_anim = anim;
			_current_anim->setComponent( this );
		}

		Anim::AnimationHandler * Component::getAnimationHandler()
		{
			return _current_anim;
		}

		bool Component::BeginAnimation()
		{
			if ( !_animating )
				ForceEndAnimation( );
			_animating = true;
			_current_anim->Start( );
			return true;
		}

		bool Component::ForceEndAnimation()
		{
			if ( !_animating )
				return false;
			_animating = false;
			_current_anim->Stop( );
			_current_anim->getTick( )->set_anim_complete( false );
			_current_anim->getTick( )->set_did_action( false );
			return true;
		}

		Component * Component::get_child_of(const std::function<bool(Component*)> &functor)
		{
			for (auto& x : _children)
			{
				if (functor(x))
					return x;

				auto c = x->get_child_of( functor );
				if ( c )
					return c;
			}
			return nullptr;
		}

		Component * Component::get_last_child_of(const std::function<bool(Component*)> &functor)
		{
			Component* last = nullptr;
			for (auto& x : _children)
			{
				if (functor(x))
					last = x;
			}
			return last;
		}

		std::vector<Component*> Component::get_all_children_of(const std::function<bool(Component*)> &functor)
		{
			std::vector<Component*> vec;
			for (auto& x : _children)
				if (functor(x))
					vec.push_back( x );
			return vec;
		}

		Component *Component::get_child_of_name(const Utils::String &name)
		{
			return get_child_of([&](Component* lhs)
			{
				if (lhs->getName( ) == name)
					return true;
				return false;
			} );
		}

		Component * Component::get_child_of_type(const Type &type)
		{
			return get_child_of([&](Component* lhs)
			{
				if (lhs->getType() == type)
					return true;
				return false;
			});
		}

		Component * Component::get_child_of_allignment(const Allignment &allign)
		{
			return get_child_of([&](Component* lhs)
			{
				if (lhs->getAllignment() == allign)
					return true;
				return false;
			});
		}

		Component *Component::get_child_with_string(const Utils::String &str)
		{
			return get_child_of([&](Component* lhs)
			{
				if (lhs->getName() == str)
					return true;
				else if (lhs->getFont() == str)
					return true;
				else if (lhs->getText() == str)
					return true;
				else if (lhs->getHiddenText() == str)
					return true;
				return false;
			});
		}

		Component * Component::get_child_with_strstr(const Utils::String &str)
		{
			return get_child_of( [&](Component* lhs)
			{
				if ( lhs->getName( ).contains( str ) )
					return true;
				else if ( lhs->getFont( ).contains( str ) )
					return true;
				else if ( lhs->getText( ).contains( str ) )
					return true;
				else if ( lhs->getHiddenText( ).contains(str) )
					return true;
				return false;
			} );
		}

		Component * Component::get_last_child_of_name(const Utils::String &name)
		{
			return get_last_child_of([&](Component* lhs)
			{
				if ( lhs->getName( ) == name )
					return true;
				return false;
			});
		}

		Component * Component::get_last_child_of_type(const Type &type)
		{
			return get_last_child_of([&](Component* lhs)
			{
				if ( lhs->getType( ) == type )
					return true;
				return false;
			});
		}

		Component * Component::get_last_child_of_allignment(const Type &allign)
		{
			return get_last_child_of([&](Component* lhs)
			{
				if ( lhs->getAllignment( ) == allign )
					return true;
				return false;
			});
		}

		Component * Component::get_last_child_with_string(const Utils::String &str)
		{
			return get_last_child_of([&](Component* lhs)
			{
				if ( lhs->getName( ) == str )
					return true;
				else if ( lhs->getFont( ) == str )
					return true;
				else if ( lhs->getText( ) == str )
					return true;
				else if ( lhs->getHiddenText( ) == str )
					return true;
				return false;
			});
		}

		Component * Component::get_last_child_with_strstr(const Utils::String &str)
		{
			return get_last_child_of([&](Component* lhs)
			{
				if ( lhs->getName( ).contains( str ) )
					return true;
				else if ( lhs->getFont( ).contains( str ) )
					return true; 
				else if ( lhs->getText( ).contains( str ) )
					return true;
				else if ( lhs->getHiddenText( ).contains( str ) )
					return true;
				return false;
			});
		}

		std::vector<Component*> Component::get_all_children_of_name(const Utils::String &name)
		{
			return get_all_children_of([&](Component* lhs)
			{
				if (lhs->getName( ) == name)
					return true;
				return false;
			});
		}

		std::vector<Component*> Component::get_all_children_of_type(const Type &type)
		{
			return get_all_children_of([&](Component* lhs)
			{
				if (lhs->getType( ) == type)
					return true;
				return false;
			});
		}

		std::vector<Component*> Component::get_all_children_of_allignment(const Allignment &allign)
		{
			return get_all_children_of([&](Component* lhs)
			{
				if (lhs->getAllignment( ) == allign)
					return true;
				return false;
			});
		}

		std::vector<Component*> Component::get_all_children_with_string(const Utils::String &str)
		{
			return get_all_children_of([&](Component* lhs)
			{
				if (lhs->getName( ) == str)
					return true;
				else if (lhs->getFont( ) == str)
					return true;
				else if (lhs->getText( ) == str)
					return true;
				else if (lhs->getHiddenText( ) == str)
					return true;
				return false;
			});
		}

		std::vector<Component*> Component::get_all_children_with_strstr(const Utils::String &str)
		{
			return get_all_children_of([&](Component* lhs)
			{
				if ( lhs->getName( ).contains( str ) )
					return true;
				else if ( lhs->getFont( ).contains( str ) )
					return true;
				else if ( lhs->getText( ).contains( str ) )
					return true;
				else if ( lhs->getHiddenText( ).contains( str ) )
					return true;
				return false;
			});
		}

		void Component::Release()
		{
			OnRelease( ).Invoke( this );
			for ( auto&x : _children ) {
				x->Release( );
				delete x;
			}
			_children.clear( );
		}

		bool Component::OnMouseMove(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;

			for ( auto& x : _children )
				x->OnMouseMove( mouse );
			return true;
		}

		bool Component::OnLeftMouseDown(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;

			for ( auto& x : _children )
				x->OnLeftMouseDown( mouse );
			return true;
		}

		bool Component::OnLeftMouseUp(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;

			for ( auto& x : _children )
				x->OnLeftMouseUp( mouse );
			return true;
		}

		bool Component::OnRightMouseDown(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;

			for ( auto& x : _children )
				x->OnRightMouseDown( mouse );
			return true;
		}

		bool Component::OnRightMouseUp(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;

			for ( auto& x : _children )
				x->OnRightMouseUp( mouse );
			return true;
		}

		bool Component::OnLeftMouseDoubleClick(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;
			for (auto& x : _children)
				x->OnLeftMouseDoubleClick(mouse);
			return true;
		}

		bool Component::OnRightMouseDoubleClick(Vector2 mouse)
		{
			if (!_enabled || !_visible)
				return true;
			for (auto& x : _children)
				x->OnRightMouseDoubleClick(mouse);
			return true;
		}

		bool Component::OnKeyDown(uint key)
		{
			if (!_enabled || !_visible)
				return true;

			for (auto& x : _children)
				x->OnKeyDown(key);
			return true;
		}

		bool Component::OnKeyUp(uint key)
		{
			if (!_enabled || !_visible)
				return true;

			for (auto& x : _children)
				x->OnKeyUp(key);
			return true;
		}

		bool Component::OnKeyDownChar(char key)
		{
			if (!_enabled || !_visible)
				return true;

			for (auto& x : _children)
				x->OnKeyDownChar(key);
			return true;
		}

		void Component::Tick()
		{

			if ( _animating && _current_anim )
			{
				_current_anim->Tick( );
			}

			if ( _current_anim && _current_anim->isCompleted( ) )
			{
				OnAnimationCompleted().Invoke( this, _current_anim );
				ForceEndAnimation( );
			}

			for ( auto&x : _children )
				x->Tick( );
		}

		bool Component::Collides(Component *r)
		{
			return Collides(
				r->getAbsolutePosition() + r->getPadding()
				);
		}

		bool Component::Collides(const Vector2 &mouse)
		{
			auto m_pos = getAbsolutePosition() + getPadding();
			auto m_size = getSize();
			return mouse.x >= m_pos.x && mouse.x <= (m_pos.x + m_size.x) &&
				mouse.y >= m_pos.y && mouse.y <= (m_pos.y + m_size.y);
		}

		bool Component::CollidesWithChildren(const Vector2 &mouse)
		{
			for ( auto x : getChildren( ) )
				if ( x->Collides( mouse ) || x->CollidesWithChildren( mouse ) )
					return true;
			return false;
		}

		Event<bool, Component*, Vector2>& Component::OnAbsolutePositionChanged()
		{
			return _OnAbsolutePositionChanged;
		}

		Event<bool, Component*, Vector2>& Component::OnPaddingChanged()
		{
			return _OnPaddingChanged;
		}

		Event<bool, Component*, Vector2>& Component::OnSizeChanged()
		{
			return _OnSizeChanged;
		}

		Event<bool, Component*, Style::Stylesheet>& Component::OnStyleChanged()
		{
			return _OnStyleChanged;
		}

		Event<bool, Component*, Utils::String>& Component::OnNameChanged()
		{
			return _OnNameChanged;
		}

		Event<bool, Component*, Utils::String>& Component::OnTextChanged()
		{
			return _OnTextChanged;
		}

		Event<bool, Component*, Utils::String>& Component::OnHiddenTextChanged()
		{
			return _OnHiddenTextChanged;
		}

		Event<bool, Component*, Utils::String>& Component::OnFontChanged()
		{
			return _OnFontChanged;
		}

		Event<bool, Component*, Vector2>& Component::OnMouseEnter()
		{
			return _OnMouseEnter;
		}

		Event<bool, Component*, Vector2>& Component::OnMouseLeave()
		{
			return _OnMouseLeave;
		}

		Event<bool, Component*, Vector2>& Component::OnComponentClicked()
		{
			return _OnComponentClicked;
		}

		Event<bool, Component*, Renderer::D9Renderer*>& Component::OnPrePaint()
		{
			return _OnPrePaint;
		}

		Event<bool, Component*, Renderer::D9Renderer*>& Component::OnPostPaint()
		{
			return _OnPostPaint;
		}

		Event<bool, Component*, Component*>& Component::OnParentChanged()
		{
			return _OnParentChanged;
		}

		Event<bool, Component*, Component*>& Component::OnChildAdded()
		{
			return _OnChildAdded;
		}

		Event<bool, Component*, int>& Component::OnMinChanged()
		{
			return _OnMinChanged;
		}

		Event<bool, Component*, int>& Component::OnMaxChanged()
		{
			return _OnMaxChanged;
		}

		Event<bool, Component*, int>& Component::OnStateChanged()
		{
			return _OnStateChanged;
		}

		Event<bool, Component*, Allignment>& Component::OnAllignmentChanged()
		{
			return _OnAllignmentChanged;
		}

		Event<bool, Component*, Type>& Component::OnTypeChanged()
		{
			return _OnTypeChanged;
		}

		Event<bool, Component*, bool>& Component::OnVisibleChanged()
		{
			return _OnVisibleChanged;
		}

		Event<bool, Component*, bool>& Component::OnEnabledChanged()
		{
			return _OnEnabledChanged;
		}

		Event<bool, Component*, Anim::AnimationHandler*>& Component::OnNewAnimationHandler()
		{
			return _OnNewAnimationHandler;
		}

		Event<bool, Component*, Anim::AnimationHandler*>& Component::OnAnimationBegun()
		{
			return _OnAnimationBegun;
		}

		Event<bool, Component*, Anim::AnimationHandler*>& Component::OnAnimationForceComplete()
		{
			return _OnAnimationForceComplete;
		}

		Event<bool, Component*, Anim::AnimationHandler*>& Component::OnAnimationCompleted()
		{
			return _OnAnimationCompleted;
		}

		Event<bool, Component*>& Component::OnRelease()
		{
			return _OnRelease;
		}

	}
}