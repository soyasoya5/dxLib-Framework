#pragma once
#include "../dx.h"


namespace Utils {

	extern 
	bool 
	memcmp ( byte *_bufA,
			 byte *_bufB,
			 uint   _sz );
	
	// SSE
	extern
	bool
	zeromem( byte* _dest,
			 uint _sz );

	// 
	extern
	bool
	strcmp( const char* _bufA,
			const char* _bufB );

	// Standard method
	extern
	bool
	memcpy( byte *_dest,
		    const byte *_src,
		    uint   _sz );

	// Standard method
	extern
	bool
	memset( byte *_dest,
		    const byte &_val,
			uint _sz );
	
	// SSE
	extern
	bool
	memset_sse( byte *_dest,
				const byte &_val,
				uint _sz );

	extern
	void*
	alloc( const uint& _sz );

	extern
	void
	dealloc( void* _ptr,
			 const uint &_sz );
}