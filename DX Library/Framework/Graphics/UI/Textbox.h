#pragma once
#include "Component.h"


namespace Graphics {
	namespace UI {

		// BRB

		class Textbox : public Component
		{
		private:
			uint _timeBuffer, _time2;
			bool _blink, _password;
			char _passC;
			Vector2 _textSize;
			Event<bool, Component*, char> _OnCharacterAdded;
			Event<bool, Component*> _OnStartWriting, _OnStopWriting;
		public:
			void Paint( Renderer::D9Renderer* ) override;

			void Tick( ) override;
			bool OnMouseMove( Vector2 ) override;
			bool OnLeftMouseDown( Vector2 ) override;
			bool OnLeftMouseUp( Vector2 ) override;
			bool OnRightMouseDown( Vector2 ) override;
			bool OnRightMouseUp( Vector2 ) override;
			bool OnKeyDown( uint ) override;
			bool OnKeyUp( uint ) override;
			bool OnKeyDownChar( char ) override;
			bool isChecked( ) { return static_cast<bool>( getState( ) ); }

			void setPasswordChar( const char& );
			char getPasswordChar( );

			void setPassword( const bool& );
			bool isPassword( );
			Event<bool, Component*, char>& OnCharacterAdded( );
			Event<bool, Component*>& OnStartWriting( );
			Event<bool, Component*>& OnStopWriting( );
		};



	}
}


