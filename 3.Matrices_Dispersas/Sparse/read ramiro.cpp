#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Use: %s <file_name.mat>\n", argv[0]);
		return 1;
	}

	FILE* file = fopen(argv[1], "rb");

	int header[5];
	fread(header, sizeof(int), 5, file);

	int format = header[0] % 10;
	int type = header[0] - format;

	printf("format: %i (%s)\n", format, (format == 0) ? "full matrix" : (format == 1) ? "text" : (format == 2) ? "Sparse matrix" : "INVALID");
	printf("type:   %i (%s)\n", type, (type == 0) ? "double" : (type == 10) ? "float" : (type == 20) ? "int" : (type == 30) ? "short" : (type == 40) ? "unsigned short" : (type == 50) ? "unsigned char" : "INVALID");

	if (format == 0) // Full matrix
	{
		int rows = header[1];
		int cols = header[2];
		int field = header[3];
		int name_size = header[4];
		char name[128];
		fread(name, name_size, 1, file);

		printf("rows:  %i\n", rows);
		printf("cols:  %i\n", cols);
		printf("field: %i (%s)\n", field, (field == 0) ? "real" : (field == 1) ? "complex" : "INVALID");
		printf("name:  %s\n", name);

		double* tmp = new double[rows * cols];
		fread(tmp, sizeof(double), rows * cols, file);

		double* matrix = new double[rows * cols];
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				matrix[i * cols + j] = tmp[j * rows + i];
				printf("%7.2f", matrix[i * cols + j]);
			}
			printf("\n");
		}

		delete[] matrix;
		delete[] tmp;
	}
	else if (format == 1)
	{
		// Text matrix 
	}
	else if (format == 2)
	{
	int nnz_plus_one = header[1];
	int nnz = nnz_plus_one - 1;
	int field = header[2];
	int dummy = header[3];
	int name_size = header[4];

	char name[128];
	fread(name, name_size, 1, file);

	printf("nnz+1: %i\n", nnz_plus_one);
	printf("field: %i (%s)\n", field, (field == 0) ? "real" : (field == 1) ? "complex" : "INVALID");
	printf("name:  %s\n", name);

	
	double* I_d = new double[nnz];
	fread(I_d, sizeof(double), nnz, file);
	double rows;
	fread(&rows, sizeof(double), 1, file);

	
	double* J_d = new double[nnz];
	fread(J_d, sizeof(double), nnz, file);
	double cols;
	fread(&cols, sizeof(double), 1, file);

	
	double* V = new double[nnz];
	fread(V, sizeof(double), nnz, file);

	double zero;
	fread(&zero, sizeof(double), 1, file);

	printf("rows: %.0f\n", rows);
	printf("cols: %.0f\n", cols);

	// Mostrar valores dispersos
	printf("\nValores no nulos:\n");
	for (int i = 0; i < nnz; ++i)
	{
		printf("(%d, %d) = %.2f\n", (int)I_d[i], (int)J_d[i], V[i]);
	}

	// Crear matriz densa e inicializar con ceros
	double* dense = new double[(int)rows * (int)cols];
	for (int i = 0; i < (int)(rows * cols); ++i)
		dense[i] = 0.0;

	// Llenar valores no nulos
	for (int i = 0; i < nnz; ++i)
	{
		int r = (int)I_d[i] - 1; 
		int c = (int)J_d[i] - 1;
		dense[r * (int)cols + c] = V[i];
	}

	// Imprimir matriz completa
	printf("\nMatriz completa:\n");
	for (int i = 0; i < (int)rows; ++i)
	{
		for (int j = 0; j < (int)cols; ++j)
		{
			printf("%7.2f", dense[i * (int)cols + j]);
		}
		printf("\n");
	}

	delete[] I_d;
	delete[] J_d;
	delete[] V;
	delete[] dense;
	}

	fclose(file);
	return 0;
}
