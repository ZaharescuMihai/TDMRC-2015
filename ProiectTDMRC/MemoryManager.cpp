#include "stdafx.h"
#include "MemoryManager.h"




MemoryManager *MemoryManager::instance = NULL;
int MemoryManager::nr_of_handlers = 0;

MemoryManager::MemoryManager()
{
	memory_used=0;
	max_memory_used=0;

	sizes = SimpleVector<std::pair<size_t, size_t>>();
}

/*MemoryManager(const MemoryManager &right)
{
}*/

void MemoryManager::mmAlloc(void *address, size_t size)
{
	sizes.insert(std::pair<size_t,size_t>((size_t)address, size));
	memory_used += size;

	if(max_memory_used < memory_used)
		max_memory_used = memory_used;
}

void MemoryManager::mmFree(void *address)
{
	size_t val = (size_t)address;
	size_t size = 0;

	for(unsigned it = 0; it!=sizes.size(); it++)
		if(sizes[it].first == val)
		{
			size = sizes[it].second;
			sizes.remove(it);
			break;
		}
	
		//TO DO: size is 0
	//std::cout<<size<<" ";
	memory_used -= size;
}

MemoryManager* MemoryManager::getInstance()
{
	if(instance==NULL)
	{
		
		instance = (MemoryManager*)calloc(sizeof(MemoryManager), 1);

		//TO DO: *instance contains garbage info. When the destructor will be called at the assignment, garbage will be tried to be freed
		//patched inside the operator= with sizes.init();
		*instance = MemoryManager();
	}

	nr_of_handlers ++;

	return instance;
}

void MemoryManager::releaseInstance()
{
	nr_of_handlers --;

	if(nr_of_handlers<=0)
		delete instance;
}

MemoryManager::~MemoryManager()
{
	nr_of_handlers--;
	
	if(instance && nr_of_handlers>=0)
	{
		dumpInfo();
		free(instance);
	}
}

void MemoryManager::dumpInfo()
{
	if(memory_used != 0)
		std::cout<<"Memory Leaks Detected!: "<<memory_used/1024.0<<" kB\n";
	else
		std::cout<<"No Memory Leaks Detected!\n";

	std::cout<<"Max Memory Used: "<<max_memory_used/1024.0<<" kB\n";
}

MemoryManager& MemoryManager::operator=(MemoryManager &right)
{
	if(this == &right)
		return *this;

	memory_used = right.memory_used;
	max_memory_used = right.max_memory_used;
	instance = right.instance;

	//sizes.init();
	sizes = right.sizes;
}



void* operator new(size_t sz) 
{
  void* m = malloc(sz);
  if(!m) printf("out of memory");

  MemoryManager::getInstance()->mmAlloc(m, sz);

  return m;
}

void operator delete(void* m) 
{
	MemoryManager::getInstance()->mmFree(m);
	free(m);
}

