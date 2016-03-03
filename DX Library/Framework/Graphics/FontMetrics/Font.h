#pragma once
#include "../../Utils/String.h"

namespace Graphics {
	namespace Renderer { class D9Renderer; }
	namespace FontMetrics {

		class Font : public Object
		{
		private:
			friend class YRenderer;
			Utils::String _name;
			Utils::String _fontName;
			uint iSize, iWeight, iStyle, iOpt1, iOpt2, iOpt3, iOpt4;
			LPD3DXFONT _font;
			TEXTMETRICA metrics;
			Renderer::D9Renderer* _render;
		public:
			Font(Utils::String szSurfaceFontName, Utils::String szWinFontName, uint iSize, uint iWeight, void* render, uint iStyle = 0, uint iOpt1 = 0, uint iOpt2 = 0, uint iOpt3 = 0, uint iOpt4 = 0);

			inline LPD3DXFONT get() { return _font; }
			Utils::String surface() { return _name; }
			Utils::String windows() { return _fontName; }
			void Release() override;
			TEXTMETRICA* Metrics( );
			Renderer::D9Renderer* render( );
			
		};


	}
}