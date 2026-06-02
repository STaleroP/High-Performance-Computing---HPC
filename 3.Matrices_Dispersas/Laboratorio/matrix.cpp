#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <cstdlib>

using namespace std;
using namespace chrono;

using Matrix = vector<vector<int>>;

// -------------------- Utilidades --------------------

Matrix inicializarMatriz(int n)
{
    Matrix mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat[i][j] = rand() % 10;
    return mat;
}

Matrix transponerMatriz(const Matrix &mat)
{
    int n = mat.size();
    Matrix transpuesta(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            transpuesta[j][i] = mat[i][j];
    return transpuesta;
}

void medirTiempo(const string &nombre, function<void()> funcion)
{
    auto inicio = high_resolution_clock::now();
    funcion();
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << "\u23F1  " << nombre << ": " << duracion.count() << " segundos\n";
}

bool compararMatrices(const Matrix &A, const Matrix &B)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j] != B[i][j])
                return false;
    return true;
}

// -------------------- Main --------------------

int main()
{
    const int n = 1024; // Tamaño de la matriz
    Matrix A, B, BT;
    Matrix C1(n, vector<int>(n, 0)); // A × B (fila x columna)
    Matrix C2(n, vector<int>(n, 0)); // A × B optimizado
    Matrix C3(n, vector<int>(n, 0)); // A × Bᵗ (fila x fila)
    Matrix C4(n, vector<int>(n, 0)); // A × Bᵗ optimizado

    // 1. Inicialización
    medirTiempo("Generación de matrices", [&]()
                {
        A = inicializarMatriz(n);
        B = inicializarMatriz(n); });

    // 2. Multiplicación A × B (fila × columna)
    medirTiempo("Multiplicación A × B (fila × columna)", [&]()
                {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int suma = 0;
                for (int k = 0; k < n; ++k)
                    suma += A[i][k] * B[k][j];
                C1[i][j] = suma;
            } });

    // 3. Multiplicación A × B optimizada (i-k-j)
    medirTiempo("Multiplicación A × B optimizada (i-k-j)", [&]()
                {
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k) {
                int a_ik = A[i][k];
                for (int j = 0; j < n; ++j)
                    C2[i][j] += a_ik * B[k][j];
            } });

    // 4. Transposición de B
    medirTiempo("Transposición de B", [&]()
                { BT = transponerMatriz(B); });

    // 5. Multiplicación A × Bᵗ (fila × fila)
    medirTiempo("Multiplicación A × Bᵗ (fila × fila)", [&]()
                {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int suma = 0;
                for (int k = 0; k < n; ++k)
                    suma += A[i][k] * BT[j][k];
                C3[i][j] = suma;
            } });

    // 6. Multiplicación A × Bᵗ optimizada (i-k-j)
    medirTiempo("Multiplicación A × Bᵗ optimizada (i-k-j)", [&]()
                {
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k) {
                int a_ik = A[i][k];
                for (int j = 0; j < n; ++j)
                    C4[i][j] += a_ik * BT[j][k];
            } });

    // 7. Comparación de resultados
    cout << "\n\U0001F4CA Comparación de resultados:\n";
    cout << "- C1 vs C2: " << (compararMatrices(C1, C2) ? "✅ Iguales" : "❌ Diferentes") << endl;
    cout << "- C1 vs C3: " << (compararMatrices(C1, C3) ? "✅ Iguales" : "❌ Diferentes") << endl;
    cout << "- C1 vs C4: " << (compararMatrices(C1, C4) ? "✅ Iguales" : "❌ Diferentes") << endl;

    return 0;
}
