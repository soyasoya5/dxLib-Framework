#pragma once
#include "../../dx.h"
#include "../Stylesheet/Stylesheet.h"
#include "../../Event/EventHandler.h"
#include "../../Utils/string.h"
#include "Anim\Anim.h"



namespace Graphics {
	namespace Renderer { class D9Renderer; }

	namespace UI {

		enum Allignment : uint // Text alligment
		{
			Left,
			Right,
			Middle
		};

		enum Type // E.g a slider
		{
			Horizontal,
			Vertical
		};

		class Component : public Object
		{
		private:
			Style::Stylesheet _style;
			Vector2 _abs, _pos, _size;
			Utils::String _name, _text, _hidden_text, _font;
			int _min, _max, _state;
			Allignment _allign;
			Type _type;
			Component* _parent;
			std::vector<Component*> _children;
			Anim::AnimationHandler* _current_anim;
			bool _enabled, _visible;
			bool _animating;
			void* _userdata;
			
		protected:
			bool _hovered, _focusing;

		private: // Events
			Event<bool, Component*, Vector2> _OnAbsolutePositionChanged, _OnPaddingChanged, _OnSizeChanged;
			Event<bool, Component*, Style::Stylesheet> _OnStyleChanged;
			Event<bool, Component*, Utils::String> _OnNameChanged, _OnTextChanged, _OnHiddenTextChanged, _OnFontChanged;
			Event<bool, Component*, Vector2> _OnMouseEnter, _OnMouseLeave, _OnComponentClicked;
			Event<bool, Component*, Renderer::D9Renderer*> _OnPrePaint, _OnPostPaint;
			Event<bool, Component*, Component*> _OnParentChanged, _OnChildAdded;
			Event<bool, Component*, int> _OnMinChanged, _OnMaxChanged, _OnStateChanged;
			Event<bool, Component*, Allignment> _OnAllignmentChanged;
			Event<bool, Component*, Type> _OnTypeChanged;
			Event<bool, Component*, bool> _OnVisibleChanged, _OnEnabledChanged;
			Event<bool, Component*, Anim::AnimationHandler*> _OnNewAnimationHandler;
			Event<bool, Component*, Anim::AnimationHandler*> _OnAnimationBegun;
			Event<bool, Component*, Anim::AnimationHandler*> _OnAnimationForceComplete;
			Event<bool, Component*, Anim::AnimationHandler*> _OnAnimationCompleted;    
			Event<bool, Component*> _OnRelease;
		public:
			Component( );
			virtual ~Component( );

			// Returns the current stylesheet
			Style::Stylesheet getStylesheet( );
			virtual void setStylesheet( const Style::Stylesheet& );

			// Returns the Absolute position of the component (it is drawn at absolute + padding)
			Vector2 getAbsolutePosition( );
			virtual void setAbsolutePosition( const Vector2& );

			// Returns the padding of the component
			Vector2 getPadding( );
			virtual void setPadding( const Vector2& );

			// Returns the size of the component
			Vector2 getSize( );
			virtual void setSize( const Vector2& );

			// Returns the name of the component
			Utils::String getName( );
			virtual void setName( const Utils::String& );

			// Returns the text of the component
			Utils::String getText( );
			virtual void setText( const Utils::String& );

			// Returns the 'hidden' text (It isn't really hidden, it'll only be used for e.g textboxes when nothing has been entered)
			Utils::String getHiddenText( );
			virtual void setHiddenText( const Utils::String& );

			// Returns the font for the current component.
			Utils::String getFont( );
			virtual void setFont( const Utils::String& );

			// Returns the minimum state value for the current component.
			int getMin( );
			virtual void setMin( const int& );

			// Returns the maximum state value for the current component.
			int getMax( );
			virtual void setMax( const int& );

			// Returns the state for the current component. (E.g information about the component)
			int getState( );
			virtual void setState( const int& );

			// Returns the allignment (e.g the allignment of text in a textbox)
			Allignment getAllignment( );
			virtual void setAllignment( const Allignment& );

			// Returns the type (e.g if a scroll bar is vertical or horizontal)
			Type getType( );
			virtual void setType( const Type& );

			// Returns the parent
			Component* getParent( );
			virtual void setParent( Component* );

			// Sets a ptr.
			void* getUserdata( );
			void setUserdata( void* );

			// Returns all children
			std::vector<Component*> getChildren( );
			void addChild( Component* );
			void removeChild( Component* );
			void removeChild( const Utils::String& );
			void addChildRaw( Component* ); // < Add child without setting any thing like parent, absolute pos etc.

			// Returns wether the item is enabled (If it is not enabled controls will not work but it is still drawn)
			bool isEnabled( );
			virtual void setEnabled( const bool& );
			
			// Returns wether or not the item is visible
			bool isVisible( );
			virtual void setVisible( const bool& );

			// Returns wether or not the item is currently focused
			bool isFocused( );

			// Returns wether or not the item is currently hovered
			bool isHovered( );

			virtual void setAnimationHandler( Anim::AnimationHandler* );
			Anim::AnimationHandler* getAnimationHandler( );

			bool BeginAnimation( );
			bool ForceEndAnimation( );
			
		public: // Complex child searching
			// Custom functor for comparing a component with something else.
			Component* get_child_of( const std::function<bool(Component*)>& );
			Component* get_last_child_of( const std::function<bool(Component*)>& );
			std::vector<Component*> get_all_children_of( const std::function<bool(Component*)>& );

			// Returns the first component found that matches the argument
			Component* get_child_of_name(const Utils::String&);
			Component* get_child_of_type(const Type& type);
			Component* get_child_of_allignment(const Allignment&);
			Component* get_child_with_string( const Utils::String& );
			Component* get_child_with_strstr( const Utils::String& );

			// Returns the last component found that matches the argument
			Component* get_last_child_of_name( const Utils::String& );
			Component* get_last_child_of_type( const Type& );
			Component* get_last_child_of_allignment( const Type& );
			Component* get_last_child_with_string( const Utils::String& );
			Component* get_last_child_with_strstr( const Utils::String& );


			// Returns all the components that matches the argument
			std::vector<Component*> get_all_children_of_name( const Utils::String& );
			std::vector<Component*> get_all_children_of_type( const Type& );
			std::vector<Component*> get_all_children_of_allignment( const Allignment& );
			std::vector<Component*> get_all_children_with_string( const Utils::String& );
			std::vector<Component*> get_all_children_with_strstr( const Utils::String& );
		public: // Virtuals
			virtual void Release( );

			// Default implementations do NOT handle collisions etc.
			virtual bool OnMouseMove( Vector2 );
			virtual bool OnLeftMouseDown( Vector2 );
			virtual bool OnLeftMouseUp( Vector2 );
			virtual bool OnRightMouseDown( Vector2 );
			virtual bool OnRightMouseUp( Vector2 );
			virtual bool OnLeftMouseDoubleClick( Vector2 );
			virtual bool OnRightMouseDoubleClick( Vector2 );
			virtual bool OnKeyDown( uint );
			virtual bool OnKeyUp( uint );
			virtual bool OnKeyDownChar( char );
			virtual void Paint( Renderer::D9Renderer* ) = 0;
			virtual void Tick( );
			virtual bool Collides( Component* );
			virtual bool Collides( const Vector2& );
			virtual bool CollidesWithChildren( const Vector2& );

		public:
			Event<bool, Component*, Vector2>& OnAbsolutePositionChanged( );
			Event<bool, Component*, Vector2>& OnPaddingChanged( );
			Event<bool, Component*, Vector2>& OnSizeChanged( );
			Event<bool, Component*, Style::Stylesheet>& OnStyleChanged( );
			Event<bool, Component*, Utils::String>& OnNameChanged( );
			Event<bool, Component*, Utils::String>& OnTextChanged( );
			Event<bool, Component*, Utils::String>& OnHiddenTextChanged( );
			Event<bool, Component*, Utils::String>& OnFontChanged( );
			Event<bool, Component*, Vector2>& OnMouseEnter( );
			Event<bool, Component*, Vector2>& OnMouseLeave( );
			Event<bool, Component*, Vector2>& OnComponentClicked( );
			Event<bool, Component*, Renderer::D9Renderer*>& OnPrePaint( );
			Event<bool, Component*, Renderer::D9Renderer*>& OnPostPaint( );
			Event<bool, Component*, Component*>& OnParentChanged( );
			Event<bool, Component*, Component*>& OnChildAdded( );
			Event<bool, Component*, int>& OnMinChanged( );
			Event<bool, Component*, int>& OnMaxChanged( );
			Event<bool, Component*, int>& OnStateChanged( );
			Event<bool, Component*, Allignment>& OnAllignmentChanged( );
			Event<bool, Component*, Type>& OnTypeChanged( );
			Event<bool, Component*, bool>& OnVisibleChanged( );
			Event<bool, Component*, bool>& OnEnabledChanged( );
			Event<bool, Component*, Anim::AnimationHandler*>& OnNewAnimationHandler( );
			Event<bool, Component*, Anim::AnimationHandler*>& OnAnimationBegun( );
			Event<bool, Component*, Anim::AnimationHandler*>& OnAnimationForceComplete( );
			Event<bool, Component*, Anim::AnimationHandler*>& OnAnimationCompleted( );
			Event<bool, Component*>& OnRelease( );
		};

	}
}