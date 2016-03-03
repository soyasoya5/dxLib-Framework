#include "Utils.h"
#include <mmintrin.h>
#include <stdint.h>
#include <string.h>


namespace Utils {


	bool memcmp( byte* _bufA, byte* _bufB, uint n )
	{
		static const uint uint_size = sizeof( uint );
		while ( n > uint_size)
		{
			if ( (int)*_bufA != (int)*_bufB )
				return false;
			_bufA += uint_size, _bufB += uint_size;
			n -= uint_size;
		}
		while( n > 0 )
		{
			if ( *_bufA != *_bufB )
				return false;
			++_bufA, ++_bufB;
			--n;
		}
		return true;
	}

	bool zeromem(byte * _dest, uint _sz)
	{
		__m128i zero = _mm_setzero_si128();
		for (auto i = rcast<__m128i*>(_dest),
			end = rcast<__m128i*>(_dest + _sz);
			i < end; ++i)
		{
			_mm_storeu_si128(i, zero);
		}
		return true;
	}

	bool strcmp(const char * _bufA, const char * _bufB)
	{
		while ( (*_bufA)  && (*_bufA) == (*_bufB))
		{
			++_bufA;
			if ( ! ( *(_bufB + 1) && *(_bufB + 1) == 0 ) )
				++_bufB;
		}
		return _bufA - _bufB == 0;
	}

	bool memcpy( byte* _dest, const byte* _src, uint _sz )
	{
		if ( _sz == 0 || _dest == nullptr || _src == nullptr )
			return false;
		while( _sz > sizeof( uint ) )
		{
			*(uint*)_dest = *(uint*)_src;
			_sz -= sizeof( uint );
			_dest += sizeof( uint ), _src += sizeof( uint );
		}
		while ( _sz > 0 ) {
			*_dest = *_src;
			--_sz, ++_dest, ++_src;
		}
		return true;
	}

	bool memset( byte* _dest, const byte& _val, uint _sz )
	{
		if (_sz == 0 || _dest == nullptr)
			return false;
		while( _sz > 0 ) 
		{
			*_dest = _val;
			--_sz, ++_dest;
		}
		return true;
	}

	bool memset_sse(byte * _dest, const byte & _val, uint _sz)
	{
		static const __m128i zero = _mm_set1_epi32( _val );
		for (auto i = rcast<__m128i*>(_dest),
			end = rcast<__m128i*>(_dest + _sz);
			i < end; ++i)
		{
			_mm_storeu_si128(i, zero);
		}
		return true;
	}
	
	void* alloc( const uint& _sz )
	{
		return ccast<void*>( new byte[_sz] );
	}

	void dealloc( void* _ptr, const uint &_sz )
	{
		operator delete[](_ptr, _sz);
	}


}