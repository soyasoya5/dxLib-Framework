#pragma once
#include "Types.h"
#include "../string.h"


namespace Utils {
	namespace Memory {

		class MemoryBase
		{
		protected:
			Handle<>* _handle;
			uint _pID;
			Utils::String _proc;
			std::vector<Module> _modules;
			bool _can;
		public:
			virtual bool Setup( const Utils::String &_Proc ) = 0;

			virtual bool read_bytes( const Module &_Module, const uint &_Offset, byte *_Buff, const uint &_Size ) = 0;
			virtual bool write_bytes( const Module &_Module, const uint &_Offset, byte *_Buff, const uint &_Size ) = 0;
			virtual Module& moduleAt( const Utils::String &_Name );

			template<typename _Type>
			_Type Read( const Module &_Module, const uint &_Addr )
			{
				_Type _Val = _Type( );
				if ( !_can )
					return _Val;
				read_bytes( _Module, _Addr, ccast<byte*>( &_Val ), sizeof(_Type) );
				return _Val;
			}

			template<typename _Type>
			bool Write( const Module &_Module, const uint &_Addr, const _Type &_Val )
			{
				if ( !_can )
					return false;
				return write_bytes( _Module, _Addr, ccast<byte*>( &_Val ), sizeof(_Type) );
			}

			virtual bool isInitalized( ) { return _can; }
		};

	}
}