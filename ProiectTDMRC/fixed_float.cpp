#include "fixed_float.h"

fixed_float::fixed_float(unsigned char integer_bits, unsigned char fractional_bits)
{
	float flt = integer_bits + fractional_bits/256.0f;
	
	*this = flt;
}

fixed_float::fixed_float(float data)
{
	*this = data;
}

fixed_float& fixed_float::operator=(const float &b)
{
	bits = ((unsigned short)(b*256.0f));

	return *this;
}

float fixed_float::getFloat() const
{
	float ret;
	ret = ((float)bits)/256.0f;
	return ret;
}

unsigned char fixed_float::getFractionalBits()
{
	float flt = getFloat();

	return (unsigned char)(((flt - (unsigned char)flt))*256);
}

unsigned char fixed_float::getIntegerBits()
{
	float flt = getFloat();

	return (unsigned char)flt;
}

float fixed_float::operator* (const float &b_flt)
{
	return getFloat() * b_flt;
}

float fixed_float::operator/ (const float &b_flt)
{
	return getFloat() / b_flt;
}

float fixed_float::operator+ (const float &b_flt)
{
	return getFloat() + b_flt;
}

float fixed_float::operator- (const float &b_flt)
{
	return getFloat() - b_flt;
}

const fixed_float fixed_float::operator* (const fixed_float &b_flt)
{
	return fixed_float(getFloat() * b_flt.getFloat());
}

const fixed_float fixed_float::operator/ (const fixed_float &b_flt)
{
	return fixed_float(getFloat() / b_flt.getFloat());
}

const fixed_float fixed_float::operator+ (const fixed_float &b_flt)
{
	return fixed_float(getFloat() + b_flt.getFloat());
}

const fixed_float fixed_float::operator- (const fixed_float &b_flt)
{
	return fixed_float(getFloat() - b_flt.getFloat());
}

bool fixed_float::operator<(const fixed_float &b_fflt)
{
	return bits < b_fflt.bits;
}

bool fixed_float::operator>(const fixed_float &b_fflt)
{
	return bits > b_fflt.bits;
}

bool fixed_float::operator<=(const fixed_float &b_fflt)
{
	return bits <= b_fflt.bits;
}

bool fixed_float::operator>=(const fixed_float &b_fflt)
{
	return bits >= b_fflt.bits;
}

bool fixed_float::operator!=(const fixed_float &b_fflt)
{
	return bits != b_fflt.bits;
}

bool fixed_float::operator==(const fixed_float &b_fflt)
{
	return bits == b_fflt.bits;
}

bool fixed_float::operator<(const float &b_fflt)
{
	return getFloat() < b_fflt;
}

bool fixed_float::operator>(const float &b_fflt)
{
	return getFloat() > b_fflt;
}

bool fixed_float::operator<=(const float &b_fflt)
{
	return getFloat() <= b_fflt;
}

bool fixed_float::operator>=(const float &b_fflt)
{
	return getFloat() >= b_fflt;
}

bool fixed_float::operator!=(const float &b_fflt)
{
	return getFloat() != b_fflt;
}

bool fixed_float::operator==(const float &b_fflt)
{
	return getFloat() == b_fflt;
}

