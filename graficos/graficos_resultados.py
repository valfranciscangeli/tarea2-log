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
    radix_data = radix_data.groupby('repeticion')
    quick_data = quick_data.groupby('repeticion')
    print(radix_data)
    print(quick_data)

    tiempos = k_data.groupby(['s_name'], as_index=False)
    #print(tiempos)
    savefig("grafico2^"+str(x)+".png", dpi=300)  # Guardo la figura en formato png a 300 DPI 


