#include "Painter.h"
#include "Window\MsgBox.h"
#include "Window\Window.h"
#include "../Application.h"
#include "Pen.h"
#include "Line.h"

// INCLUDE DIRECTX LIBRARIES
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


begin_GRAPHICS

Painter * Painter::Create(__GRAPHICS Window * _Target, const bool &_Windowed)
{
	auto application = __LIB Application::get( );

	if ( !_Target )
	{
		auto ids = __GRAPHICS MsgBox( "Unable to create DirectX9 Painter.\n"
									  "Nullpointer passed as Target window.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Error", 
									   __GRAPHICS OKCancel | __GRAPHICS IconError ).Show( );
		if ( ids == __GRAPHICS MsgBox::Ok )
			return nullptr;
		else
			application->exit( );
		application->exit( );
	}

	auto painter = new Painter( );
	if ( FAILED( Direct3DCreate9Ex( D3D9b_SDK_VERSION, (IDirect3D9Ex**)&painter->_d3dobj ) ) )
	{
		auto ids = __GRAPHICS MsgBox( "Unable to create DirectX9 Painter.\n"
									  "Direct3DCreate9Ex failed.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Fatal Error", 
									   __GRAPHICS OKCancel | __GRAPHICS IconError ).Show( );
		if ( ids == __GRAPHICS MsgBox::Ok )
			return nullptr;
		else
			application->exit( );
		return nullptr;
	}


	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(params));
	params.Windowed = _Windowed;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.BackBufferFormat = D3DFMT_A8R8G8B8; // 0xAARRGGBB (ARGB)
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D16;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.BackBufferWidth = (_Windowed ? 0 : _Target->Width( ));
	params.BackBufferHeight = (_Windowed ? 0 : _Target->Height( ));
	params.hDeviceWindow = _Target->native_handle( );
	params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	
	auto obj = (IDirect3D9Ex*)painter->_d3dobj;

	// D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _windowptr->_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &_device
	auto result = obj->CreateDevice( D3DADAPTER_DEFAULT, 
									 D3DDEVTYPE_HAL, 
									 _Target->native_handle( ), 
									 D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									 &params,
									 (IDirect3DDevice9**)&painter->_device );
	
	if ( FAILED(result) )
	{
		auto ids = __GRAPHICS MsgBox( "Unable to create DirectX9 Painter.\n"
									  "Creating the device failed, See logs for error.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Fatal Error", 
									   __GRAPHICS OKCancel | __GRAPHICS IconError ).Show( );
		if ( ids == __GRAPHICS MsgBox::Ok )
			return nullptr;
		else
			application->exit( );
		return nullptr;
	}

	result = D3DXCreateLine( (IDirect3DDevice9*)painter->_device, (ID3DXLine**)&painter->_line );
	if ( FAILED(result) )
	{
		auto ids = __GRAPHICS MsgBox( "Unable to create DirectX9 Line.\n"
									  "Creating a ID3DXLine failed, you can continue but you are recommended to restart.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Slight Error", 
									   __GRAPHICS OKCancel | __GRAPHICS IconError ).Show( );
		if ( ids == __GRAPHICS MsgBox::Cancel )
		{
			application->exit( );
			return nullptr;
		}
	}

	_Target->setPainter( painter );

	_Target->OnWindowResize( ) += []( __GRAPHICS Window *sender, __GRAPHICS WindowMovedArgs &args )
	{
		auto painter = (Painter*)sender->getPainter( );
		painter->ResetPainter( args.region.size, sender );
	};

	_Target->OnWindowMaximize( ) += []( __GRAPHICS Window *sender )
	{
		auto painter = (Painter*)sender->getPainter( );
		painter->ResetPainter( { sender->Width( ), sender->Height( ) }, sender );
	};

	return painter;
}

Painter::~Painter()
{
	((IDirect3DDevice9*)_device)->Release( );
	((IDirect3D9Ex*)_d3dobj)->Release( );
	((ID3DXLine*)_line)->Release( );
}

bool Painter::ResetPainter(const __MATH Vector2 & _Size, __GRAPHICS Window *_Target)
{
	if ( _target != _Target ) {
		if ( _target )
			this->_target->setPainter( nullptr, false );
		this->_target = _Target;
		this->_target->setPainter( this, false );
	}

	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(params));
	params.Windowed = TRUE;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.BackBufferFormat = D3DFMT_A8R8G8B8;
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D16;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.BackBufferWidth = _Size.x;
	params.BackBufferHeight = _Size.y;
	params.hDeviceWindow = _target->native_handle( );
	params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return SUCCEEDED( ((IDirect3DDevice9*)_device)->Reset( &params ) );
}

void Painter::BeginPaint()
{
	((IDirect3DDevice9*)_device)->Clear( 0, nullptr, D3DCLEAR_TARGET, 0x0, 1.f, 0 );
	((IDirect3DDevice9*)_device)->BeginScene( );
}

void Painter::Paint( const __GRAPHICS Text & _Text, const __GRAPHICS Pen & _Pen)
{
}

void Painter::Paint(const __GRAPHICS Shape & _Shape)
{
}

void Painter::PaintRect( const __MATH Region & _Region, const __GRAPHICS Pen & _Pen)
{
	static D3DRECT rect_angle;
	rect_angle = { static_cast<LONG>( _Region.position.x ), 
				   static_cast<LONG>( _Region.position.y ), 
				   static_cast<LONG>( _Region.position.x + _Region.size.x ), 
				   static_cast<LONG>( _Region.position.y + _Region.size.y ) };
	((IDirect3DDevice9*)_device)->Clear( 1, &rect_angle, D3DCLEAR_TARGET, _Pen.Color( ), 1.f, 0 );
}

void Painter::PaintRectOutlined( const __MATH Region &_Region, const __GRAPHICS Pen &_PenInner, const __GRAPHICS Pen &_PenOuter )
{
	__MATH Region outer_region = _Region;
	outer_region.position.x -= _PenOuter.Thickness( );
	outer_region.position.y -= _PenOuter.Thickness( );
	outer_region.size.x += _PenOuter.Thickness( );
	outer_region.size.y += _PenOuter.Thickness( );

	PaintRect( outer_region, _PenOuter );
	PaintRect( _Region, _PenInner );
}

void Painter::PaintLine(const __GRAPHICS Line & _Line)
{
	auto pen = _Line.Pen( );
	auto target = _Line.Target( );
	auto pos = _Line.Position( );

	if ( _line == nullptr )
	{
		if ( FAILED( D3DXCreateLine( (IDirect3DDevice9*)_device, (ID3DXLine**)&_line ) ) )
			return;
		((ID3DXLine*)_line)->SetPattern( 0xFFFFFFFF );
		((ID3DXLine*)_line)->SetAntialias( TRUE );
	}

	D3DXVECTOR2 points[2];
	points[0] = { pos.x, pos.y };
	points[1] = { target.x, target.y };
	((ID3DXLine*)_line)->SetWidth( pen.Thickness( ) );
	((ID3DXLine*)_line)->Draw( points, 2, pen.Color( ) );
}

void Painter::PresentPaint()
{
	((IDirect3DDevice9*)_device)->EndScene( );
	((IDirect3DDevice9*)_device)->Present( 0, 0, 0, 0 );
}

Painter::Painter()
	: _device( nullptr ), _d3dobj( nullptr ), _line( nullptr ), _target( nullptr )
{
}


end_GRAPHICS


