#include "Module.h"

begin_MEMORY

Module::Module(const ulong & image, const ulong & size, const __LIB String &_Name)
	: _image(image), _size(size), _module(_Name)
{ }

ulong Module::Image() const
{
	return _image;
}

ulong Module::Size() const
{
	return _size;
}

__LIB String Module::Name() const
{
	return _module;
}

bool Module::isDummy() const
{
	return _module == "_Dummy";
}

ulong Module::operator*() const
{
	return _image;
}


end_MEMORY