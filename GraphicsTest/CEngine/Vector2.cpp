#include "Vector2.h"
#include "math.h"

vector2f::vector2f()
	:x(0), y(0)
{}
vector2f::vector2f(float x, float y)
	:x(x), y(y)
{}
vector2f::vector2f(float xy)
	: x(xy), y(xy)
{}

vector2f vector2f::operator+ (const float &num)  const{
	vector2f tmp;
	tmp.x = x + num;
	tmp.y = y + num;
	return tmp;
}
vector2f vector2f::operator- (const float &num)  const{
	vector2f tmp;
	tmp.x = x - num;
	tmp.y = y - num;
	return tmp;
}
vector2f vector2f::operator* (const float &num)  const{
	vector2f tmp;
	tmp.x = x * num;
	tmp.y = y * num;
	return tmp;
}
vector2f vector2f::operator/ (const float &num)  const{
	vector2f tmp;
	tmp.x = x / num;
	tmp.y = y / num;
	return tmp;
}
vector2f vector2f::operator+ (const vector2f &vt)  const{
	vector2f tmp;
	tmp.x = x + vt.x;
	tmp.y = y + vt.y;
	return tmp;
}
vector2f vector2f::operator- (const vector2f &vt)  const{
	vector2f tmp;
	tmp.x = x - vt.x;
	tmp.y = y - vt.y;
	return tmp;
}
vector2f vector2f::operator* (const vector2f &vt)  const{
	vector2f tmp;
	tmp.x = x * vt.x;
	tmp.y = y * vt.y;
	return tmp;
}
vector2f vector2f::operator/ (const vector2f &vt)  const{
	vector2f tmp;
	tmp.x = x / vt.x;
	tmp.y = y / vt.y;
	return tmp;
}
void vector2f::operator+= (const float &num)
{
	x += num;
	y += num;
}
void vector2f::operator-= (const float &num)
{
	x -= num;
	y -= num;
}
void vector2f::operator*= (const float &num)
{
	x *= num;
	y *= num;
}
void vector2f::operator/= (const float &num)
{
	x /= num;
	y /= num;
}
void vector2f::operator+= (const vector2f &vt)
{
	x += vt.x;
	y += vt.y;
}
void vector2f::operator-= (const vector2f &vt)
{
	x -= vt.x;
	y -= vt.y;
}
void vector2f::operator*= (const vector2f &vt)
{
	x *= vt.x;
	y *= vt.y;
}
void vector2f::operator/= (const vector2f &vt)
{
	x /= vt.x;
	y /= vt.y;
}

float vector2f::get_sum() const
{
	return x + y;
}

float vector2f::lengh() const
{
	return sqrt(lengh_square());
}
float vector2f::lengh_square() const
{
	return x*x + y*y;
}
float vector2f::distance_with(const vector2f &vt) const
{
	return sqrt(distance_square_with(vt));
}
float vector2f::distance_square_with(const vector2f &vt) const
{
	return pow(x - vt.x, 2) + pow(y - vt.y, 2);
}
float vector2f::distance_between(const vector2f &vt1, const vector2f &vt2)
{
	return vt1.distance_with(vt2);
}
float vector2f::distance_square_between(const vector2f &vt1, const vector2f &vt2)
{
	return vt1.distance_square_with(vt2);
}
float vector2f::dot_product_with(const vector2f &vt) const
{
	return x * vt.x + y * vt.y;
}
float vector2f::angle_to_radian(const float &angle)
{
	return angle * PI / 180;
}
float vector2f::radian_to_angle(const float &radian)
{
	return radian * 180 / PI;
}
float vector2f::angel_with(const vector2f &vt) const
{
	return radian_to_angle(radian_with(vt));
}
float vector2f::angel_between(const vector2f &vt1, const vector2f &vt2)
{
	return vt1.angel_with(vt2);
}
float vector2f::radian_with(const vector2f &vt) const
{
	return atan2(vt.y, vt.x) - atan2(y, x);
}
float vector2f::radian_between(const vector2f &vt1, const vector2f &vt2)
{
	return vt1.radian_with(vt2);
}
float vector2f::normalize_radian(const float &radian)
{
	if (radian < 0)
	{
		return radian + 2 * PI;
	}
}
float vector2f::normalize_angle(const float &angle)
{
	if (angle < 0)
	{
		return angle + 360;
	}
}
void vector2f::normalize()
{
	*this /= lengh();
}
vector2f vector2f::get_normalize() const
{
	return *this / this->lengh();
}
vector2f vector2f::normalize_vector2f(const vector2f &vt)
{
	return vt.get_normalize();
}
vector2f vector2f::get_othogonal() const
{
	return vector2f(-y, x);
}
void vector2f::rotateA(const float &angle, const vector2f &vt2)
{
	float radian = angle_to_radian(angle);
	rotateR(radian, vt2);
}
void vector2f::rotateR(const float &radian, const vector2f &vt2)
{
	this->x = ((this->x - vt2.x) * cos(radian)) - ((this->y - vt2.y) * sin(radian)) + vt2.x;
	this->y = ((this->y - vt2.y) * cos(radian)) - ((this->x - vt2.x) * sin(radian)) + vt2.y;
}

vector2f vector2f::getRotateA(const float &angle, const vector2f &vt2)
{
	float radian = angle_to_radian(angle);
	return getRotateR(radian, vt2);
}
vector2f vector2f::getRotateR(const float &radian, const vector2f &vt2)
{
	vector2f vt;
	vt.x = ((this->x - vt2.x) * cos(radian)) - ((this->y - vt2.y) * sin(radian)) + vt2.x;
	vt.y = ((this->y - vt2.y) * cos(radian)) - ((this->x - vt2.x) * sin(radian)) + vt2.y;
	return vt;
}