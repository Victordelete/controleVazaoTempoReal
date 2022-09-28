#include "functions.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <unistd.h>
#include <time.h>
using namespace std;

//fun��o utilizada para determinar as interrup��es poss�veis
    //limite seguran�a para sensores, bot�o seguran�a, bot�o desligamento controle.
bool analizaInterrupcoes( float interrupcao_tempo , float inicio_geral){

    //transformar a quantidade de tempo em clock
    int clock_limite = int(interrupcao_tempo*float(CLOCKS_PER_SEC));

    //caso eu tenha alcan�ado o limite de clock para a interrupcao eu testo a diretiva
    if(clock_limite < int((clock()-inicio_geral)*1000)){
        cout<<"\n\n";
        tempo_passado(inicio_geral);
        cout<<"Interrupcao apos tempo limite da chamada.\n";
        cout<<"Chamada da funcao que realiza tratativa de finalizacao de processo.\n\n\n";

        return true;
    }
    //caso n�o tenoa cegado ao limite somente pauso o per�odo de teset da interrup��o
    else{
        //cout<<"Interrupcao tempo: ";
        funcSleep(randomGen(15,20));
        return false;
    }
    return false;
}

//fun��o utilizada para realiza��o do controle PI da vaz�o de controle
controlProper atuControleVazao(controlProper contStatus, 
                          tanqueObjeto tanque1,
                          tanqueObjeto tanque2, 
                          tanqueObjeto tanque3){
    //cout<<"Controle Vazao Tempo: ";
    funcSleep(randomGen(225,300));

    float random;

    //Utilizando um consumo randomico
    random = 0.01*float(rand()%100);
    contStatus.consumo1 = random;

    random = 0.01*float(rand()%100);
    contStatus.consumo2 = random;

    float media = (tanque1.preenAtual + tanque2.preenAtual + tanque3.preenAtual) / 3;
    contStatus.vazao1 = contStatus.ganho*(tanque1.preenAtual-media);
    contStatus.vazao2 = contStatus.ganho*(tanque3.preenAtual-media);

    return contStatus;
}

tanqueObjeto atuAltura(controlProper contStatus, tanqueObjeto tanque, int idTanque){
    tanque.preenAnter = tanque.preenAtual;

    //selecionar o calculo para diferentes valores. 
    switch (idTanque)
    {
    case 1:
        tanque.preenAtual = tanque.preenAnter - 
                            contStatus.consumo1*contStatus.delTempo - 
                            contStatus.vazao1*contStatus.delTempo;
        break;
    case 2:
        tanque.preenAtual = tanque.preenAnter + 
                            contStatus.vazao1*contStatus.delTempo + 
                            contStatus.vazao2*contStatus.delTempo; 
        break;
    case 3:
        tanque.preenAtual = tanque.preenAnter - 
                            contStatus.consumo2*contStatus.delTempo - 
                            contStatus.vazao2*contStatus.delTempo;
        break;
    }

    return tanque; 
}

//fun��o utilizada para leitura auxiliar de press�o do sistema
grandeza atuSensorPressao(grandeza valor){
    funcSleep(randomGen(75,100));
    return valor;
}

//fun��o utilizada para leitura auxiliar de press�o do sistema
grandeza atuSensorVazao(grandeza valor){
    valor.tempoLeit = 2;
    funcSleep(randomGen(75,100));
    return valor;
}

//fun��o utilizada para leitura auxiliar de press�o do sistema
grandeza atuSensorTemperatura(grandeza valor){
    funcSleep(randomGen(75,100));
    return valor;
}

//fun��o utilizada para leitura auxiliar de press�o do sistema
grandeza atuSensorAltura(grandeza valor){
    funcSleep(randomGen(75,100));
    return valor;
}

//fun��o que realiza um sleep de tempo recebido
void funcSleep(int temp_Sleep){
    usleep(temp_Sleep*1000);
    return;
}

//fun��o que gera a randomiza��o dos processos de leitura
int randomGen(int lim_inf, int lim_sup){
    int random = lim_inf + rand()%(lim_sup-lim_inf);
    return random;
}

//fun��o imprime o tempo passado
void tempo_passado(float inicio_geral){
    double temp_passado;
    temp_passado = double(int(clock()-inicio_geral)/double(CLOCKS_PER_SEC)*1000);
    //cout<<"TEMPO PASSADO: ";
    //cout << fixed << showpoint; //delimitar precisao da impressao do tempo
    //cout << setprecision(3);
    //cout<<temp_passado<<endl;
    //cout<<"\n";
}
