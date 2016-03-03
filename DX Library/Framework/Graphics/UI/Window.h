#pragma once
#include "Component.h"


namespace Graphics {
	namespace UI {


		class Window : public Component
		{
		private:
			bool _top;
			Vector2 _moved;

		public:
			Window( );

			virtual void Paint( Renderer::D9Renderer* );
			virtual bool OnMouseMove( Vector2 );
			virtual bool OnLeftMouseDown( Vector2 );
			virtual bool OnLeftMouseUp( Vector2 );


			void setTopMost( const bool& );
			bool TopMost( );

		};

	}
}

