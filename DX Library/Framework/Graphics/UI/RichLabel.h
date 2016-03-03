#pragma once
#include "Component.h"



namespace Graphics {
	namespace UI {


		class Text
		{
		private:
			Utils::String text;
			Color color;
		public:
			Text( const Utils::String &text, const Color &color = D3DCOLOR_ARGB( 255, 255, 255, 255 ) );

			Utils::String getText( ) const;
			Color getColor( ) const;
		};

		class RichLabel : public Component
		{
		private:
			struct RichText
			{
				bool newline;
				Utils::String text;
				Color color;
			};
			std::vector<RichText> _texts;

		public:
			void Paint( Renderer::D9Renderer* ) override;


			void appendText( const Utils::String &text, const Color &color = D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
			Vector2 getTextSize_unsafe( Renderer::D9Renderer* );
			void popLast( );

			RichLabel& operator+=( const Text &other );
		};


	



	}
}


