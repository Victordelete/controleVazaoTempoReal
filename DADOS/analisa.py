import os

file = "analisa.py"

path = os.path.abspath(file)
path = path[0: -len(file)]

tId = "\\0_doisConsumosIguais.txt"

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

while True:
    linha = arquivo.readline().strip()
    ciclo.append(linha)

    linha = arquivo.readline().strip()
    tanque1.append(linha)

    linha = arquivo.readline().strip()
    tanque2.append(linha)

    linha = arquivo.readline().strip()
    tanque3.append(linha)

    linha = arquivo.readline().strip()
    vazao1.append(linha)

    linha = arquivo.readline().strip()
    vazao2.append(linha)

    linha = arquivo.readline().strip()
    consumo1.append(linha)

    linha = arquivo.readline().strip()
    consumo2.append(linha)

    linha = arquivo.readline().strip()
    tempoRes.append(linha)
    
    linha = arquivo.readline()
    linha = arquivo.readline() #Leio os \n entre cada leitura
    
    if linha == '':
        print("Fim do arquivo.\n")
        break

print(tempoRes)

arquivo.close()