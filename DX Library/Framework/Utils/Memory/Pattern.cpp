#include "Pattern.h"
#include "Module.h"
#include "MemoryBase.h"

using namespace dx;

Utils::Memory::Address::Address(Module * _Module, const uint & _Offset)
	: _module( _Module ), _offset( _Offset )
{ }

bool Utils::Memory::Address::IsNullOrZero()
{
	return _module == nullptr || _module->isDummy( );
}

Module * Utils::Memory::Address::getModule( )
{
	return _module;
}

uint Utils::Memory::Address::getOffset( )
{
	return _offset;
}

uint Utils::Memory::Address::get_addr( )
{
	return (*_module) + _offset;
}

std::vector<uint> Utils::Memory::Pattern::break_pattern()
{
	std::vector<uint> _Ret;

	auto pattern = _pattern;
	while( true )
	{
		auto npos = pattern.find( " " );
		if ( npos != String::bad )
		{
			auto sub = pattern.substr( 0, npos );
			if ( sub == "??" )
				_Ret.push_back( static_cast<uint>( -1 ) );
			else
				_Ret.push_back( sub.to<uint>( ) );
			pattern.erase( 0, npos + 1 );
		}
		else
		{
			if ( !pattern.empty( ) ) 
			{
				if ( pattern == "??" )
					_Ret.push_back( static_cast<uint>( -1 ) );
				else
					_Ret.push_back( pattern.to<uint>( ) );
			}
			break;
		}
	}
	return _Ret;
}

bool Utils::Memory::Pattern::memcmp(std::vector<uint>& _Pattern, byte * _Module)
{
	for ( auto&x : _Pattern )
	{
		if ( x == static_cast<uint>( -1 ) ) { }
		else if ( x != *_Module ) 
			return false;
		++_Module;
	}
	return true;
}

Utils::Memory::Pattern::Pattern(const Utils::String & _Pattern, Module * _Module, MemoryBase * _Memory)
	: _pattern( _Pattern ), _module( _Module ), _memory( _Memory )
{ }

void Utils::Memory::Pattern::ChangeModule(Module * _Module)
{
	_module = _Module;
}

void Utils::Memory::Pattern::ChangeMemoryBase(MemoryBase * _Memory)
{
	_memory = _Memory;
}

void Utils::Memory::Pattern::ChangePattern(const Utils::String & _Pattern)
{
	_pattern = _Pattern;
}


Address Utils::Memory::Pattern::Scan()
{
	auto pattern = break_pattern( );
	byte* bytes = new byte[_module->Size( )];
	auto delete_function = []( byte* ptr )
	{
		// Optimizer apparently think this function is uesless
		// and will delete it, however adding these nops prevent that.
		__asm nop;
		__asm nop;
		__asm nop;
		delete[] ptr;
	};

	ScopeExit<byte> guard( bytes, 
					       delete_function);

	// Read module into memory.
	if ( !_memory->read_bytes( *_module, 0, bytes, _module->Size( ) ) )
		return Address{ &_memory->moduleAt( "_Dummy" ), 0x0 };

	uint count = 0;
	while( (count + pattern.size( )) < _module->Size( ) )
	{
		// Compare memory
		if ( memcmp( pattern, bytes + count ) )
			return Address{ _module, count };
		++count;
	}
	return Address{ &_memory->moduleAt( "_Dummy" ), 0x0 };
}

bool Utils::Memory::Pattern::isDummy()
{
	return _module->isDummy( );
}
