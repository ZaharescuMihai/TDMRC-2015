#ifndef __FIXED_FLOAT_H__
#define __FIXED_FLOAT_H__

/**
Sorry for the name :D double wouldn't have worked either as it is only 2 bytes.
It means fixed (not floating) precision real number.
*/
class fixed_float
{
	//first 8 bits = integer, last 8 bits = fractionary
	unsigned short bits; 
public:
	fixed_float(unsigned char integer_bits, unsigned char frqactional_bits);

	fixed_float(float data=0);

	fixed_float& operator= (const float &b_flt);

	float operator* (const float &b_flt);

	float operator/ (const float &b_flt);

	float operator+ (const float &b_flt);

	float operator- (const float &b_flt);

	const fixed_float operator* (const fixed_float &b_flt);

	const fixed_float operator/ (const fixed_float &b_flt);

	const fixed_float operator+ (const fixed_float &b_flt);

	const fixed_float operator- (const fixed_float &b_flt);

	bool operator< (const fixed_float &b_flt);

	bool operator> (const fixed_float &b_flt);

	bool operator<= (const fixed_float &b_flt);

	bool operator>= (const fixed_float &b_flt);

	bool operator!= (const fixed_float &b_flt);

	bool operator== (const fixed_float &b_flt);

	bool operator< (const float &b_flt);

	bool operator> (const float &b_flt);

	bool operator<= (const float &b_flt);

	bool operator>= (const float &b_flt);

	bool operator!= (const float &b_flt);

	bool operator== (const float &b_flt);

	float getFloat() const;

	unsigned char getFractionalBits();

	unsigned char getIntegerBits();

private:
	float getSubunitry();
};

#endif