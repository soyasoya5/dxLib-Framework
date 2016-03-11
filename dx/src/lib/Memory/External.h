#pragma once
#include "MemoryBase.h"


begin_MEMORY

		class ExternalImpl : public __MEMORY MemoryBase
		{
		public:
			ExternalImpl( );
			~ExternalImpl( );

			bool Setup( const __LIB String &_Proc ) override;
			bool Detach( );
			bool SetupModules( );
			bool DetachModules( );

			virtual bool read_bytes( const __MEMORY Module &_Module, const __DX uint &_Offset, __DX byte *_Buff, const __DX uint &_Size ) override;
			virtual bool write_bytes( const __MEMORY Module &_Module, const __DX uint &_Offset, __DX byte *_Buff, const __DX uint &_Size ) override;
		};


end_MEMORY

