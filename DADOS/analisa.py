import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

file = "analisa.py"

path = os.path.abspath(file)
path = path[0: -len(file)]

i = 3

if i == 0:
    tId = "\\0_doisConsumosIguais.txt"

if i == 1:
    tId = "\\1_consumoTresVezesMaior.txt"

if i == 2:
    tId = "\\2_consumoZera.txt"

if i == 3:
    tId = "\\2_consumoZera - Copia.txt"
    
print(path+tId)

arquivo = open(path + tId, "r")

ciclo = []
tanque1 = []
tanque2 = []
tanque3 = []
vazao1 = []
vazao2 = []
consumo1 = []
consumo2 = []
tempoRes = []
ind = []

i = 0

while True:
    ind.append(i)
    i = i+1
    
    linha = arquivo.readline().strip()
    ciclo.append(linha)

    linha = float(arquivo.readline().strip())
    tanque1.append(linha)

    linha = float(arquivo.readline().strip())
    tanque2.append(linha)

    linha = float(arquivo.readline().strip())
    tanque3.append(linha)

    linha = float(arquivo.readline().strip())
    vazao1.append(linha)

    linha = float(arquivo.readline().strip())
    vazao2.append(linha)

    linha = float(arquivo.readline().strip())
    consumo1.append(linha)

    linha = float(arquivo.readline().strip())
    consumo2.append(linha)

    linha = float(arquivo.readline().strip())
    tempoRes.append(linha)
    
    linha = arquivo.readline()
    linha = arquivo.readline() #Leio os \n entre cada leitura
    
    if linha == '':
        print("Fim do arquivo.\n")
        break

fig, ax = plt.subplots(2)

ax[0].plot(ind, tanque1, 'g', ind, tanque2, 'r', ind, tanque3, 'y')

#ax[1].plot(ind, consumo1, 'g', ind, consumo2, 'y')
ax[1].plot(ind, tempoRes)

arquivo.close()