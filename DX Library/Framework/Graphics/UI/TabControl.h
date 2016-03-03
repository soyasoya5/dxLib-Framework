#pragma once
#include "Component.h"

namespace Graphics {
	namespace UI {
		
		class Tab : public Component
		{
		private:
			uint _idx;
		public:
			uint getIndex( );
			void setIndex( const uint& );
			Vector2 getStrSize( );
			void setStrSize( const Vector2& );

			void Paint( Renderer::D9Renderer* );
		
		};

		class TabControl : public Component
		{
		private:
			uint _selected;
			std::vector<Tab*> _tabs;
			Event<bool, TabControl*, uint> _OnSelectedTabChanged;
		public:
			std::vector<Tab*> getTabs( );
			void addTab( Tab* );

			void Paint( Renderer::D9Renderer* ) override;
			bool OnMouseMove( Vector2 ) override;
			bool OnLeftMouseDown( Vector2 ) override;
			bool OnLeftMouseUp( Vector2 ) override;
			bool OnRightMouseDown( Vector2 ) override;
			bool OnRightMouseUp( Vector2 ) override;
			bool OnLeftMouseDoubleClick( Vector2 ) override;
			bool OnRightMouseDoubleClick( Vector2 ) override;
			bool OnKeyDown( uint ) override;
			bool OnKeyUp( uint ) override;
			bool OnKeyDownChar( char ) override;

			bool TabCollides( const uint& idx, const Vector2& );
			bool CollidesWithChildren( const Vector2& ) override;
			
			Event<bool, TabControl*, uint>& OnSelectedTabChanged( );
		};

	}
}