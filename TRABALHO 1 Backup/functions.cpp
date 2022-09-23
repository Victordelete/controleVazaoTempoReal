#include "functions.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <unistd.h>
#include <time.h>
using namespace std;

//função utilizada para determinar as interrupções possíveis
    //limite segurança para sensores, botão segurança, botão desligamento controle.
bool analizaInterrupcoes(char interrupcao_tipo, float interrupcao_tempo , float inicio_geral){

    //transformar a quantidade de tempo em clock
    int clock_limite = int(interrupcao_tempo*float(CLOCKS_PER_SEC));

    //caso eu tenha alcançado o limite de clock para a interrupcao eu testo a diretiva
    if(clock_limite < int((clock()-inicio_geral)*1000)){
        if(interrupcao_tipo == 'T'){
            cout<<"\n\n";
            tempo_passado(inicio_geral);
            cout<<"Interrupcao devido a botao tempo.\n";
            cout<<"Chamada da funcao que realiza tratativa de finalizacao de processo.\n\n\n";

            return true;
        }
        if(interrupcao_tipo == 'P'){
            cout<<"\n\n";
            tempo_passado(inicio_geral);
            cout<<"Interrupcao devido a botao emergencia.\n";
            cout<<"Chamada da funcao que realiza tratativa de emergencia.\n\n\n";

            return true;
        }
    }
    //caso não tenoa cegado ao limite somente pauso o período de teset da interrupção
    else{
        cout<<"Interrupcao tempo: ";
        funcSleep(randomGen(15,20));
        return false;
    }
    return false;
}

//função utilizada para realização do controle PI da vazão de controle
grandeza atuControleVazao(grandeza valor){
    cout<<"Controle Vazao Tempo: ";
    funcSleep(randomGen(225,300));
    return valor;
}

//função utilizada para leitura auxiliar de pressão do sistema
grandeza atuSensorPressao(grandeza valor){
    cout<<"Sensor Pressao Tempo: ";
    funcSleep(randomGen(75,100));
    return valor;
}

//função utilizada para leitura auxiliar de pressão do sistema
grandeza atuSensorVazao(grandeza valor){
    cout<<"Sensor Vazao Tempo: ";
    valor.tempoLeit = 2;
    funcSleep(randomGen(75,100));
    return valor;
}

//função utilizada para leitura auxiliar de pressão do sistema
grandeza atuSensorTemperatura(grandeza valor){
    cout<<"Sensor Temperatura tempo: ";
    funcSleep(randomGen(75,100));
    return valor;
}

//função utilizada para leitura auxiliar de pressão do sistema
grandeza atuSensorAltura(grandeza valor){
    cout<<"Sensor Altura tempo: ";
    funcSleep(randomGen(75,100));
    return valor;
}

//função que realiza um sleep de tempo recebido
void funcSleep(int temp_Sleep){
    cout<<temp_Sleep<<"\n";

    usleep(temp_Sleep*1000);
    return;
}

//função que gera a randomização dos processos de leitura
int randomGen(int lim_inf, int lim_sup){
    //unsigned seed = time(NULL);
    //srand(seed);
    int random = lim_inf + rand()%(lim_sup-lim_inf);
    return random;
}

//função imprime o tempo passado
void tempo_passado(float inicio_geral){
    double temp_passado;
    temp_passado = double(int(clock()-inicio_geral)/double(CLOCKS_PER_SEC)*1000);
    cout<<"TEMPO PASSADO: ";
    cout << fixed << showpoint; //delimitar precisao da impressao do tempo
    cout << setprecision(3);
    cout<<temp_passado<<endl;
    cout<<"\n";
}
