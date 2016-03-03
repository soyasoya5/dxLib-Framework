#pragma once
#include "Component.h"


namespace Graphics {
	namespace UI {


		class Label : public Component
		{
		private:
			bool _selected;

		public:
			Label();
			void Paint( Renderer::D9Renderer* ) override;

			bool OnMouseMove( Vector2 ) override;
			bool OnLeftMouseDown( Vector2 ) override;
			bool OnLeftMouseUp( Vector2 ) override;
			bool OnLeftMouseDoubleClick( Vector2 ) override;
		};

		class LinkedLabel : public Component
		{
		private:
			Vector2 _textSize;
			std::string _link;

		public:
			void Paint(Renderer::D9Renderer*) override;

			bool OnMouseMove(Vector2) override;
			bool OnLeftMouseDown(Vector2) override;
			bool OnLeftMouseUp(Vector2) override;
			std::string getLink( );
			void setLink( const std::string& );


		};



	}
}