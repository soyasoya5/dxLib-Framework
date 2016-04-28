#include "Region.h"
#include "Vector2.h"

begin_MATH

Region & Region::MoveBy(const ::dx::lib::Math::Vector2 & _Amount)
{
	position += _Amount;
	return *this;
}

Region & Region::MoveTo(const ::dx::lib::Math::Vector2 & _Position)
{
	position = _Position;
	return *this;
}

Region & Region::ResizeBy(const ::dx::lib::Math::Vector2 & _Amount)
{
	size += _Amount;
	return *this;
}

Region & Region::ResizeTo(const ::dx::lib::Math::Vector2 & _Size)
{
	size = _Size;
	return *this;
}

bool Region::Intersects(const ::dx::lib::Math::Region & _Other)
{
	return _Other.position.Intersects( *this );
}

end_MATH
