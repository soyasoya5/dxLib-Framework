#pragma once
#include "Component.h"


namespace Graphics {
	namespace UI {

		class Checkbox : public Component
		{
		public:
			Checkbox();

			void Paint( Renderer::D9Renderer* ) override;

			bool OnMouseMove( Vector2 ) override;
			bool OnLeftMouseDown( Vector2 ) override;
			bool OnLeftMouseUp( Vector2 ) override;
			bool OnRightMouseDown( Vector2 ) override;
			bool OnRightMouseUp( Vector2 ) override;
			bool OnKeyDown( uint ) override;
			bool OnKeyUp( uint ) override;
			bool isChecked( ) { return static_cast<bool>( getState( ) ); }
		};


	}
}