#include "MemoryBase.h"
#include "Module.h"

begin_MEMORY

__MEMORY Module & MemoryBase::moduleAt(const __LIB String & _Name)
{
	for ( auto&x : _modules )
		if ( x.Name( )  == _Name )
			return x;
	return _modules[0];
}


end_MEMORY