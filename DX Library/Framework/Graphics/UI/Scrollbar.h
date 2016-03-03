#pragma once
#include "Component.h"


namespace Graphics {
	namespace UI {

		class Scrollbar : public Component
		{
		private:
			Vector2 _barPos, _barSize, _moved;
			bool _barhover, _barfocus, _clicking;


		public:
			float CalculateScroll( );
			float CalculateBar( );
			void UpdateBar();
			void UpdateScroll();
			int getScroll( );
			void setScroll( const int &id );
			Vector2 getBarPos( );
			void setBarPos( const Vector2& );
			Vector2 getBarSize( );
			void setBarSize( const Vector2& );

			bool BarCollides( const Vector2& );
		public:
			virtual void Paint( Renderer::D9Renderer* ) override;

			bool OnMouseMove( Vector2 ) override;
			bool OnLeftMouseDown( Vector2 ) override;
			bool OnLeftMouseUp( Vector2 ) override;
			bool OnRightMouseDown( Vector2 ) override;
			bool OnRightMouseUp( Vector2 ) override;
			bool OnKeyDown( uint ) override;
			bool OnKeyUp( uint ) override;
		};

		// Slider/Scrollbar is the same thing.
		typedef Scrollbar Trackbar;
		typedef Scrollbar Slider;


	}
}