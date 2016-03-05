#pragma once
#include "Component.h"
#include <atomic>


namespace Graphics {
	namespace UI {
		class RichLabel;
		class Scrollbar;

		class ListBox : public Component
		{
			std::vector<std::pair<Utils::String, Utils::String>> _todos;
			std::vector<RichLabel*> _items;
			Scrollbar* _bar;
			bool _reCalc;
			std::atomic<bool> _can;
			int _count;

			void setMaxCount( Renderer::D9Renderer* );
			bool ReOrder( Renderer::D9Renderer* );
			bool ReOrderNext( Renderer::D9Renderer* );
			Event<bool, Component*> _myOnItemSelected;
		public:
			ListBox();
			~ListBox();

			void Paint( Renderer::D9Renderer* );
			void Tick( ); 

			virtual bool OnMouseMove( Vector2 ) override;
			virtual bool OnLeftMouseDown( Vector2 ) override;
			virtual bool OnLeftMouseUp( Vector2 ) override;
			virtual bool OnKeyDown( uint ) override;
			virtual bool OnKeyUp( uint ) override;

			void setStylesheet( const Style::Stylesheet &sheet ) override;
			void setSize( const Vector2& vec ) override;
			void removeItem( const Utils::String &str );
			void removeItem( const int &idx );
			void ClearItems( );
			void addItem( const Utils::String &_Text, const Utils::String &value="" );
			void addItem( const Utils::String & _Text, const Utils::String &_Value, const Color & _Color  );
			void addItem_safe( const Utils::String& name, const Utils::String &value="" );

			std::vector<RichLabel*> Range( ) { return _items; }
			Event<bool, Component*>& OnItemSelected();
		};

	}
}