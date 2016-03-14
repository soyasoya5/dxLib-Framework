#include "Region.h"
#include "Vector2.h"

begin_MATH

void Region::MoveBy(const __MATH Vector2 & _Amount)
{
	position += _Amount;
}

void Region::MoveTo(const __MATH Vector2 & _Position)
{
	position = _Position;
}

void Region::ResizeBy(const __MATH Vector2 & _Amount)
{
	size += _Amount;
}

void Region::ResizeTo(const __MATH Vector2 & _Size)
{
	size = _Size;
}

bool Region::Intersects(const __MATH Region & _Other)
{
	return _Other.position.Intersects( *this );
}

end_MATH
