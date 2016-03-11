#pragma once
#include "MemoryBase.h"


begin_MEMORY

		class InternalImpl : public MemoryBase
		{
		public:
			InternalImpl( );
			~InternalImpl( );

			bool Setup( const __LIB String &_Proc ) override;
			bool Detach( );
			bool SetupModules( );
			bool DetachModules( );
			
			
			virtual bool read_bytes( const __MEMORY Module &_Module, const __DX uint &_Offset, byte *_Buff, const __DX uint &_Size ) override;
			virtual bool write_bytes( const __MEMORY Module &_Module, const __DX uint &_Offset, byte *_Buff, const __DX uint &_Size ) override;
		};
		


end_MEMORY