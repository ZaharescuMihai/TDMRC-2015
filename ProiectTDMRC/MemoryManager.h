#pragma once
#include "stdafx.h"

#include "SimpleVector.h"

class MemoryManager
{
private:
	size_t memory_used;
	size_t max_memory_used;

	static int nr_of_handlers;

	static MemoryManager *instance;

	//TO DO: use map, but pay atention that map uses new for each element, causing reentering the allocation function and stack overflow
	SimpleVector<std::pair<size_t, size_t>> sizes;


	MemoryManager();

	//MemoryManager(const MemoryManager &right);

	~MemoryManager();

public:
	static MemoryManager* getInstance();

	static void releaseInstance();

	void mmAlloc(void *address, size_t size);

	void mmFree(void *address);

	void dumpInfo();

	void init();

	MemoryManager& operator=(MemoryManager &right);
};

void* operator new(size_t sz) ;

void operator delete(void* m) ;

