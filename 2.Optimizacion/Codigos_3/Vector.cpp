#include "mem.h"
#include "Vector.h"
#include <stdio.h>

Vector::Vector()
{
	printf("%40p Constructor()\n", (void*)(this));
	size = 0;
	data = (double*)0;
}

Vector::Vector(const Vector& A)
{
	printf("%40p Constructor(%p)\n", (void*)(this), (void*)&A);
	size = A.size;
	data = new double[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = A.data[i];
	}
}

Vector::Vector(int s)
{
	printf("%40p Constructor(%i)\n", (void*)(this), s);
	size = s;
	data = new double[size];
}

Vector::~Vector()
{
	printf("%40p Destructor()\n", (void*)(this));
	delete [] data;
}

Vector& Vector::operator = (const Vector& A)
{
	printf("%40p operator = (%p)\n", (void*)(this), (void*)&A);
	if (size != A.size)
	{
		Resize(A.size);
	}
	for (int i = 0; i < size; ++i)
	{
		data[i] = A.data[i];
	}
	return *this;
}

void Vector::Resize(int s)
{
	printf("%40p Resize(%i)\n", (void*)(this), s);
	delete [] data;
	size = s;
	data = new double[size];
}


Vector operator - (const Vector& A)
{
	Vector C(A.size);
	printf("%40p operator - (%p)\n", (void*)&C, (void*)&A);
	for (int i = 0; i < C.size; ++i)
	{
		C.data[i] = -A.data[i];
	}
	return C;
}

Vector operator + (const Vector& A, const Vector& B)
{
	Vector C(A.size);
	printf("%40p operator + (%p, %p)\n", (void*)&C, (void*)&A, (void*)&B);
	for (int i = 0; i < C.size; ++i)
	{
		C.data[i] = A.data[i] + B.data[i];
	}
	return C;
}

Vector operator * (double a, const Vector& B)
{
	Vector C(B.size);
	printf("%40p operator * (%f, %p)\n", (void*)&C, a, (void*)&B);
	for (int i = 0; i < C.size; ++i)
	{
		C.data[i] = a*B.data[i];
	}
	return C;
}
