#include "Direct_Access_Image.h"
#include "stdafx.h"
#include "particle.h"
#include "fixed_float.h"

class ElementalDust
{
	int nr_particles_int;
	particle *partiles_prt;

public:
	ElementalDust();
	~ElementalDust();

	void import(KImage *import, float multiplicator);

	void import(char *file_name);

	void import(void *file_contents, size_t size);

	void SaveAs(char *file_name);

	void SaveAs(KImage *import, float multiplicator);

	ElementalDust& operator= (ElementalDust b_flt);

	bool operator==(ElementalDust &b_flt);

	bool operator!=(ElementalDust &b_flt);

	void sortParticles();

private:
	void clear();
};