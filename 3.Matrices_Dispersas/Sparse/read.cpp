#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Use: %s <file_name.mat>\n", argv[0]);
		return 1;
	}

	FILE *file = fopen(argv[1], "rb");

	int header[5];
	fread(header, sizeof(int), 5, file);

	int format = header[0] % 10;
	int type = header[0] - format;

	printf("format: %i (%s)\n", format, (format == 0) ? "full matrix" : (format == 1) ? "text"
																	: (format == 2)	  ? "Sparse matrix"
																					  : "INVALID");
	printf("type:   %i (%s)\n", type, (type == 0) ? "double" : (type == 10) ? "float"
														   : (type == 20)	? "int"
														   : (type == 30)	? "short"
														   : (type == 40)	? "unsigned short"
														   : (type == 50)	? "unsigned char"
																			: "INVALID");

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
		printf("field: %i (%s)\n", field, (field == 0) ? "real" : (field == 1) ? "complex"
																			   : "INVALID");
		printf("name:  %s\n", name);

		double *tmp = new double[rows * cols];
		fread(tmp, sizeof(double), rows * cols, file);

		double *matrix = new double[rows * cols];
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
		// Text matrix (Not used)
	}
	else if (format == 2) // Sparse matrix
	{
		// Extrae metadatos del encabezado
		int nnz = header[1] - 1;
		int field = header[2];
		int name_size = header[4];

		// Lee el nombre de la matriz
		char name[128] = {0};
		fread(name, 1, name_size, file);

		// Lee vectores I, J y V, junto con filas, columnas y dummy
		double *I = new double[nnz];
		fread(I, sizeof(double), nnz, file);
		double rows;
		fread(&rows, sizeof(double), 1, file);

		double *J = new double[nnz];
		fread(J, sizeof(double), nnz, file);
		double cols;
		fread(&cols, sizeof(double), 1, file);

		double *V = new double[nnz];
		fread(V, sizeof(double), nnz, file);
		double dummy;
		fread(&dummy, sizeof(double), 1, file);

		// Imprime metadatos en consola
		printf("format: %i (Sparse matrix)\n", format);
		printf("type:   %i (%s)\n", type,
			   (type == 0) ? "double" : (type == 10) ? "float"
									: (type == 20)	 ? "int"
									: (type == 30)	 ? "short"
									: (type == 40)	 ? "unsigned short"
									: (type == 50)	 ? "unsigned char"
													 : "INVALID");
		printf("nnz+1: %d\n", nnz + 1);
		printf("field: %d (%s)\n", field, (field == 0) ? "real" : "complex");
		printf("name:  %s\n", name);
		printf("rows:  %.0f\n", rows);
		printf("cols:  %.0f\n", cols);

		// Imprime valores no nulos en consola
		printf("\nValores no nulos:\n");
		for (int i = 0; i < nnz; ++i)
			printf("(%d, %d) = %.2f\n", (int)I[i], (int)J[i], V[i]);

		// Reconstruye matriz completa
		double *dense = new double[(int)rows * (int)cols]();
		for (int i = 0; i < nnz; ++i)
		{
			int r = (int)I[i] - 1;
			int c = (int)J[i] - 1;
			dense[r * (int)cols + c] = V[i];
		}

		// Imprime matriz completa en consola
		printf("\nMatriz completa:\n");
		for (int i = 0; i < (int)rows; ++i)
		{
			for (int j = 0; j < (int)cols; ++j)
				printf("%7.2f", dense[i * (int)cols + j]);
			printf("\n");
		}

		// Crea nombre de archivo .txt basado en el nombre del binario
		char txt_name[256];
		strcpy(txt_name, argv[1]);
		char *dot = strrchr(txt_name, '.');
		if (dot)
			strcpy(dot, ".txt");
		else
			strcat(txt_name, ".txt");

		// Escribe metadatos y valores no nulos en archivo .txt
		FILE *out = fopen(txt_name, "w");
		if (out)
		{
			fprintf(out, "format: %i (Sparse matrix)\n", format);
			fprintf(out, "type:   %i (%s)\n", type,
					(type == 0) ? "double" : (type == 10) ? "float"
										 : (type == 20)	  ? "int"
										 : (type == 30)	  ? "short"
										 : (type == 40)	  ? "unsigned short"
										 : (type == 50)	  ? "unsigned char"
														  : "INVALID");
			fprintf(out, "nnz+1: %d\n", nnz + 1);
			fprintf(out, "field: %d (%s)\n", field, (field == 0) ? "real" : "complex");
			fprintf(out, "name:  %s\n", name);
			fprintf(out, "rows:  %.0f\n", rows);
			fprintf(out, "cols:  %.0f\n", cols);
			fprintf(out, "\nValores no nulos:\n");
			for (int i = 0; i < nnz; ++i)
				fprintf(out, "(%d, %d) = %.2f\n", (int)I[i], (int)J[i], V[i]);
			fclose(out);
		}
		else
		{
			fprintf(stderr, "No se pudo abrir el archivo de salida.\n");
		}

		// Libera memoria
		delete[] I;
		delete[] J;
		delete[] V;
		delete[] dense;
	}

	fclose(file);
	return 0;
}
