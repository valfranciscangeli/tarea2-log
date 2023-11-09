import pandas as pd
import matplotlib.pyplot as plt
from pylab import *


archivos = range(1, 65)
eje_x = []
eje_y_radix = []
eje_y_quick = []
""" acá se abriran los archivos para el exponente especificado """
for x  in archivos:
    # Agregar el exponente del tamaño del universo al eje x
    eje_x.append(x)

    # Abrir archivo de resultados
    k_data = pd.read_csv("output/resultados_2^"+str(x)+".csv")

    # Separar data de cada algoritmo
    radix_data = k_data[ (k_data['s_name'] =='radix')]
    quick_data = k_data[ (k_data['s_name'] =='quick')]

    # Agregar cada promedio a su eje respectivo
    eje_y_radix.append(radix_data.mean(numeric_only=True)['sort_time(us)'])
    eje_y_quick.append(quick_data.mean(numeric_only=True)['sort_time(us)'])
    

# Crear el gráfico
plt.figure(figsize=(8, 6))  # Opcional: establece el tamaño de la figura

# setear valores x
x_val = eje_x

# setear valores y
y1_Val = eje_y_radix
y2_Val = eje_y_quick

# Graficar la primera curva
plt.plot(x_val, y1_Val, label="radix_sort", marker='o', linestyle='-')

# Graficar la segunda curva
plt.plot(x_val, y2_Val, label="quick_sort", marker='x', linestyle='--')

# Personaliza el gráfico
plt.title(f"Tiempos promedio de $RadixSort$ vs $Quicksort$ para 100 consultas vs universo tamaño $2^x$")

plt.xlabel("Exponente Tamaño Universo")
plt.ylabel("Tiempo Promedio")
plt.legend()  # Agrega una leyenda
plt.grid(True)  # Agrega una cuadrícula
savefig("grafico_promedios.png", dpi=300)  # Guardo la figura en formato png a 300 DPI 
plt.show()


