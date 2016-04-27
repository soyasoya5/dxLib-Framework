#include "BasePainter.h"

begin_GRAPHICS

BasePainter* BasePainter::_Singleton = nullptr;

BasePainter * BasePainter::getSingleton()
{
	return _Singleton;
}

void BasePainter::setSingleton(BasePainter * ptr)
{
	_Singleton = ptr;
}



end_GRAPHICS
