import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os
import sys

def analytical_solution(name, x, y):
    if name == 'euler':
        return np.exp(x * y)
    elif name == 'laplace':
        return np.log(y**2 + x**2)
    elif name == 'constanza':
        return (x - y)**2
    elif name == 'fraccion':
        with np.errstate(divide='ignore', invalid='ignore'):
            result = x * y * np.log(np.where(x * y > 0, x * y, 1))
            result[np.isnan(result)] = 0
            return result
    return None

def process_solution_file(input_path, output_path):
    filename = os.path.basename(input_path)
    name = filename.split('.')[0]
    data = np.loadtxt(input_path)

    x_vals = data[:, 0]
    y_vals = data[:, 1]
    z_vals = data[:, 2]

    n = int(np.sqrt(len(x_vals)))
    X = x_vals.reshape(n, n)
    Y = y_vals.reshape(n, n)
    Z = z_vals.reshape(n, n)

    Z_analytical = analytical_solution(name, X, Y)

    fig = plt.figure(figsize=(15, 10 if Z_analytical is not None else 5))

    if Z_analytical is not None:
        ax1 = fig.add_subplot(2, 2, 1, projection='3d')
        ax1.plot_surface(X, Y, Z, cmap='viridis', alpha=0.7)
        ax1.plot_surface(X, Y, Z_analytical, cmap='plasma', alpha=0.5)
        ax1.set_title(f'3D Numérica vs Analítica - {name}')

        ax2 = fig.add_subplot(2, 2, 2)
        pcm2 = ax2.pcolormesh(X, Y, Z, shading='auto', cmap='viridis')
        fig.colorbar(pcm2, ax=ax2)
        ax2.set_title(f'Numérica - {name}')

        ax3 = fig.add_subplot(2, 2, 3)
        pcm3 = ax3.pcolormesh(X, Y, Z_analytical, shading='auto', cmap='plasma')
        fig.colorbar(pcm3, ax=ax3)
        ax3.set_title(f'Analítica - {name}')

        ax4 = fig.add_subplot(2, 2, 4)
        error = np.abs(Z - Z_analytical)
        pcm4 = ax4.pcolormesh(X, Y, error, shading='auto', cmap='hot')
        fig.colorbar(pcm4, ax=ax4)
        ax4.set_title(f'Error Absoluto - {name}')
    else:
        ax1 = fig.add_subplot(121, projection='3d')
        surf = ax1.plot_surface(X, Y, Z, cmap='viridis')
        ax1.set_title(f'3D - {name}')
        fig.colorbar(surf, ax=ax1, shrink=0.5, aspect=5)

        ax2 = fig.add_subplot(122)
        heatmap = ax2.pcolormesh(X, Y, Z, shading='auto', cmap='viridis')
        ax2.set_title(f'Mapa de Calor - {name}')
        fig.colorbar(heatmap, ax=ax2)

    plt.tight_layout()
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    plt.close()

def main(input_dir, output_dir):
    if not os.path.exists(input_dir):
        print(f"Error: Directorio de entrada {input_dir} no existe")
        return False

    dat_files = []
    for root, _, files in os.walk(input_dir):
        for filename in files:
            if filename.endswith('.dat'):
                dat_files.append(os.path.join(root, filename))

    total = len(dat_files)
    if total == 0:
        print("No se encontraron archivos .dat")
        return False

    for i, input_path in enumerate(dat_files, 1):
        relative_path = os.path.relpath(input_path, input_dir)
        relative_dir = os.path.dirname(relative_path)
        base_name = os.path.splitext(os.path.basename(relative_path))[0] + ".png"
        output_subdir = os.path.join(output_dir, relative_dir)
        output_path = os.path.join(output_subdir, base_name)

        try:
            process_solution_file(input_path, output_path)
        except Exception as e:
            print(f"\nError procesando {input_path}: {str(e)}")

        percent = (i * 100) / total
        print(f"\rGenerando gráficos {i}/{total} ({percent:.0f}%) - {relative_path}", end='', flush=True)

    print("\nProceso de generación de gráficos finalizado.")
    return True

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Uso: python plot_results.py <directorio_entrada> <directorio_salida>")
        sys.exit(1)

    success = main(sys.argv[1], sys.argv[2])
    sys.exit(0 if success else 1)
