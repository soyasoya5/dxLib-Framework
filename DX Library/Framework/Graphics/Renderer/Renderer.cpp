#include "Renderer.h"
#include "../../Window/Win32Window.h"
#include "../FontMetrics/Font.h"


namespace Graphics {
	namespace Renderer {

		D9Renderer::D9Renderer(Win32Window * window)
		{
			/*if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &_d3d)))
				return;

			D3DPRESENT_PARAMETERS params;
			ZeroMemory(&params, sizeof(params));
			params.hDeviceWindow = window->getHWND();
			params.SwapEffect = D3DSWAPEFFECT_DISCARD;
			params.Windowed = TRUE;

			RECT win;
			GetWindowRect(window->getHWND(), &win);

			params.BackBufferWidth = win.right;//getWindowFromHWND(m_hWnd)->getWidth();
			params.BackBufferHeight = win.bottom;//getWindowFromHWND(m_hWnd)->getHeight();
			params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

			if (SUCCEEDED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->getHWND(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &_device)))
				window->_render = this;*/
			_windowptr = window;
		}

		bool D9Renderer::Create()
		{
			if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &_d3d)))
				return false;

			D3DPRESENT_PARAMETERS params;
			ZeroMemory(&params, sizeof(params));
			params.Windowed = TRUE;
			params.SwapEffect = D3DSWAPEFFECT_DISCARD;
			params.BackBufferFormat = D3DFMT_A8R8G8B8;
			params.EnableAutoDepthStencil = TRUE;
			params.AutoDepthStencilFormat = D3DFMT_D16;
			params.MultiSampleType = D3DMULTISAMPLE_NONE;
			params.BackBufferWidth = this->_windowptr->getParams().size.x;
			params.BackBufferHeight = this->_windowptr->getParams().size.y;
			params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

			if (SUCCEEDED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _windowptr->_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &_device)))
				return true;
			return false;
		}

		bool D9Renderer::Reset(Vector2 window_size)
		{
			D3DPRESENT_PARAMETERS params;
			ZeroMemory(&params, sizeof(params));
			params.Windowed = TRUE;
			params.SwapEffect = D3DSWAPEFFECT_DISCARD;
			params.BackBufferFormat = D3DFMT_A8R8G8B8;
			params.EnableAutoDepthStencil = TRUE;
			params.AutoDepthStencilFormat = D3DFMT_D16;
			params.MultiSampleType = D3DMULTISAMPLE_NONE;
			params.BackBufferWidth = window_size.x;
			params.BackBufferHeight = window_size.y;
			params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			return SUCCEEDED(_device->Reset(&params));
		}

		LPD3DXFONT D9Renderer::getFontData(Utils::String name)
		{
			for (auto&x : _fonts)
				if (x->surface() == name)
					return x->get();
			return nullptr;
		}

		FontMetrics::Font * D9Renderer::fontAt(const Utils::String & name)
		{
			for ( auto&x : _fonts)
				if ( x->surface( ) == name )
					return x;
			return nullptr;
		}

		void D9Renderer::PrepareFont(Utils::String szSurfaceFontName, Utils::String szWinFontName, uint iSize, uint iWeight, uint iStyle, uint iOpt1, uint iOpt2, uint iOpt3, uint iOpt4)
		{
			_fonts.emplace_back(
				new FontMetrics::Font(szSurfaceFontName, szWinFontName, iSize, iWeight, this, iStyle, iOpt1, iOpt2, iOpt3, iOpt4)
				);
		}

		void D9Renderer::BorderBox(float x, float y, float w, float h, uint thickness, D3DCOLOR color)
		{
//			std::lock_guard<std::mutex> lock( mutex );
			Rect(x, y, w, thickness, color);
			Rect(x, y, thickness, h, color);
			Rect(x + w, y, thickness, h, color);
			Rect(x, y + h, w + thickness, thickness, color);
		}

		void D9Renderer::BorderBoxOutlined(float x, float y, float w, float h, uint thickness, uint border_thickness, D3DCOLOR color, D3DCOLOR outlined)
		{
//			std::lock_guard<std::mutex> lock( mutex );
			BorderBox(x, y, w, h, thickness, color);
			BorderBox(x - border_thickness, y - border_thickness, w + border_thickness + thickness, h + border_thickness + thickness, border_thickness, outlined);
			BorderBox(x + thickness, y + thickness, w - border_thickness - thickness, h - border_thickness - thickness, border_thickness, outlined);
		}

		void D9Renderer::Line(float x, float y, float xx, float yy, D3DCOLOR color)
		{
//			std::lock_guard<std::mutex> lock( mutex );
			if (_line == nullptr)
			{
				if (FAILED(D3DXCreateLine(_device, &_line)))
					return;

				if (!_line)
					return;

				_line->SetWidth(1.f);
				_line->SetPattern(0xFFFFFFFF);
				_line->SetAntialias(TRUE);
			}

			_line->SetWidth(1);
			D3DXVECTOR2 points[2];
			points[0].x = (FLOAT)x;
			points[0].y = (FLOAT)y;
			points[1].x = (FLOAT)xx;
			points[1].y = (FLOAT)yy;
			_line->Draw(points, 2, color);
		}

		void D9Renderer::Rect(float x, float y, float w, float h, D3DCOLOR color)
		{
//			std::lock_guard<std::mutex> lock( mutex );
			static D3DRECT rect_angle;
			rect_angle = { static_cast<LONG>(x), static_cast<LONG>(y), static_cast<LONG>(x + w), static_cast<LONG>(y + h) };//{ (LONG)x, (LONG)y, (LONG)x + w, (LONG)y + h };
			_device->Clear(1, &rect_angle, D3DCLEAR_TARGET, color, 1.f, 0);
		}

		void D9Renderer::RectOutlined(float x, float y, float w, float h, float border_thickness, D3DCOLOR color, D3DCOLOR outlined)
		{
//			std::lock_guard<std::mutex> lock( mutex );
			Rect(x, y, w, h, color);
			BorderBox(x - border_thickness, y - border_thickness, w + border_thickness, h + border_thickness, border_thickness, outlined);
		}

		void D9Renderer::String(float x, float y, Utils::String szFont, D3DCOLOR color, Utils::String szString)
		{
//			std::lock_guard<std::mutex> lock( mutex );
			auto font = getFontData(szFont);
			if (!font)
				return;

			static RECT rect_angle;
			rect_angle = { static_cast<LONG>(x), static_cast<LONG>(y), static_cast<LONG>(x + 500), static_cast<LONG>(y + 200) };
			(font)->DrawTextA(nullptr, szString.c_str(), -1, &rect_angle, DT_TOP, color);
		}


		void D9Renderer::Circle(float x, float y, float rad, D3DCOLOR color)
		{
//			std::lock_guard<std::mutex> lock( mutex );
#define D3DFVF_TL (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
			struct D3DTLVERTEX
			{
				float fX;
				float fY;
				float fZ;
				float fRHW;
				D3DCOLOR Color;
				float fU;
				float fV;
			};
			auto CreateD3DTLVERTEX = [&](float X, float Y, float Z, float RHW,
				D3DCOLOR color, float U, float V)
			{
				D3DTLVERTEX v;
				v.fX = X;
				v.fY = Y;
				v.fZ = Z;
				v.fRHW = RHW;
				v.Color = color;
				v.fU = U;
				v.fV = V;
				return v;
			};
			static const int NUMPOINTS = 100;
			static float PI = 3.14159;
			D3DTLVERTEX Circle[NUMPOINTS + 1];
			static int i;
			static float X;
			static float Y;
			static float Theta;
			static float WedgeAngle;	//Size of angle between two points on the circle (single wedge)
			i = X = Y = Theta = WedgeAngle = 0;
			//Precompute WedgeAngle
			WedgeAngle = (float)((2 * PI) / NUMPOINTS);
			//Set up vertices for a circle
			//Used <= in the for statement to ensure last point meets first point (closed circle)
			for (i = 0; i <= NUMPOINTS; i++)
			{
				//Calculate theta for this vertex
				Theta = i * WedgeAngle;

				//Compute X and Y locations
				X = (float)(x + rad * cos(Theta));
				Y = (float)(y - rad * sin(Theta));

				Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f);
			}
			//Now draw the circle
			_device->SetFVF(D3DFVF_TL);
			_device->SetTexture(0, NULL);
			_device->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));


		}

		void D9Renderer::Screenshot(Utils::String file)
		{
			if ( !file.contains( "." ) )
				file += ".jpg";
			LPDIRECT3DSURFACE9 back;
			_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back);
			if (!back)
				return;
			D3DXSaveSurfaceToFile(file.c_str(), D3DXIFF_JPG, back, 0, 0);
			back->Release();
		}

		void D9Renderer::Begin(D3DCOLOR back)
		{
			_device->Clear(0, nullptr, D3DCLEAR_TARGET, back, 1.f, 0);
			_device->BeginScene();
		}

		void D9Renderer::Begin()
		{
			_device->Clear(0, nullptr, D3DCLEAR_TARGET, 0x00000000, 1.f, 0);
			_device->BeginScene();
		}

		void D9Renderer::Present()
		{
			_device->EndScene();
			_device->Present(0, 0, 0, 0);
		}

		Vector2 D9Renderer::StrSize(FontMetrics::Font * font, const Utils::String & str)
		{
			std::lock_guard<std::mutex> lock( mutex );
			if (!font)
				return{ 0.0f, 0.0f };
			RECT rect_textSize;
			font->get( )->DrawTextA(NULL, str.c_str(), -1, &rect_textSize, DT_CALCRECT, 0xFFFFFFFF);
			return{ float(rect_textSize.right - rect_textSize.left), float(rect_textSize.bottom - rect_textSize.top) };
		}

		Vector2 D9Renderer::StrSize(Utils::String font, const Utils::String &str)
		{
			return StrSize( fontAt( font ), str );
		}

		void D9Renderer::Release()
		{
			if (_d3d)
				_d3d->Release();
			if (_device)
				_device->Release();

			for (auto&x : _fonts) {
				x->Release();
				delete x;
			}
			_fonts.clear();
		}


	}
}

