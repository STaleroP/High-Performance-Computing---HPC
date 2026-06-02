#include "mem.h"
#include <stdio.h>
#include <malloc.h>

#ifdef REPORT_MEM
	static size_t allocated = 0;
#endif

void* operator new [] (size_t size) throw()
{
	void* object = malloc(size);
	#ifdef REPORT_MEM
		size_t m_size = malloc_usable_size(object);
		allocated += m_size;
		printf("%11li new(%li)\n", allocated, m_size);
	#endif
	return object; 
}

void operator delete [] (void* object) throw()
{
	#ifdef REPORT_MEM
		size_t m_size = malloc_usable_size(object);
		allocated -= m_size;
		printf("%11li delete(%li)\n", allocated, m_size);
	#endif
	free(object);
}
