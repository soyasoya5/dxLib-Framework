#pragma once
#include "MemoryBase.h"


namespace Utils {
	namespace Memory {

		class ExternalImpl : public MemoryBase
		{
		public:
			ExternalImpl( );
			~ExternalImpl( );

			bool Setup( const Utils::String &_Proc ) override;
			bool Detach( );
			bool SetupModules( );
			bool DetachModules( );

			virtual bool read_bytes( const Module &_Module, const uint &_Offset, byte *_Buff, const uint &_Size ) override;
			virtual bool write_bytes( const Module &_Module, const uint &_Offset, byte *_Buff, const uint &_Size ) override;
		};


	}
}

