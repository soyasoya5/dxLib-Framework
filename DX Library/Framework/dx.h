#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <vector>
#include <fstream>
#include <ctime>
#include <mutex>
#include <thread>
#include <future>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")



typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR2 Vector3;
typedef D3DXVECTOR2 Vector4;

#ifndef _dx_types_byte
typedef unsigned char byte;
#define _dx_types_byte
#endif

#ifndef _dx_types_uint
typedef unsigned int uint;
#define _dx_types_uint
#endif

#ifndef _dx_types_ulong
typedef unsigned long ulong;
#define _dx_types_ulong
#endif

#ifndef _dx_types_color
typedef uint Color;
#define _dx_types_color
#endif

#ifndef _dx_tl_enable_if
template<bool _Test, typename _Type = void>
class enable_if
{ };

template<typename _Type>
class enable_if<true, _Type>
{
public:
	typedef _Type type;
};
#define _dx_tl_enable_if
#endif

#ifndef _dx_using
template<typename T>
using pointer = typename std::remove_pointer<T>::type*;

template<typename T>
using param = const T&;
#define _dx_using
#endif

enum Key : uint
{
	key_leftButton = 1,
	key_rightButton,
	key_reserved_01,
	key_middleButton,
	key_xbutton,
	key_xbutton2,
	key_reserved_02,
	key_backspace,
	key_tab,
	key_reserved_03 = 0x0A,
	key_clear = 0x0C,
	key_enter = 0x0D,
	key_shift = 0x10,
	key_control = 0x11,
	key_alt = 0x12,
	key_pause = 0x13,
	key_caps = 0x14,
	key_escape = 0x1B,
	key_space = 0x20,
	key_pgup = 0x21,
	key_pgdn = 0x22,
	key_end = 0x23,
	key_home = 0x24,
	key_left = 0x25,
	key_up = 0x26,
	key_right = 0x27,
	key_down = 0x28,
	key_insert = 0x2D,
	key_delete = 0x2E,
	key_help = 0x2F,
	key_0 = 0x30,
	key_1 = 0x31,
	key_2 = 0x32,
	key_3 = 0x33,
	key_4 = 0x34,
	key_5 = 0x35,
	key_6 = 0x36,
	key_7 = 0x37,
	key_8 = 0x38,
	key_9 = 0x39,
	key_a = 0x41,
	key_b = 0x42,
	key_c = 0x43,
	key_d = 0x44,
	key_e = 0x45,
	key_f = 0x46,
	key_g = 0x47,
	key_h = 0x48,
	key_i = 0x49,
	key_j = 0x4A,
	key_k = 0x4B,
	key_l = 0x4C,
	key_m = 0x4D,
	key_n = 0x4E,
	key_o = 0x4F,
	key_p = 0x50,
	key_q = 0x51,
	key_r = 0x52,
	key_s = 0x53,
	key_t = 0x54,
	key_u = 0x55,
	key_v = 0x56,
	key_w = 0x57,
	key_x = 0x58,
	key_y = 0x59,
	key_z = 0x5A,
	key_leftWindows = 0x5B,
	key_rightWindows = 0x5C,
	key_num0 = 0x60,
	key_num1 = 0x61,
	key_num2 = 0x62,
	key_num3 = 0x63,
	key_num4 = 0x64,
	key_num5 = 0x65,
	key_num6 = 0x66,
	key_num7 = 0x67,
	key_num8 = 0x68,
	key_num9 = 0x69,
	key_F1 = 0x70,
	key_F2 = 0x71,
	key_F3 = 0x72,
	key_F4 = 0x73,
	key_F5 = 0x74,
	key_F6 = 0x75,
	key_F7 = 0x76,
	key_F8 = 0x77,
	key_F9 = 0x78,
	key_F10 = 0x79,
	key_F11 = 0x7A,
	key_F12 = 0x7B,
	key_F13 = 0x7C,
	key_F14 = 0x7D,
	key_F15 = 0x7E,
	key_numlock = 0x90,
	key_leftShift = 0xA1,
	key_leftControl = 0xA2,
	key_rightControl = 0xA3,
	key_comma = 0xBC,
	key_minus = 0xBD,
	key_dot = 0xBE
};


class Colors
{
public:
	typedef const uint type;
	static type AliciaBlue				= 0xFFF0F8FFu;
	static type AntiqueWhite			= 0xFFFAEBD7u;
	static type Aqua				    = 0xFF00FFFFu;
	static type Aquamarine				= 0xFF7FFFD4u;
	static type Azure					= 0xFFF0FFFFu;
	static type Beige					= 0xFFF5F5DCu;
	static type Bisque					= 0xFFFFE4C4u;
	static type Black					= 0xFF000000u;
	static type BlanchedAlmond			= 0xFFFFEBCDu;
	static type Blue					= 0xFF0000FFu;
	static type BlueViolet				= 0xFF8A2BE2u;
	static type Brown					= 0xFFA52A2Au;
	static type BurlyWodd				= 0xFFDEB887u;
	static type CadetBlue				= 0xFF5F9EA0u;
	static type Chartreuse				= 0xFF7FFF00u;
	static type Chocolate			    = 0xFFD2691Eu;
	static type Coral					= 0xFFFF7F50u;
	static type CornFlowerBlue			= 0xFF6495EDu;
	static type Cornsilk				= 0xFFFFF8DCu;
	static type Crimson					= 0xFFDC143Cu;
	static type Cyan				    = 0xFF00FFFFu;
	static type DarkBlue				= 0xFF00008Bu;
	static type DarkCyan				= 0xFF008B8Bu;
	static type DarkGoldenRod			= 0xFFB8860Bu;
	static type DarkGray				= 0xFFA9A9A9u;
	static type DarkGreen				= 0xFF006400u;
	static type DarkKhaki				= 0xFFBDB76Bu;
	static type DarkMagneta				= 0xFF8B008Bu;
	static type DarkOliveGreen			= 0xFF556B2Fu;
	static type DarkOrange				= 0xFFFF8C00u;
	static type DarkOrchid				= 0xFF9932CCu;
	static type DarkRed					= 0xFF8B0000u;
	static type DarkSalmon				= 0xFFE9967Au;
	static type DarkSeaGreen			= 0xFF8FBC8Fu;
	static type DarkSlateBlue			= 0xFF483D8Bu;
	static type DarkSlateGray			= 0xFF2F4F4Fu;
	static type DarkTurquoise			= 0xFF00CED1u;
	static type DarkViolet				= 0xFF9400D3u;
	static type DeepPink				= 0xFFFF1493u;
	static type DeepSkyeBlue			= 0xFF00BFFFu;
	static type DimGray					= 0xFF696969u;
	static type DodgerBlue				= 0xFF1E90FFu;
	static type FireBrick				= 0xFFB22222u;
	static type FloralWhite				= 0xFFFFFAF0u;
	static type ForestGreen				= 0xFF228B22u;
	static type Fuchsia					= 0xFFFF00FFu;
	static type Gainsboro				= 0xFFDCDCDCu;
	static type GhostWhite				= 0xFFF8F8FFu;
	static type Gold					= 0xFFFFD700u;
	static type GoldenRod				= 0xFFDAA520u;
	static type Gray					= 0xFF808080u;
	static type Green					= 0xFF008000u;
	static type GreenYellow				= 0xFFADFF2Fu;
	static type HoneyDew				= 0xFFF0FFF0u;
	static type HotPink					= 0xFFFF69B4u;
	static type IndianRed				= 0xFFCD5C5Cu;
	static type Indigo					= 0xFF4B0082u;
	static type Ivory					= 0xFFFFFFF0u;
	static type Khaki					= 0xFFF0E68Cu;
	static type Lavender				= 0xFFE6E6FAu;
	static type LavenderBlush			= 0xFFFFF0F5u;
	static type LawnGreen				= 0xFF7CFC00u;
	static type LemonChiffon			= 0xFFFFFACDu;
	static type LightBlue				= 0xFFADD8E6u;
	static type LightCoral				= 0xFFF08080u;
	static type LightCyan				= 0xFFE0FFFFu;
	static type LightGoldenrodYellow    = 0xFFFAFAD2u;
	static type LightGray				= 0xFFD3D3D3u;
	static type LightGreen				= 0xFF90EE90u;
	static type LightPink				= 0xFFFFB6C1u;
	static type LightSalmon				= 0xFFFFA07Au;
	static type LightSeaGreen			= 0xFF20B2AAu;
	static type LightSkyBlue			= 0xFF87CEFAu;
	static type LightSlateGray			= 0xFF778899u;
	static type LightSteelBlue			= 0xFFB0C4DEu;
	static type LightYellow				= 0xFFFFFFE0u;
	static type Lime					= 0xFF00FF00u;
	static type LimeGreen				= 0xFF32CD32u;
	static type Linen					= 0xFFFAF0E6u;
	static type Magenta					= 0xFFFF00FFu;
	static type Maroon					= 0xFF800000u;
	static type MediumAquamarine		= 0xFF66CDAAu;
	static type MediumBlue				= 0xFF0000CDu;
	static type MediumOrchid			= 0xFFBA55D3u;
	static type MediumPurple			= 0xFF9370DBu;
	static type MediumSeaGreen			= 0xFF3CB371u;
	static type MediumSlateBlue			= 0xFF7B68EEu;
	static type MediumSpringGreen		= 0xFF00FA9Au;
	static type MediumTurquoise			= 0xFF48D1CCu;
	static type MediumVioletRed			= 0xFFC71585u;
	static type MidnightBlue			= 0xFF191970u;
	static type MintCream				= 0xFFF5FFFAu;
	static type MistyRose				= 0xFFFFE4E1u;
	static type Moccasin				= 0xFFFFE4B5u;
	static type NavajoWhite				= 0xFFFFDEADu;
	static type Navy					= 0xFF000080u;
	static type OldLace					= 0xFFFDF5E6u;
	static type Olive					= 0xFF808000u;
	static type OliveDrab				= 0xFF6B8E23u;
	static type Orange					= 0xFFFFA500u;
	static type OrangeRed				= 0xFFFF4500u;
	static type Orchid					= 0xFFDA70D6u;
	static type PaleGoldenRod			= 0xFFEEE8AAu;
	static type PaleGreen				= 0xFF98FB98u;
	static type PaleTurquoise			= 0xFFAFEEEEu;
	static type PaleVioletRed			= 0xFFDB7093u;
	static type PapayaWhip				= 0xFFFFEFD5u;
	static type PeachPuff				= 0xFFFFDAB9u;
	static type Peru					= 0xFFCD853Fu;
	static type Pink					= 0xFFFFC0CBu;
	static type Plum					= 0xFFDDA0DDu;
	static type PowderBlue				= 0xFFB0E0E6u;
	static type Purple					= 0xFF800080u;
	static type Red						= 0xFFFF0000u;
	static type RosyBrown				= 0xFFBC8F8Fu;
	static type RoyalBlue				= 0xFF4169E1u;
	static type SaddleBrown				= 0xFF8B4513u;
	static type Salmon					= 0xFFFA8072u;
	static type SandyBrown				= 0xFFF4A460u;
	static type SeaGreen				= 0xFF2E8B57u;
	static type SeaShell				= 0xFFFFF5EEu;
	static type Sienna					= 0xFFA0522Du;
	static type Silver					= 0xFFC0C0C0u;
	static type SkyBlue					= 0xFF87CEEBu;
	static type SlateBlue				= 0xFF6A5ACDu;
	static type SlateGray				= 0xFF708090u;
	static type Snow					= 0xFFFFFAFAu;
	static type SpringGreen				= 0xFF00FF7Fu;
	static type SteelBlue				= 0xFF4682B4u;
	static type Tan						= 0xFFD2B48Cu;
	static type Teal					= 0xFF008080u;
	static type Thistle					= 0xFFD8BFD8u;
	static type Tomato					= 0xFFFF6347u;
	static type Transparent				= 0x00FFFFFFu;
	static type Turquoise				= 0xFF40E0D0u;
	static type Violet					= 0xFFEE82EEu;
	static type Wheat					= 0xFFF5DEB3u;
	static type White					= 0xFFFFFFFFu;
	static type WhiteSmoke				= 0xFFF5F5F5u;
	static type Yellow					= 0xFFFFFF00u;
	static type YellowGreen				= 0xFF9ACD32u;
};


// STATIC_CAST

template<typename Tx, typename Fx = void*>
constexpr Tx scast( Fx fx )
{
	return static_cast<Tx>( fx );
}



// REINTERPRET_CAST

template<typename Tx, typename Fx = void*>
Tx rcast( Fx fx )
{
	return reinterpret_cast<Tx>( fx );
}

// DYNAMIC_CAST

template<typename Tx, typename Fx = void*>
Tx dcast( Fx fx )
{
	return dynamic_cast<Tx>( fx );
}


template<typename Tx, typename Fx = void*>
Tx ccast( Fx fx )
{
	return ( ( Tx )( fx ) );
}


class Object
{
private:
	bool _heap;

public:
	Object( ) : _heap(false) {}
	virtual ~Object( ) {}

	template<typename T, typename..._Args>
	static T* SafeAlloc( _Args&&...args )
	{
		if (!std::is_base_of<Object, T>::value)
			return nullptr;
		auto obj = new T( std::forward<_Args>(args)... );
		auto ptr = dynamic_cast<Object*>(obj);
		ptr->_heap = true;
		return obj;
	}

	virtual void Release( )
	{
		// Do release..
	}

	bool isHeap( )
	{
		return _heap;
	}

	bool isStack( )
	{
		return !_heap;
	}
};

template<typename _Type>
class ScopeExit
{
	_Type *_val;
	std::function<void(_Type*)> _dest;
public:
	ScopeExit( _Type *_Val, std::function<void(_Type*)> _Destructor )
	{
		_val = _Val;
		_dest = _Destructor;
	}

	~ScopeExit( )
	{
		if ( _dest )
			_dest( _val );
	}

};


namespace Utils {
	class Clock;
	template<typename Px>
	class Iterator;
	template<typename Px>
	class ReverseIterator;
	class Logger;
	enum Log_t;
	enum Severity_t;
	class String;
	namespace Memory {
		struct Destructor { };
		struct LiveFor { };
		class Module;
		template<typename _Lifetime = Destructor,
			uint _Delay = static_cast<uint>(-1)>
		class Handle;
		class MemoryBase;
		class InternalImpl;
		class ExternalImpl;
		class Address;
		class Pattern;
	};

	//namespace Serialization { 
	//	class Serializer;
	//	class SerializationType;
	//}

}

namespace FileIO {
	class Tokenizer;
	class ConfigElement;
	class Config;
	class Path;
	class File;
}

namespace Graphics {
	namespace FontMetrics {
		class Font;
		class Metrics;
	}

	namespace Renderer {
		class D9Renderer;
	}

	namespace Style {
		class StyleElement;
		class Stylesheet;
	}

	namespace UI {

		namespace Anim {
			class Tick;
			class AnimationHandler;
		}

		namespace UML {
			class Document;
			class Parameter;
			class SyntaxHelper;
			class Executer;
		}

		class Component;
		class BackgroundTask;
		class Button;
		class Canvas;
		class Checkbox;
		class Label;
		class LinkedLabel;
		class RichLabel;
		class ListBox;
		class Scrollbar;
		class Tab;
		class TabControl;
		class Textbox;
		class Window;
	}

	enum DialogType;
	enum DialogResult;
	class Task;
	class Form;
};

namespace dx
{
	using namespace Utils;
	using namespace Memory;
	using namespace FileIO;
	using namespace Graphics;
	using namespace FontMetrics;
	using namespace Renderer;
	using namespace Style;
	using namespace UI;
}