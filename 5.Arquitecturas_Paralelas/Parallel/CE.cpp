#include <iostream>
#include <vector>
#include <cmath>
#include <fstream> // Para manejo de archivos

int main()
{
    int n;
    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;

    std::vector<bool> es_primo(n + 1, true);
    es_primo[0] = es_primo[1] = false;

    int limite = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= limite; ++i)
    {
        if (es_primo[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                es_primo[j] = false;
            }
        }
    }

    // Crear y abrir el archivo de salida
    std::ofstream archivo("ce.txt");
    if (!archivo)
    {
        std::cerr << "No se pudo crear el archivo." << std::endl;
        return 1;
    }

    archivo << "Numeros primos hasta " << n << ":\n";
    for (int i = 2; i <= n; ++i)
    {
        if (es_primo[i])
        {
            archivo << i << " ";
        }
    }

    archivo << std::endl;
    archivo.close(); // Cerrar el archivo

    return 0;
}
