#include <dwmapi.h>
#include "Win32Window.h"
#include "../Graphics/Renderer/Renderer.h"
#include "../Graphics/Form.h"
#include "..\Graphics\UI\Window.h"
#include "../Graphics/UI/Canvas.h"


LRESULT CALLBACK WindowProc(HWND hWnd, uint Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_NCCREATE:
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		break;
	}

	auto current_window = (Win32Window*)GetWindowLongPtrA(hWnd, GWL_USERDATA);
	if (current_window == nullptr)
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	return current_window->HandleInput(hWnd, Msg, wParam, lParam);
}

Win32Window::Win32Window()
{

}

Win32Window::~Win32Window()
{
	Release();
}

bool Win32Window::Create(WindowParams *param)
{
	if (isCreated())
		return false;
	if (param->szClass.empty() || param->size == Vector2{ 0,0 })
		return false;


	if (param->type == param->type_standard) {

		WNDCLASSEX wc;
		wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = param->szTitle.c_str();
		wc.lpszClassName = param->szClass.c_str();
		wc.hInstance = NULL;

		if (FAILED(RegisterClassExA(&wc)))
			return _error();

		

		if (!(_hwnd = CreateWindowA(param->szClass.c_str(), param->szTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			param->pos.x, param->pos.y,
			param->size.x, param->size.y,
			NULL, NULL, NULL, this)))
			return false;

		_params = *param;


		ShowWindow(_hwnd, SW_SHOW);

		if (!UpdateWindow(_hwnd))
			return false;
	}
	else
	{
		WNDCLASSEX wc;
		wc.style = 0;


		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = param->szTitle.c_str();
		wc.lpszClassName = param->szClass.c_str();
		wc.hInstance = NULL;

		if (!RegisterClassEx(&wc))
			return false;

		BOOL bComposition = 0;
		if (FAILED(DwmIsCompositionEnabled(&bComposition)))
			return false;


		auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
		if (!(_hwnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
				param->szClass.c_str(),
				param->szTitle.c_str(),
				WS_POPUP,
				param->pos.x, param->pos.y,
				param->size.x, param->size.y,
				NULL, NULL, NULL, this))
			)
			return false;

		
		if ( !SetLayeredWindowAttributes( _hwnd, param->transparency_key, 255, ULW_COLORKEY | LWA_ALPHA ) )
			return false;
		
		static MARGINS  DWMMargins = { -1, -1, -1, -1 };
		if ( FAILED( DwmExtendFrameIntoClientArea( _hwnd, &DWMMargins ) ) )
			return false;

		ShowWindow( _hwnd, SW_SHOW );
		if ( !UpdateWindow( _hwnd ) )
			return false;

		_params = *param;
	}
	

	if (this->_render)
	{
		_render->Release();
		delete _render;
	}

	_render = Graphics::Renderer::D9Renderer::SafeAlloc<Graphics::Renderer::D9Renderer>( this );
	if (!_render->Create())
		return _error();

	return _success();
}

void Win32Window::Quit()
{
	_quit = true;
}

bool Win32Window::isMinimized()
{
	return _min;
}

bool Win32Window::isCreated()
{
	return _created;
}

void Win32Window::Release()
{
	_render->Release();
}

LRESULT Win32Window::HandleInput(HWND hwnd, uint msg, WPARAM wParam, LPARAM lParam)
{
	POINTS p = MAKEPOINTS(lParam);
	WindowEventParams params;
	params.key = wParam;
	params.lp = &p;
	params.msg = msg;
	OnEvent().Invoke(params);

	switch (msg)
	{
	case WM_QUIT:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSELEAVE:
		OnMouseLeave().Invoke();
		return 0;
		break;
	case WM_KEYDOWN:
		OnKeyDown().Invoke( static_cast<uint>( wParam ) );
		return 0;
		break;
	case WM_KEYUP:
		OnKeyUp().Invoke( static_cast<uint>( wParam ) );
		return 0;
		break;
	case WM_MOUSEMOVE:
		OnMouseMove().Invoke( Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) } );
		return 0;
		break;
	case WM_MOVE:
		OnWindowMove().Invoke( Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) } );
		return 0;
		break;
	case WM_SIZE:
		OnWindowResize().Invoke( Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) }, hwnd);
		return 0;
		break;
	case WM_LBUTTONDOWN:
		OnLeftMouseDown().Invoke( Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) } );
		return 0;
		break;
	case WM_LBUTTONUP:
		OnLeftMouseUp().Invoke(Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) });
		return 0;
		break;
	case WM_RBUTTONDOWN:
		OnRightMouseDown().Invoke(Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) });
		return 0;
		break;
	case WM_RBUTTONUP:
		OnRightMouseUp().Invoke(Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) });
		return 0;
		break;
	case WM_LBUTTONDBLCLK:
		OnLeftMouseDoubleClick().Invoke(Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) });
		return 0;
		break;
	case WM_RBUTTONDBLCLK:
		OnRightMouseDoubleClick().Invoke(Vector2{ static_cast<float>(p.x), static_cast<float>(p.y) });
		return 0;
		break;
	case WM_CHAR:
		OnKeyDownChar().Invoke( wParam );
		return 0;
		break;
	case WM_CLOSE:
	{
		auto res = OnWindowClose().Invoke();
		if ( !res.empty( ) && res[0] )
			return 0;
		else
			Quit( );
		break;
	}
	case WM_DESTROY:
		Quit();
		return 0;
		break;
	}

	if (IsIconic(hwnd)) {
		if (!_prevState)
			OnWindowMinimize().Invoke();
		_prevState = true;
	}
	else {
		if (_prevState)
			OnWindowMaximize().Invoke();
		_prevState = false;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Win32Window::PollEvents()
{
	static MSG msg;
	if (_quit)
		return false;

	if (PeekMessage(&msg, _hwnd, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return __super::PollEvents( );

}

bool Win32Window::_success()
{
	_created = true;
	return true;
}

bool Win32Window::_error()
{
	_created = false;
	return false;
}


void Win32Window::LaunchForm(Graphics::Form *f)
{
	if ( _canvas == nullptr ) {
		_canvas = new Graphics::UI::Canvas();
		OnMouseMove() += [&](Vector2 p) { return _canvas->OnMouseMove(p); };
		OnLeftMouseDown() += [&](Vector2 p) { return _canvas->OnLeftMouseDown(p); };
		OnLeftMouseUp() += [&](Vector2 p) { return _canvas->OnLeftMouseUp(p); };
		OnRightMouseDown() += [&](Vector2 p) { return _canvas->OnRightMouseDown(p); };
		OnRightMouseUp() += [&](Vector2 p) { return _canvas->OnRightMouseUp(p); };
		OnRightMouseDoubleClick() += [&](Vector2 p) { return _canvas->OnRightMouseDoubleClick(p); };
		OnLeftMouseDoubleClick() += [&](Vector2 p) { return _canvas->OnLeftMouseDoubleClick(p); };
		OnKeyDown() += [&](uint p) { return _canvas->OnKeyDown(p); };
		OnKeyUp() += [&](uint p) { return _canvas->OnKeyUp(p); };
		OnKeyDownChar() += [&](char p) { return _canvas->OnKeyDownChar(p); };
	}
	_forms.push_back( f );
	f->_win32window = this;
	f->_canvas = _canvas;
	f->Initalize( );
	this->OnWindowMinimize( ) += [&min = this->_min] ( )mutable->bool
	{
		min = true;
		return true;
	};
	this->OnWindowMaximize( ) += [&min = this->_min]( ) mutable->bool
	{
		min = false;
		return true;
	};

	OnEvent( ) += [f]( WindowEventParams p ) { return f->Event( p );  };
}

bool Win32Window::PaintForms()
{
	if ( isMinimized( ) )
		return false;
	_canvas->Paint( _render );
	for ( auto& f : _forms )
		if ( f ) 
			f->Paint( _render );
	return true;
}

bool Win32Window::TickForms()
{
	for ( auto& f : _forms )
		if ( f )
			f->DoTick( ); 
	return true;
}

Event<bool, Vector2>& Win32Window::OnWindowMove()
{
	return _OnWindowMove;
}

Event<bool, Vector2, HWND>& Win32Window::OnWindowResize()
{
	return _OnWindowResize;
}

Event<bool>& Win32Window::OnWindowMinimize()
{
	return _OnWindowMinimize;
}

Event<bool>& Win32Window::OnWindowMaximize()
{
	return _OnWindowMaximize;
}

Event<bool>& Win32Window::OnWindowClose()
{
	return _OnWindowClose;
}

