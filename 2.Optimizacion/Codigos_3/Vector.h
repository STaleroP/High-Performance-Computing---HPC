#ifndef __Vector_h__
#define __Vector_h__

struct Vector
{
	int size;
	
	double* data;
	
	Vector();

	Vector(const Vector& A);

	Vector(int s);
	
	~Vector();

	Vector& operator = (const Vector& A);
	
	void Resize(int s);
};

Vector operator - (const Vector& A);

Vector operator + (const Vector& A, const Vector& B);

Vector operator * (double a, const Vector& B);

#endif
