#pragma once
class Win32Window;
#include "../../dx.h"
#include "../../Utils/string.h"

namespace Graphics {
	namespace FontMetrics { class Font; };
	namespace Renderer {


		class D9Renderer : public Object
		{
		private:
			std::mutex mutex;
			friend class Object;
			LPDIRECT3D9EX _d3d;
			LPDIRECT3DDEVICE9 _device;
			LPD3DXLINE _line;
			Win32Window* _windowptr;
			
			std::vector<FontMetrics::Font*> _fonts;

			D9Renderer() = default;
		public:
			D9Renderer(Win32Window* window);
			bool Create();
			bool Reset(Vector2 window_size);
			inline LPDIRECT3DDEVICE9 getDevice() { return _device; }

		public:
			LPD3DXFONT					getFontData(Utils::String name);
			FontMetrics::Font*			fontAt( const Utils::String &name );
			void						PrepareFont(Utils::String szSurfaceFontName, Utils::String szWinFontName, uint iSize, uint iWeight, uint iStyle = 0, uint iOpt1 = 0, uint iOpt2 = 0, uint iOpt3 = 0, uint iOpt4 = 0);
			void						BorderBox(float x, float y, float w, float h, uint thickness, D3DCOLOR color);
			void						BorderBoxOutlined(float x, float y, float w, float h, uint thickness, uint border_thickness, D3DCOLOR color, D3DCOLOR outline);
			void						Line(float x, float y, float xx, float yy, D3DCOLOR color);
			void						Rect(float x, float y, float w, float h, D3DCOLOR color);
			void						RectOutlined(float x, float y, float w, float h, float border_thickness, D3DCOLOR color, D3DCOLOR outlined);
			void						String(float x, float y, Utils::String szFont, D3DCOLOR color, Utils::String szString);
			void						Circle(float x, float y, float rad, D3DCOLOR color);
			void						Screenshot(Utils::String file);
			void						Begin(D3DCOLOR back);
			void						Begin();
			void						Present();
			Vector2						StrSize(Utils::String  font, const Utils::String &String);
			Vector2						StrSize(FontMetrics::Font*  font, const Utils::String &String);


			void Release() override;
		};

	}
}