import pandas as pd
import matplotlib.pyplot as plt
from pylab import *
import matplotlib.pyplot as plt


archivos = [1,4,8,15,32,64]
""" acá se abriran los archivos para el exponente especificado """
for x  in archivos:
    k_data = pd.read_csv("experimento/output/resultados_2^"+str(x)+".csv")
    radix_data = k_data[ (k_data['s_name'] =='radix')]
    quick_data = k_data[ (k_data['s_name'] =='quick')]
    c1 = radix_data.columns.tolist()  
    c2 = quick_data.columns.tolist()  
    rdata = [radix_data[columna].tolist() for columna in c1]
    qdata = [quick_data[columna].tolist() for columna in c2]
    #print(rdata)
    #print(qdata)
    
    tiempos = k_data.groupby(['s_name'], as_index=False)
    #print(tiempos)
    # Crear el gráfico
    plt.figure(figsize=(8, 6))  # Opcional: establece el tamaño de la figura
    # setear valores x
    x_val = radix_data['repeticion'].unique()
    # setear valores y
    y1_Val = radix_data['sort_time(us)'].to_list()
    y2_Val = quick_data['sort_time(us)'].to_list()
    # Graficar la primera curva
    plt.plot(x_val, y1_Val, label="radix_sort", marker='o', linestyle='-')

    # Graficar la segunda curva
    plt.plot(x_val, y2_Val, label="quick_sort", marker='x', linestyle='--')

    # Personaliza el gráfico
    plt.title("Tiempos de Radix vs Quicksort por iteración")
    plt.xlabel("iteración")
    plt.ylabel("tiempos")
    plt.legend()  # Agrega una leyenda
    plt.grid(True)  # Agrega una cuadrícula
    savefig("grafico2^"+str(x)+".png", dpi=300)  # Guardo la figura en formato png a 300 DPI 
    plt.show()


