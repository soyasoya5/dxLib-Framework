#pragma once

#ifndef _WIN32
#ifndef INVALID_HANLDE_VALUE
#define INVALID_HANDLE_VALUE ((void*)(long)-1)
#endif
#endif

#ifndef begin_LIB
#define begin_LIB namespace dx { namespace lib {
#endif
#ifndef end_LIB
#define end_LIB } }
#endif


#ifndef begin_MEMORY
#define begin_MEMORY namespace dx { namespace lib { namespace Memory {
#endif

#ifndef end_MEMORY
#define end_MEMORY } } }
#endif


#ifndef begin_FILEIO
#define begin_FILEIO namespace dx { namespace lib { namespace FileIO {
#endif

#ifndef end_FILEIO
#define end_FILEIO } } }
#endif

#ifndef begin_GRAPHICS
#define begin_GRAPHICS namespace dx { namespace lib { namespace Graphics {
#endif

#ifndef end_GRAPHICS
#define end_GRAPHICS } } }
#endif

#ifndef begin_MATH
#define begin_MATH namespace dx { namespace lib { namespace Math {
#endif

#ifndef end_MATH
#define end_MATH } } }
#endif

#ifndef __DX
#define __DX ::dx::
#endif

#ifndef __LIB
#define __LIB ::dx::lib::
#endif

#ifndef __MEMORY
#define __MEMORY ::dx::lib::Memory::
#endif

#ifndef __FILEIO
#define __FILEIO ::dx::lib::FileIO::
#endif

#ifndef __GRAPHICS
#define __GRAPHICS ::dx::lib::Graphics::
#endif

#ifndef __MATH
#define __MATH ::dx::lib::Math::
#endif