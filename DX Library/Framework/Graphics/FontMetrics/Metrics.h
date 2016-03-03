#pragma once
#include "../../dx.h"
#include "../../Utils/string.h"

namespace Graphics {
	namespace FontMetrics {
		class Font;

		class Metrics
		{
		private:
			Font* _font;

		public:
			Metrics( Font* font );

			
			float MaxHeight( );
			float MaxWidth( );
			float AvgWidth( );
		
			Vector2 SizeOfString( const Utils::String &string );
		};


	}
}