import pandas as pd


""" aca vamos a recorrer el csv pa encontrar el k mejor para cada universo """

k_data = pd.read_csv("experimento/output/Registro_de_tiempos_por_cada_k.csv")
print(k_data)

promedios = k_data.groupby(['n_universo', 'k_value'], as_index=False)['tiempo_(micro_segundos)'].mean()
print(promedios)


minimos = {}
for ind in promedios.index:
    llave = promedios['n_universo'][ind]
    k = promedios['k_value'][ind]
    promedio = promedios['tiempo_(micro_segundos)'][ind] 
    #print(promedios['n_universo'][ind], promedios['k_value'][ind], promedios['tiempo_(micro_segundos)'][ind])
    if not llave in minimos:
        min_value = (k, promedio)
        minimos[llave] = min_value
    else:
        prev_min_value = minimos[llave]
        new_min_value = (k, promedio)
        #print("valores de promedio",prev_min_value[0] ,prev_min_value[1] , new_min_value[0], new_min_value[1])
        if prev_min_value[1] > new_min_value[1]:
            minimos[llave] = new_min_value
            
            
#print(minimos)



# crear vector para el otro exp
resultado = []
for llave in minimos:
    resultado.append(minimos[llave][0])
    
    
print("lista de k's elegidos: " + str(resultado))


# graficamos k vs tiempo promedio para cada universo

