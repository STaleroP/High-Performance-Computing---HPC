#ifndef __mem_h__
#define __mem_h__

typedef __SIZE_TYPE__ size_t;

void* operator new [] (size_t size) throw();

void operator delete [] (void* object) throw();

#endif
