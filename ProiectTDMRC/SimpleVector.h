#pragma once

#include "stdafx.h"

//TO DO: NOT thread safe!

template <typename T>
class SimpleVector
{
private:
	T *elements;
	unsigned int nr_of_elements;
	unsigned int allocated_size;

public:
	SimpleVector()
	{
		init();
	}

	SimpleVector(const SimpleVector &right)
    {
		init();

        *this = right;
    }

	~SimpleVector()
	{
		if(elements)
			free(elements);
		elements = NULL;
		nr_of_elements=0;
		allocated_size=0;
	}

	void init()
	{
		elements = NULL;
		nr_of_elements=0;
		allocated_size=0;
	}

	void insert(T element)
	{
		if(elements == NULL || nr_of_elements == allocated_size)
		{
			allocated_size = allocated_size * 2 + 1;
			T *new_elements = (T*)malloc(sizeof(T)*allocated_size);

			for(unsigned int i=0; i<nr_of_elements; i++)
				new_elements[i] = elements[i];

			delete[] elements;
			elements = new_elements;
		}

		elements[nr_of_elements] = element;
	}

	void remove(int index)
	{
		nr_of_elements--;

		for(unsigned int i=index; i<nr_of_elements; i++)
				elements[i] = elements [i+1];
	}

	unsigned int size()
	{
		return nr_of_elements;
	}

	T& operator[](unsigned int it)
	{
		return elements[it];
	}

	SimpleVector& operator=(SimpleVector &right)
	{
		if(&right == this)
			return *this;

		if(elements)
			free(elements);

		allocated_size = right.allocated_size;
		nr_of_elements = right.nr_of_elements;

		T *new_elements = (T*)malloc(sizeof(T)*allocated_size);

		for(unsigned int i=0; i<nr_of_elements; i++)
				elements[i] = right.elements[i];

		return *this;
	}
};