#include "Vector2.h"
#include "math.h"
#include "Region.h"
#include <math.h>

begin_MATH

float Vector2::Dot( const Vector2 &_Other ) const
{
	
	return (x * _Other.x) + (y * _Other.y);
}

bool Vector2::Intersects(const __MATH Region & _Area) const
{
	return (this->x >= _Area.position.x) && (this->y >= _Area.position.y) &&
		   (this->x <= _Area.position.x + _Area.size.x) && (this->y <= _Area.position.y + _Area.size.y);
}

float Vector2::Magnitude() const
{
	return ::sqrt( x*x + y*y );
}

Vector2 & Vector2::operator+=(const Vector2 & _Other)
{
	this->x += _Other.x;
	this->y += _Other.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & _Other)
{
	this->x -= _Other.x;
	this->y -= _Other.y;
	return *this;
}

Vector2 & Vector2::operator=(const Vector2 & _Other)
{
	this->x = _Other.x;
	this->y = _Other.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 & _Other) const
{
	Vector2 _Tmp;
	_Tmp.x = (this->x + _Other.x);
	_Tmp.y = (this->y + _Other.y);
	return _Tmp;
}

Vector2 Vector2::operator-(const Vector2 & _Other) const
{
	Vector2 _Tmp;
	_Tmp.x = (this->x - _Other.x);
	_Tmp.y = (this->y - _Other.y);
	return _Tmp;
}

Vector2 Vector2::operator*(const Vector2 & _Other) const
{
	Vector2 _Tmp;
	_Tmp.x = (this->x * _Other.x);
	_Tmp.y = (this->y * _Other.y);
	return _Tmp;
}

Vector2 Vector2::operator/(const Vector2 & _Other) const
{
	Vector2 _Tmp;
	_Tmp.x = (this->x / _Other.x);
	_Tmp.y = (this->y / _Other.y);
	return _Tmp;
}

bool Vector2::operator>(const Vector2 & _Other) const
{
	return (this->x > _Other.x && this->y > _Other.y);
}

bool Vector2::operator>=(const Vector2 & _Other) const
{
	return (this->x >= _Other.x && this->y >= _Other.y);
}

bool Vector2::operator<(const Vector2 & _Other) const
{
	return (this->x < _Other.x && this->y < _Other.y);
}

bool Vector2::operator<=(const Vector2 & _Other) const
{
	return (this->x <= _Other.x && this->y <= _Other.y);
}

bool Vector2::operator==(const Vector2 & _Other) const
{
	return (this->x == _Other.x && this->y == _Other.y);
}

bool Vector2::operator!=(const Vector2 & _Other) const
{
	return !(*this == _Other);
}


end_MATH
