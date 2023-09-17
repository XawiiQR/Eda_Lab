import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
#print(pandas.__version__)
#datos = pd.read_csv('distancias.txt',header=None)
datos = pd.read_csv('distancias.txt')
cabeza = datos.columns.tolist()
head=int(cabeza[0])


# Genera un vector de 10 números aleatorios entre 0 y 100 (cambia esto según tus datos)

# Crea el histograma
plt.hist(datos, bins=10, edgecolor='black')
y= datos.max().max()
plt.xlim(0, y+0.01)  # Comienza en 0 y termina en el valor máximo de los datos

print(datos.max().max())
# Configura etiquetas y título
plt.xlabel('Valores')
plt.ylabel('Frecuencia')
plt.title(f'Histograma de {head} datos Aleatorios')

# Muestra el histograma
plt.show()
#print(head)
#print (datos)