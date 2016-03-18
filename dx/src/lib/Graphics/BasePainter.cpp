#include "BasePainter.h"

begin_GRAPHICS

BasePainter* BasePainter::_Singleton = nullptr;

BasePainter * BasePainter::getSingleton()
{
	return _Singleton;
}

void BasePainter::setSingleton(BasePainter * _Putr)
{
	_Singleton = _Putr;
}



end_GRAPHICS
