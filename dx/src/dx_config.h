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

#ifndef begin_IO
#define begin_IO namespace dx { namespace lib { namespace IO { 
#endif

#ifndef end_IO
#define end_IO } } }
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

#ifndef __IO
#define __IO ::dx::lib::IO::
#endif