import serial
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from matplotlib.animation import FuncAnimation

    
def animate():
    ax[0].cla()
    ax[1].cla()
    
    ax[0].plot(tanque1)
    ax[1].plot(tanque2)

porta = serial.Serial('COM7', 9600)	#Configurando e abrindo a porta

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
k = 0

fig, ax = plt.subplots(2)

ax[0].plot(ind, tanque1, 'g', ind, tanque2, 'r', ind, tanque3, 'y')

ax[1].plot(ind, consumo1, 'g', ind, consumo2, 'r')

while i <= 100:
    linha = porta.readline().strip().decode('ascii')
    
    if len(linha) == 0:
        ind.append(k)
        k = k+1
        
        linha = porta.readline().strip().decode('ascii')
        
        linha = porta.readline().strip().decode('ascii')
        ciclo.append(linha)
        
        linha = float(porta.readline().strip().decode('ascii'))
        tanque1.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        tanque2.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        tanque3.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        vazao1.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        vazao2.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        consumo1.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        consumo2.append(linha)
    
        linha = float(porta.readline().strip().decode('ascii'))
        tempoRes.append(linha)
        
        
        ax[0].plot(ind, tanque1, 'g', ind, tanque2, 'r', ind, tanque3, 'y')

        ax[1].plot(ind, consumo1, 'g', ind, consumo2, 'y')
        
        plt.pause(0.01)
    
    
    i = i+1

    
porta.close()