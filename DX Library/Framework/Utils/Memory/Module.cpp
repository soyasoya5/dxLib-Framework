#include "Module.h"

Utils::Memory::Module::Module(const ulong & image, const ulong & size, const Utils::String &_Name)
	: _image(image), _size(size), _module(_Name)
{ }

ulong Utils::Memory::Module::Image() const
{
	return _image;
}

ulong Utils::Memory::Module::Size() const
{
	return _size;
}

Utils::String Utils::Memory::Module::Name() const
{
	return _module;
}

bool Utils::Memory::Module::isDummy() const
{
	return _module == "_Dummy";
}

ulong Utils::Memory::Module::operator*() const
{
	return _image;
}
