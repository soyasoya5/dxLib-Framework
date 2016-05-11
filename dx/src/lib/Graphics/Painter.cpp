#include "Painter.h"
#include "Window\MsgBox.h"
#include "Window\Window.h"
#include "../Application.h"
#include "Pen.h"
#include "Line.h"
#include "Font.h"
#include "Text.h"

// INCLUDE DIRECTX LIBRARIES
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


begin_GRAPHICS

Painter * Painter::Create(Window *target, const bool &windowed, const bool &singleton)
{
	auto application = ::dx::lib::Application::get( );

	if ( !target )
	{
		auto ids = ::dx::lib::Graphics::MsgBox( "Unable to create DirectX9 Painter.\n"
									  "Nullpointer passed as Target window.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Error", 
									   ::dx::lib::Graphics::OKCancel | ::dx::lib::Graphics::IconError ).Show( );
		if ( ids == ::dx::lib::Graphics::MsgBox::Ok )
			return nullptr;
		application->exit( );
	}

	auto painter = std::unique_ptr<Painter>( new Painter( ) );
	if ( FAILED( Direct3DCreate9Ex( D3D9b_SDK_VERSION, (IDirect3D9Ex**)&painter->d3dobj_ ) ) )
	{
		auto ids = ::dx::lib::Graphics::MsgBox( "Unable to create DirectX9 Painter.\n"
									  "Direct3DCreate9Ex failed.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Fatal Error", 
									   ::dx::lib::Graphics::OKCancel | ::dx::lib::Graphics::IconError ).Show( );
		if ( ids == ::dx::lib::Graphics::MsgBox::Ok )
			return nullptr;
		return nullptr;
	}


	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(params));
	params.Windowed = windowed;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.BackBufferFormat = D3DFMT_A8R8G8B8; // 0xAARRGGBB (ARGB)
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D16;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.BackBufferWidth = (!windowed ? 0 : target->Width( ));
	params.BackBufferHeight = (!windowed ? 0 : target->Height( ));
	params.hDeviceWindow = target->native_handle( );
	params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	
	auto obj = (IDirect3D9Ex*)painter->d3dobj_;

	auto result = obj->CreateDevice( D3DADAPTER_DEFAULT, 
									 D3DDEVTYPE_HAL, 
									 target->native_handle( ), 
									 D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									 &params,
									 (IDirect3DDevice9**)&painter->device_ );
	
	if ( FAILED(result) )
	{
		auto ids = ::dx::lib::Graphics::MsgBox( "Unable to create DirectX9 Painter.\n"
									  "Creating the device failed, See logs for error.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Fatal Error", 
									   ::dx::lib::Graphics::OKCancel | ::dx::lib::Graphics::IconError ).Show( );
		if ( ids != ::dx::lib::Graphics::MsgBox::Ok )
			application->exit( );
		return nullptr;
	}

	result = D3DXCreateLine( (IDirect3DDevice9*)painter->device_, (ID3DXLine**)&painter->line_ );
	if ( FAILED(result) )
	{
		auto ids = ::dx::lib::Graphics::MsgBox( "Unable to create DirectX9 Line.\n"
									  "Creating a ID3DXLine failed, you can continue but you are recommended to restart.\n"
									  "If this problem persists open a Issue at:\n"
									  "https://bitbucket.org/Yamiez/dxlib\n"
									  "Press \"OK\" to continue the application, \"Cancel\" to exit the application.", 
									  "Slight Error", 
									   ::dx::lib::Graphics::OKCancel | ::dx::lib::Graphics::IconError ).Show( );
		if ( ids == ::dx::lib::Graphics::MsgBox::Cancel )
			application->exit( );
		return nullptr;
	}

	target->setPainter( painter.get( ) );

	target->OnWindowResize( ) += ::dx::lib::EventHandler<void(::dx::lib::Graphics::Window*, ::dx::lib::Graphics::WindowMovedArgs&)>( target->getClass( ) + "_Painter_Resize",
								  []( Window *sender, WindowMovedArgs &args )
								  {
										auto painter = (Painter*)sender->getPainter( );
										painter->ResetPainter( args.region.size, sender );
								  });

	if ( singleton )
		BasePainter::setSingleton( painter.get( ) );

	FontContext context;
	context.Height = 18;
	context.Weight = 20;
	painter->default_ = Font::Create( "Arial", context, painter.get( ) );

	return painter.release( );
}

Painter::~Painter()
{
	if ( device_ )
		((IDirect3DDevice9*)device_)->Release( );

	if ( d3dobj_ )
		((IDirect3D9Ex*)d3dobj_)->Release( );
	
	if ( line_ )
		((ID3DXLine*)line_)->Release( );
}

bool Painter::ResetPainter(const ::dx::lib::Math::Vector2 & _Size, ::dx::lib::Graphics::Window *_Target)
{
	if ( target_.get( ) != _Target )
	{ 
		if ( target_ )
			target_->setPainter( nullptr, false );
		target_.reset( _Target );
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
	params.hDeviceWindow = target_->native_handle( );
	params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return SUCCEEDED( ((IDirect3DDevice9*)device_)->Reset( &params ) );
}

void Painter::BeginPaint()
{
	((IDirect3DDevice9*)device_)->Clear( 0, nullptr, D3DCLEAR_TARGET, 0, 1.f, 0 );
	((IDirect3DDevice9*)device_)->BeginScene( );
}

void Painter::Paint( const ::dx::lib::Graphics::Text & text, const ::dx::lib::Graphics::Pen & pen)
{
	auto font_type = text.getFont( );
	if ( !font_type )
		font_type = this->defaultFont( );
	auto font = (ID3DXFont*)font_type->raw( );
	auto texts = text.getText( );
	auto pos = text.getPosition( );
	auto clip = text.getMaxClip( );
	auto format = text.getAlignment( );
	RECT rect{ static_cast<LONG>( pos.x ), 
			   static_cast<LONG>( pos.y ), 
			   static_cast<LONG>( pos.x + clip.x ), 
			   static_cast<LONG>( pos.y + clip.y ) };
	font->DrawTextA( nullptr, texts.c_str( ), -1, &rect, format, pen.Color( ) );
}

void Painter::Paint(const ::dx::lib::Graphics::Shape & shape)
{
}

void Painter::Paint(const ::dx::lib::Graphics::Circle & circle)
{
}

void Painter::PaintRect( const ::dx::lib::Math::Region & region, const ::dx::lib::Graphics::Pen & pen)
{
	static D3DRECT rect_angle;
	rect_angle = { static_cast<LONG>( region.position.x ), 
				   static_cast<LONG>( region.position.y ), 
				   static_cast<LONG>( region.position.x + region.size.x ), 
				   static_cast<LONG>( region.position.y + region.size.y ) };
	((IDirect3DDevice9*)device_)->Clear( 1, &rect_angle, D3DCLEAR_TARGET, pen.Color( ), 1.f, 0 );
}

void Painter::PaintRectOutlined( const ::dx::lib::Math::Region &region, const ::dx::lib::Graphics::Pen &inner, const ::dx::lib::Graphics::Pen &outer )
{
	::dx::lib::Math::Region outer_region = region;
	auto outThick = outer.Thickness( );
	outer_region.position.x -= outThick;
	outer_region.position.y -= outThick;
	outer_region.size.x += outThick * 2;
	outer_region.size.y += outThick * 2;

	PaintRect( outer_region, outer );
	PaintRect( region, inner );
}

void Painter::PaintLine(const ::dx::lib::Graphics::Line & line)
{
	auto pen = line.Pen( );
	auto target = line.Target( );
	auto pos = line.Position( );

	if ( line_ == nullptr )
	{
		if ( FAILED( D3DXCreateLine( (IDirect3DDevice9*)device_, (ID3DXLine**)&line_ ) ) )
			return;
		((ID3DXLine*)line_)->SetPattern( 0xFFFFFFFF );
		((ID3DXLine*)line_)->SetAntialias( TRUE );
	}

	D3DXVECTOR2 points[2];
	points[0] = { pos.x, pos.y };
	points[1] = { target.x, target.y };
	((ID3DXLine*)line_)->SetWidth( pen.Thickness( ) );
	((ID3DXLine*)line_)->Draw( points, 2, pen.Color( ) );
}

void Painter::PresentPaint()
{
	((IDirect3DDevice9*)device_)->EndScene( );
	((IDirect3DDevice9*)device_)->Present( 0, 0, 0, 0 );
}

void * Painter::native() const
{
	return device_;
}

std::shared_ptr<Font> Painter::defaultFont() const
{
	return default_;
}

void Painter::setDefaultFont(std::shared_ptr<Font> font)
{
	default_ = font;
}

Painter::Painter()
	: device_( nullptr ), d3dobj_( nullptr ), line_( nullptr ), target_( nullptr )
{
}


end_GRAPHICS


