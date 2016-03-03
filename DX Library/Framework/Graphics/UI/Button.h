#pragma once
#include "Component.h"


namespace Graphics {
	namespace UI {

		/*
		Colors:
			ui_button_disabled { FOREGROUND, LINE, TEXT }
			ui_button_focus { FOREGROUND, LINE, TEXT }
			ui_button_hover { FOREGROUND, LINE, TEXT }
			ui_button { FOREGROUND, LINE, TEXT }
		*/

		class Button : public Component
		{
		public:
			void Paint( Renderer::D9Renderer* ) override;

			bool OnMouseMove( Vector2 ) override;
			bool OnLeftMouseDown( Vector2 ) override;
			bool OnLeftMouseUp( Vector2 ) override;
			bool OnRightMouseDown( Vector2 ) override;
			bool OnRightMouseUp( Vector2 ) override;
			bool OnKeyDown( uint ) override;
			bool OnKeyUp( uint ) override;
		};


	}
}
