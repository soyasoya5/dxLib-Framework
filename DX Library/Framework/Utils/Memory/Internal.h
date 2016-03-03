#pragma once
#include "MemoryBase.h"


namespace Utils {
	namespace Memory {

		class InternalImpl : public MemoryBase
		{
		public:
			InternalImpl( );
			~InternalImpl( );

			bool Setup( const Utils::String &_Proc ) override;
			bool Detach( );
			bool SetupModules( );
			bool DetachModules( );
			
			
			virtual bool read_bytes( const Module &_Module, const uint &_Offset, byte *_Buff, const uint &_Size ) override;
			virtual bool write_bytes( const Module &_Module, const uint &_Offset, byte *_Buff, const uint &_Size ) override;
		};
		


	}
}