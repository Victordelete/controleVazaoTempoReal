/*Trabalho 1: Sistemas de Tempo Real
    Aplicação desenvolvida para o trabalho de Sistemas de Tempo Real.

    Programa implementa o controle um processo de vazão para um tanque fechado,
    levando em consideração o controlador de vazão, leitura de sensor de pressão,
    sensor de algura do líquido, sensor de composição da mistura, e sensor de vazão.
    Assim como um processo não periodico de acionamento de segurança do processo.

    Aluno: Victor Hugo Marques Vieira.
    Matrícula: 150047649.

    Desenvolvimento em C/C++ utilizando as bibliotecas nativas do CodeBlocks versão 17.12
    habilitando funções de compilação para C++ 2011 ISO C Language.
*/

//Inclusões necessárias para o programa
#include "functions.cpp" //módulo das funções desenvolvidas

    //bibliotecas de tempo para o sistema
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
    using namespace std;

//definições de constantes globais utilizadas no programa
int temp_ciclo = 650 ; //tempo de cada ciclo
clock_t temp_ini, temp_fim;
float inicio_geral; //guardar o inicio geral do programa

//Função que análisa o tempo necessário para o sincronismo
void anaSleep();
//função que realiza um sleep de tempo recebido
void funcSleep(float temp_Sleep);

//inicio do programa
int main(int argc, char *argv[]){

    if(argc != 3) {
        cout<<"Poucos argumentos.\n";
        return -1;
    }

    //atribuição das chamadas da função
    char interrupcao_tipo = argv[1][0];
    float interrupcao_tempo = strtof(argv[2], nullptr) ;

    //caso o argumento recebido seja diferente do tipo T ou P não é um teste válido
    if(interrupcao_tipo != 'T' && interrupcao_tipo != 'P'){
        cout<<"Tipo de teste '"<<interrupcao_tipo<<"' nao suportado.\n\n";
        return -1;
    }

    //auxiliar para geração dos testes aleatórios
    unsigned seed = time(NULL);
    srand(seed);

    //Inicialização dos objetos que herdarão os valores das funções
    grandeza controleVazao;
    grandeza sensorPressao;
    grandeza sensorVazao;
    grandeza sensorTemperatura;
    grandeza sensorAltura;

    inicio_geral = float(clock());
    cout<<"inicio geral"<<inicio_geral<<"\n\n";
    //loop infinito para o controle das funções periodicas
    while(true){
        ///PRIMEIRO CICLO
        //pego o tempo inicial do ciclo
        temp_ini = clock()-inicio_geral;
        tempo_passado( inicio_geral);
            //atualizo as funções deste ciclo
            controleVazao = atuControleVazao(controleVazao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo,  inicio_geral))
                        break;
            sensorPressao = atuSensorPressao(sensorPressao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo,  inicio_geral))
                        break;
            sensorVazao = atuSensorVazao(sensorVazao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo,  inicio_geral))
                        break;
        //pego o tempo final do ciclo
        temp_fim = clock()-inicio_geral;
        anaSleep();//vejo quão longe do fim do ciclo para inicio do próximo

        ///SEGUNDO CICLO
        //pego o tempo inicial do ciclo
        temp_ini = clock()-inicio_geral;
        tempo_passado(inicio_geral);
            controleVazao = atuControleVazao(controleVazao);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo, inicio_geral))
                        break;
            sensorTemperatura = atuSensorTemperatura(sensorTemperatura);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo, inicio_geral))
                        break;
            sensorAltura = atuSensorAltura(sensorAltura);
                if(analizaInterrupcoes(interrupcao_tipo, interrupcao_tempo, inicio_geral))
                        break;
        temp_fim = clock()-inicio_geral;
        anaSleep(); //vejo quão longe do fim do ciclo para inicio do próximo
    }

    return 0;
}

//Função que análisa o tempo necessário para o sincronismo
void anaSleep(){
    //vejo o tempo necessário para atingir o período do ciclo
    int temp_dif = temp_ciclo - (int(temp_fim) - int(temp_ini)); //ciclo de clock não convertido para segundos
    //pauso o sistema para atingir este tempo
    cout<<"Fim de ciclo: ";
    //testo para caso o ciclo tenha sido ultrapassado
    if(temp_dif>0){
        funcSleep(temp_dif);
    }
    cout<<"\n";
    return;
}
