#include "MemoryBase.h"
#include "Module.h"

Utils::Memory::Module & Utils::Memory::MemoryBase::moduleAt(const Utils::String & _Name)
{
	for ( auto&x : _modules )
		if ( x.Name( )  == _Name )
			return x;
	return _modules[0];
}
