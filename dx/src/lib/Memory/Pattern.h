#pragma once
#include "Types.h"


begin_MEMORY

		class Address
		{
			Module* _module;
			uint _offset;
		public:
			Address( Module *_Module, const uint &_Offset );

			bool IsNullOrZero( );
			Module *getModule( );
			uint getOffset( );

			uint get_addr( );
		};

		class Pattern
		{
		private:
			__LIB String _pattern;
			Module *_module;
			MemoryBase* _memory;

			std::vector<uint> break_pattern( );
			bool memcmp( std::vector<uint> &_Pattern, byte *_Module );
		public:
			Pattern( const __LIB String &_Pattern, Module *_Module, MemoryBase *_Memory );

			void ChangeModule( Module *_Module );
			void ChangeMemoryBase( MemoryBase *_Memory );
			void ChangePattern( const __LIB String &_Pattern );
			Address Scan( );

			bool isDummy( );
		};

end_MEMORY